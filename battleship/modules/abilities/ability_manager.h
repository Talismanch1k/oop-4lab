#ifndef BATTLESHIP_MODULES_ABILITYMANAGER_H_
#define BATTLESHIP_MODULES_ABILITYMANAGER_H_

#include <queue>
#include <memory>
#include <random>
#include <ctime>

#include "ability_interface.h"
#include "scanner_class.h"
#include "double_damage_class.h"
#include "bombardment_class.h"


class AbilityManager {
 public:
  enum AbilityType {
    kDoubleDamage,
    kScanner,
    kBombardment,
    kAbilityCount // Count of abilities
  };
 private:
  std::queue<AbilityType> abilities_queue_;  // Очередь способностей игрока
 public:
  AbilityManager();
  void addRandomAbility();
  void addAbility(AbilityType ability);
  void checkIfEnemyDestroyed(ShipManager &ship_manger); // temporary
  bool useFirstAbility(GameField &game_field, std::shared_ptr<ShipManager> ship_manager, PlayerSettings &player_settings, int x, int y);
  nlohmann::json serialize() const;
  static AbilityManager deserialize(const nlohmann::json& json);
  AbilityType getAbilityType();

};

class NoAbilitiesException : public std::runtime_error {
 public:
  NoAbilitiesException() : std::runtime_error("Способности закончились.") {}
};

#endif //BATTLESHIP_MODULES_ABILITYMANAGER_H_
