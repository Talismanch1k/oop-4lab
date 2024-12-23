#ifndef BATTLESHIP_MODULES_ABILITIES_CLASS_H_
#define BATTLESHIP_MODULES_ABILITIES_CLASS_H_

#include "../entities/game_field_class.h"

class Ability {
 public:
  virtual bool use() = 0;
};

#endif //BATTLESHIP_MODULES_ABILITIES_CLASS_H_
