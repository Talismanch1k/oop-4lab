#ifndef BATTLESHIP_MODULES_ABILITIES_SCANNER_CLASS_H_
#define BATTLESHIP_MODULES_ABILITIES_SCANNER_CLASS_H_

#include "ability_interface.h"
#include "../entities/game_field_class.h"

namespace scanner_settings {
const int kX = 2;
const int kY = 2;
}

class Scanner : public Ability {
 private:
  GameField &game_field_;
  int x_, y_;

 public:
  Scanner(GameField &game_field, int x, int y);
  bool use() override;

};



#endif //BATTLESHIP_MODULES_ABILITIES_SCANNER_CLASS_H_
