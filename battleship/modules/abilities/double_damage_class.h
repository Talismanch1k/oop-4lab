#ifndef BATTLESHIP_MODULES_ABILITIES_DOUBLE_DAMAGE_CLASS_H_
#define BATTLESHIP_MODULES_ABILITIES_DOUBLE_DAMAGE_CLASS_H_

#include "ability_interface.h"
#include "../entities/player_settings.h"

class DoubleDamage : public Ability {
  PlayerSettings &player_settings_;
 public:
  DoubleDamage(PlayerSettings &player_settings);
  bool use() override;
};

#endif //BATTLESHIP_MODULES_ABILITIES_DOUBLE_DAMAGE_CLASS_H_
