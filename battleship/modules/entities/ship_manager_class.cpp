#include "ship_manager_class.h"

ShipManager::ShipManager(const std::vector<int> &ship_sizes) {
  for (int size : ship_sizes) {
    ships_.emplace_back(size, true);
  }
}

Ship &ShipManager::getShip(int index) {
  // TODO: throw exception
  return ships_[index];
}

int ShipManager::getShipCount() const {
  return ships_.size();
}

void ShipManager::displayShips() const {
  for (int i = 0; i < ships_.size(); ++i) {
    std::cout << "Ship " << i << " segments: ";
    for (int j = 0; j < ships_[i].getLength(); ++j) {
      int status = ships_[i].getSegmentState(j);
      if (status == Ship::kIntact) {
        std::cout << "[Whole] ";
      } else if (status == Ship::kDamaged) {
        std::cout << "[Damaged] ";
      } else if (status == Ship::kDestroyed) {
        std::cout << "[Destroyed] ";
      }
    }
    std::cout << std::endl;
  }
}
int ShipManager::countDestroyedShips() const {
  int count = 0;
  for (const Ship& ship : ships_) {
    if (ship.isDestroyed()) count++;
  }
  return count;
}

void ShipManager::updateDestroyedShips(int count) {
  ships_destroyed_ = count;
}

bool ShipManager::isNewShipDestroyed() {
  int newCountDestroyedShips = countDestroyedShips();
  if (ships_destroyed_ < newCountDestroyedShips) {
    updateDestroyedShips(newCountDestroyedShips);
    return true;
  }
  return false;
}

int ShipManager::getShipIndex(const Ship* ship) const {
  auto it = std::find(ships_.begin(), ships_.end(), *ship);
  return (it != ships_.end()) ? std::distance(ships_.begin(), it) : -1;
}

Ship* ShipManager::getShipByIndex(int index) {
  if (index >= 0 && index < ships_.size()) {
    return &ships_[index];
  }
  return nullptr;
}
nlohmann::json ShipManager::serialize() const {
  nlohmann::json j;
  j["ships_destroyed"] = ships_destroyed_;
  // Создаем массив для кораблей
  j["ships"] = nlohmann::json::array();  // Указываем, что "ships" будет массивом

  for (const auto& ship : ships_) {
    j["ships"].push_back(ship.serialize());  // Добавляем каждый корабль в массив
  }
  return j;
}

ShipManager ShipManager::deserialize(const nlohmann::json& j) {
  // Проверяем наличие ключей и корректность структуры
  if (!j.contains("ships_destroyed") || !j.contains("ships")) {
    throw std::runtime_error("Неверный формат JSON для десериализации ShipManager.");
  }

  // Создаем новый объект ShipManager
  ShipManager manager = ShipManager();

  // Восстанавливаем количество уничтоженных кораблей
  manager.ships_destroyed_ = j.at("ships_destroyed").get<int>();

  // Восстанавливаем массив кораблей
  for (const auto& ship_json : j.at("ships")) {
    Ship ship = Ship::deserialize(ship_json); // Вызов метода десериализации Ship
    manager.ships_.push_back(ship);
  }

  return manager;
}



//ShipManager ShipManager::deserialize(const nlohmann::json &json) {
//  ShipManager manager;
//  for (const auto& ship_json : json) {
//    manager.addShip(Ship::deserialize(ship_json));
//  }
//  return manager;
//}

void ShipManager::addShip(const Ship& ship) {
  ships_.push_back(ship);
}
