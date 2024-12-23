#ifndef BATTLESHIP_MODULES_PLAYER_SETTINGS_H_
#define BATTLESHIP_MODULES_PLAYER_SETTINGS_H_

#include "../additional/json.hpp"

class PlayerSettings {
 private:
  int base_damage_ = 1;
  int damage_multiplier_ = 1;
 public:
  void setDamageMultiplier(int multiplier);
  int applyDamageMultiplier();
  int getBaseDamage() const;
  nlohmann::json serialize() const;
  static PlayerSettings deserialize(const nlohmann::json& json);
};

#endif //BATTLESHIP_MODULES_PLAYER_SETTINGS_H_
