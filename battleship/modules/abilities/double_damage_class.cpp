#include "double_damage_class.h"

DoubleDamage::DoubleDamage(PlayerSettings &player_settings) : player_settings_(player_settings) {}

bool DoubleDamage::use() {
  std::cout << "Enable double damage on next attack" << std::endl;
  player_settings_.setDamageMultiplier(2);
  return true;
}