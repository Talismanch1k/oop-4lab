#include "player_settings.h"

void PlayerSettings::setDamageMultiplier(int multiplier) {
  damage_multiplier_ = multiplier;
}

int PlayerSettings::applyDamageMultiplier() {
  int multiplier = damage_multiplier_;
  damage_multiplier_ = 1;
  return multiplier;
}
int PlayerSettings::getBaseDamage() const {
  return base_damage_;
}
nlohmann::json PlayerSettings::serialize() const {
  nlohmann::json j;
  j["base_damage"] = base_damage_;
  j["damage_multiplier"] = damage_multiplier_;
  return j;
}
PlayerSettings PlayerSettings::deserialize(const nlohmann::json &json) {
  PlayerSettings settings;
  settings.base_damage_ = json.at("base_damage").get<int>();
  settings.damage_multiplier_ = json.at("damage_multiplier").get<int>();
  return settings;
}
