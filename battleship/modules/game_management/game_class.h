#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_CLASS_H_

#include "../abilities/ability_manager.h"
#include "game_state_class.h"
#include "game_saver_class.h"

#include "render/game_render_class.h"
#include "render/console_render_class.h"


class Game {
 protected:
  GameState game_state_;  // Состояние игры
  bool is_game_started_ = false;
  void startNewGame();
 public:
  Game();

  void saveGame(const std::string &filename);

  // Метод для загрузки игры
  void loadGame(const std::string &filename);

  // Проверка победы
  bool checkVictory();

  // Ход компьютера
  void computerTurn();

  void startNewRound();

  void switchTurn();

  bool isGameStarted();
  void attack(int x, int y);
  void placeShip(int size, bool is_vertical, int x, int y);
  void useAbility(int x, int y);
  void startGameLoop();
};

#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_CLASS_H_
