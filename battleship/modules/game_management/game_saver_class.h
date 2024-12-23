#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_SAVER_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_SAVER_CLASS_H_

#include "game_state_class.h"

class GameSaver {
 private:
  GameState *game_state_;
 public:
  GameSaver(GameState *game_state) : game_state_(game_state){};

  void loadFromFile(const std::string &filename);
  void saveToFile(const std::string& filename);

};

#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_SAVER_CLASS_H_
