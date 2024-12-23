#include "game_field_class.h"

#include <utility>

GameField::Cell::Cell() : cell_status(kEmpty), ship(nullptr), segment_index(-1) {}

GameField::GameField(int width, int height, std::shared_ptr<ShipManager> ship_manager, PlayerSettings &player_settings) :
    width_(width), height_(height), ship_manager_(std::move(ship_manager)), player_settings_(player_settings) {
  ship_field_.resize(height, std::vector<Cell>(width));
  game_field_.resize(height, std::vector<int>(width, kUnknown));
}

bool GameField::canPlaceShip(int x, int y, int length, bool isVertical) {
  if (x < 0 || y < 0 || x >= width_ || y >= height_) return false;
  if (isVertical) {
    if (y + length > height_) return false;
    for (int xi = std::max(x - 1, 0); xi <= std::min(x + 1, width_ - 1); xi++) {
      for (int yi = std::max(0, y - 1); yi < std::min(y + length + 1, height_ - 1); ++yi) {
        if (ship_field_[yi][xi].cell_status != kEmpty) {
          return false;
        }
      }
    }
  } else {
    if (x + length > width_) return false;
    for (int yi = std::max(y - 1, 0); yi <= std::min(y + 1, height_ - 1); yi++) {
      for (int xi = std::max(0, x - 1); xi <= std::min(x + length + 1, width_ - 1); ++xi) {
        if (ship_field_[yi][xi].cell_status != kEmpty) {
          return false;
        }
      }
    }
  }
  return true;
}

//bool GameField::placeShip(Ship &ship, int x, int y) {
//  int length = ship.getLength();
//
//  if (!canPlaceShip(x, y, length, ship.isVertical())) {
//    throw ShipPlacementException();
//  }
//
//  for (int i = 0; i < length; ++i) {
//    if (ship.isVertical()) {
//      ship_field_[y + i][x].cell_status = kDestroyed;
//      ship_field_[y + i][x].ship = &ship;
//      ship_field_[y + i][x].segment_index = i;
//    } else {
//      ship_field_[y][x + i].cell_status = kDestroyed;
//      ship_field_[y][x + i].ship = &ship;
//      ship_field_[y][x + i].segment_index = i;
//    }
//  }
//
//  return true;
//}


bool GameField::placeShip(int ship_index, int x, int y) {
  Ship &ship = ship_manager_->getShip(ship_index);
  int length = ship.getLength();

  if (!canPlaceShip(x, y, length, ship.isVertical())) {
    throw ShipPlacementException();
  }

  for (int i = 0; i < length; ++i) {
    if (ship.isVertical()) {
      ship_field_[y + i][x].cell_status = kDestroyed;
      ship_field_[y + i][x].ship = &ship;
      ship_field_[y + i][x].segment_index = i;
    } else {
      ship_field_[y][x + i].cell_status = kDestroyed;
      ship_field_[y][x + i].ship = &ship;
      ship_field_[y][x + i].segment_index = i;
    }
  }

  return true;
}


bool GameField::attack(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    throw OutOfBoundsAttackException();
  }

  if (isShipSegment(x, y)) {
    Cell &cell = ship_field_[y][x];
    game_field_[y][x] = kDestroyed;
    cell.ship->takeDamage(cell.segment_index,
                          player_settings_.getBaseDamage() * player_settings_.applyDamageMultiplier());
    if (cell.ship->getSegmentState(cell.segment_index) == Ship::SegmentState::kDamaged) {
      game_field_[y][x] = GameField::CellStatus::kDamaged;
    } else {
      game_field_[y][x] = GameField::CellStatus::kDestroyed;
    }
    return true;
  } else {
    game_field_[y][x] = kEmpty;
    return false;
  }
}

bool GameField::isShipSegment(int x, int y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_)
    return false;

  Cell &cell = ship_field_[y][x];
  if (cell.cell_status == kDestroyed && cell.ship)
    return true;
  else
    return false;
}



// Конструктор копирования
GameField::GameField(const GameField &other)
    : width_(other.width_),
      height_(other.height_),
      ship_manager_(other.ship_manager_),
      player_settings_(other.player_settings_) {
  game_field_.resize(other.width_, std::vector<int>(other.height_, 0));
  game_field_ = other.game_field_;
  ship_field_.resize(other.width_, std::vector<Cell>(other.height_));
  ship_field_ = other.ship_field_;
}

// Оператор присваивания копирования
GameField &GameField::operator=(const GameField &other) {
  if (this != &other) {
    width_ = other.width_;
    height_ = other.height_;
    ship_manager_ = other.ship_manager_;
    game_field_ = other.game_field_;
    ship_field_ = other.ship_field_;
    player_settings_ = other.player_settings_;
  }
  return *this;
}

// Конструктор перемещения
GameField::GameField(GameField &&other) noexcept
    : width_(other.width_), height_(other.height_),
      game_field_(std::move(other.game_field_)),
      ship_field_(std::move(other.ship_field_)),
      ship_manager_(other.ship_manager_),
      player_settings_(other.player_settings_) {
  other.width_ = 0;
  other.height_ = 0;
}

