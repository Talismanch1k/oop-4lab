#include "console_render_class.h"

void ConsoleRender::renderField() {
  std::vector<std::vector<int>> game_field = game_field_.getGameField();
  int height = game_field_.getHeight(), width = game_field_.getWidth();

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (game_field[i][j] == GameField::CellStatus::kUnknown) {
        std::cout << ". ";
      } else if (game_field[i][j] == GameField::CellStatus::kEmpty) {
        std::cout << "O ";
      } else if (game_field[i][j] == GameField::CellStatus::kDamaged) {
        std::cout << "# ";
      } else if (game_field[i][j] == GameField::CellStatus::kDestroyed) {
        std::cout << "X ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
void ConsoleRender::renderWin(bool is_player_turn) {
  if (is_player_turn) {
    std::cout << "Победил игрок" << std::endl;
  } else {
    std::cout << "Победил компьютер" << std::endl;
  }
}

void ConsoleRender::renderShipField() {
  int height = game_field_.getHeight(), width = game_field_.getWidth();
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (!game_field_.isShipSegment(j, i)) {
        std::cout << ". ";
      } else {
        std::cout << "S ";
      }
    }
    std::cout << std::endl;
  }
}
void ConsoleRender::renderTurn(bool is_player_turn) {
  if (is_player_turn) {
    std::cout << "Ход игрока:" << std::endl;
  } else {
    std::cout << "Ход компьютера:" << std::endl;
  }
}

void ConsoleRender::renderPlacementShip() {
  std::cout << "Расстановка кораблей" << std::endl;
}
void ConsoleRender::renderAbility(AbilityManager::AbilityType type, bool res) {
  std::cout << "Была использована способность: ";
  switch (type) {
    case AbilityManager::AbilityType::kDoubleDamage: {
      std::cout << "DoubleDamage";
      break;
    }
    case AbilityManager::AbilityType::kBombardment: {
      std::cout << "Bombardment";
      break;
    }
    case AbilityManager::AbilityType::kScanner: {
      std::cout << "Scanner " << res;
      break;
    }
  }
  std::cout << std::endl;
}


