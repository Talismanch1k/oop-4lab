#include <iostream>

#include <vector>
#include <ctime>
#include "modules/entities/game_field_class.h"
#include "modules/abilities/ability_manager.h"
#include "modules/game_management/game_class.h"

int main() {
  std::srand(std::time(0)); // инициализация генератора случайных чисел
  try {
      Game game;
      game.startGameLoop();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}