// Оператор присваивания перемещения
GameField &GameField::operator=(GameField &&other) noexcept {
  if (this != &other) {
    width_ = other.width_;
    height_ = other.height_;
    game_field_ = std::move(other.game_field_);
    ship_field_ = std::move(other.ship_field_);
    ship_manager_ = other.ship_manager_;
    player_settings_ = std::move(other.player_settings_);
  }
  return *this;
}

nlohmann::json GameField::serialize() const {
  nlohmann::json j;

  // Сериализация основных данных
  j["height"] = height_;
  j["width"] = width_;

  // Сериализация настроек игрока
  j["player_settings"] = player_settings_.serialize();

  // Сериализация ShipManager для игрока
  j["ship_manager"] = ship_manager_->serialize();

  // Сериализация игрового поля
  j["game_field"] = game_field_;

  // Сериализация корабельного поля
  nlohmann::json ship_field_json = nlohmann::json::array();
  for (const auto &row : ship_field_) {
    nlohmann::json row_json = nlohmann::json::array();
    for (const auto &cell : row) {
      nlohmann::json cell_json;
      cell_json["cell_status"] = cell.cell_status;
      cell_json["segment_index"] = cell.segment_index;

      // Если в клетке есть корабль, сериализуем его индекс
      if (cell.ship != nullptr) {
        int ship_index = ship_manager_->getShipIndex(cell.ship);
        if (ship_index >= 0) {
          cell_json["ship_index"] = ship_index;  // Индекс корабля
        }
      }
      row_json.push_back(cell_json);
    }
    ship_field_json.push_back(row_json);
  }
  j["ship_field"] = ship_field_json;

  return j;
}

GameField GameField::deserialize(const nlohmann::json &json) {
  // Считываем основные данные
  int height = json.at("height").get<int>();
  int width = json.at("width").get<int>();

  // Считываем настройки игрока и менеджера кораблей
  PlayerSettings player_settings = PlayerSettings::deserialize(json.at("player_settings"));
  std::shared_ptr<ShipManager> ship_manager = std::make_shared<ShipManager>(ShipManager::deserialize(json.at("ship_manager")));

  // Создаем объект GameField
  GameField field(width, height, ship_manager, player_settings);

  // Восстанавливаем игровое поле
  field.game_field_ = json.at("game_field").get<std::vector<std::vector<int>>>();

  // Восстанавливаем корабельное поле
  const auto &ship_field_json = json.at("ship_field");
  field.ship_field_.clear();
  for (const auto &row_json : ship_field_json) {
    std::vector<Cell> row;
    for (const auto &cell_json : row_json) {
      Cell cell;
      cell.cell_status = cell_json.at("cell_status").get<int>();
      cell.segment_index = cell_json.at("segment_index").get<int>();

      // Восстановление указателя на корабль
      if (cell_json.contains("ship_index")) {
        int ship_index = cell_json.at("ship_index").get<int>();
        if (ship_index >= 0 && ship_index < ship_manager->getShipCount()) {
          cell.ship = ship_manager->getShipByIndex(ship_index);  // Восстановление по индексу
        } else {
          cell.ship = nullptr; // Если индекс некорректен, оставляем nullptr
        }
      }
      row.push_back(cell);
    }
    field.ship_field_.push_back(row);
  }
  field.game_field_.resize(height, std::vector<int>(width));  // если game_field_ - это вектор
  field.ship_field_.resize(height, std::vector<Cell>(width));  // если game_field_ - это вектор

  return field;
}
int GameField::getWidth() const {
  return width_;
}
int GameField::getHeight() const {
  return height_;
}
void GameField::placeShipsRandomly() {
  for (int i = 0; i < ship_manager_->getShipCount(); ++i) {
    Ship &ship = ship_manager_->getShip(i);
    bool placed = false;

    while (!placed) {
      // Генерируем случайную ориентацию: горизонтальную или вертикальную
      bool is_vertical = std::rand() % 2 == 0;
      ship.setOrientation(is_vertical);

      // Генерируем случайные координаты для размещения
      int max_x = width_ - (is_vertical ? 1 : ship.getLength());
      int max_y = height_ - (is_vertical ? ship.getLength() : 1);
      int x = std::rand() % max_x;
      int y = std::rand() % max_y;

      // Пытаемся разместить корабль
      int tries = 0;
      try {
        this->placeShip(i, x, y);
        placed = true;
      } catch (std::exception &e) {
        tries++;
        if (tries >= 10) {
          std::cout << e.what() << std::endl;
          throw std::runtime_error("Невозможно поставить корабль");
        }
      }
    }
  }
}
std::vector<std::vector<int>> GameField::getGameField() const {
  return game_field_;
}
bool GameField::placeLastShip(int x, int y) {
  return placeShip(ship_manager_->getShipCount() - 1, x, y);
}
std::vector<std::vector<GameField::Cell>> GameField::getShipField() const {
  return ship_field_;
}
PlayerSettings GameField::getPlayerSettings() {
  return player_settings_;
}


