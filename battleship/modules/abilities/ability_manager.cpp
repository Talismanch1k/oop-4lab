#include "ability_manager.h"

AbilityManager::AbilityManager() {
  addRandomAbility();
}

void AbilityManager::addRandomAbility() {
  AbilityType randomAbility = static_cast<AbilityType>(std::rand() % AbilityType::kAbilityCount);
  abilities_queue_.push(randomAbility);
}


bool AbilityManager::useFirstAbility(GameField &game_field,
                                     std::shared_ptr<ShipManager> ship_manager,
                                     PlayerSettings &player_settings,
                                     int x,
                                     int y) {
  if (abilities_queue_.empty()) {
    throw NoAbilitiesException();
  }
  AbilityType ability = abilities_queue_.front();
  std::unique_ptr<Ability> current_ability;

  switch (ability) {
    case AbilityType::kDoubleDamage:current_ability = std::make_unique<DoubleDamage>(player_settings);
      break;
    case AbilityType::kScanner:current_ability = std::make_unique<Scanner>(game_field, x, y);
      break;
    case AbilityType::kBombardment:current_ability = std::make_unique<Bombardment>(ship_manager);
      break;
  }

  bool result = current_ability->use();
  abilities_queue_.pop();
  return result;
}
void AbilityManager::checkIfEnemyDestroyed(ShipManager &ship_manager) {
  if (ship_manager.isNewShipDestroyed()) {
    addRandomAbility();
  }
}
void AbilityManager::addAbility(AbilityManager::AbilityType ability) {
  abilities_queue_.push(ability);
}

nlohmann::json AbilityManager::serialize() const {
  nlohmann::json j;
  std::vector<int> abilities_vector;

  // Преобразуем очередь в вектор для сериализации
  std::queue<AbilityType> temp_queue = abilities_queue_;
  while (!temp_queue.empty()) {
    abilities_vector.push_back(temp_queue.front());
    temp_queue.pop();
  }

  j["abilities_queue"] = abilities_vector;
  return j;
}

// Десериализация
 AbilityManager AbilityManager::deserialize(const nlohmann::json& json) {
  AbilityManager manager;
  const std::vector<int>& abilities_vector = json.at("abilities_queue").get<std::vector<int>>();

  // Восстанавливаем очередь из вектора
  for (int ability : abilities_vector) {
    manager.abilities_queue_.push(static_cast<AbilityType>(ability));
  }

  return manager;
}
AbilityManager::AbilityType AbilityManager::getAbilityType() {
  return abilities_queue_.front();
}


