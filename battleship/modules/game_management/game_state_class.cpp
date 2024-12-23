#include "game_state_class.h"

#include <utility>
GameState::GameState(GameField player_field, GameField enemy_field,
                     std::shared_ptr<ShipManager> player_ship_manager, std::shared_ptr<ShipManager> enemy_ship_manager,
                     AbilityManager player_ability_manager, PlayerSettings player_settings,
                     bool is_player_turn)
    : player_field_(std::move(player_field)),
      enemy_field_(std::move(enemy_field)),
      player_ship_manager_(std::move(player_ship_manager)),
      enemy_ship_manager_(std::move(enemy_ship_manager)),
      player_ability_manager_(std::move(player_ability_manager)),
      player_settings_(player_settings),
      is_player_turn_(is_player_turn) {}

GameState::GameState(GameField player_field,
                     std::shared_ptr<ShipManager> player_ship_manager,
                     AbilityManager player_ability_manager, PlayerSettings player_settings,
                     bool is_player_turn)
    : player_field_(player_field),
      enemy_field_(player_field),
      player_ship_manager_(player_ship_manager),
      enemy_ship_manager_(player_ship_manager),
      player_ability_manager_(std::move(player_ability_manager)),
      player_settings_(player_settings),
      is_player_turn_(is_player_turn) {

  std::vector<int> sizes;
  std::shared_ptr<ShipManager> ship_manager = player_ship_manager_;
  for (int i = 0; i < ship_manager->getShipCount(); ++i) {
    sizes.push_back(ship_manager->getShipByIndex(i)->getLength());
  }

  PlayerSettings enemy_settings;
  enemy_ship_manager_ = std::make_shared<ShipManager>(ShipManager(sizes));
  enemy_field_ = GameField(player_field.getWidth(), player_field.getHeight(), enemy_ship_manager_, enemy_settings);
  enemy_field_.placeShipsRandomly();
}

nlohmann::json GameState::serialize() const {
  nlohmann::json j;
  j["player_field"] = player_field_.serialize();
  j["enemy_field"] = enemy_field_.serialize();
  j["player_ship_manager"] = player_ship_manager_->serialize();
  j["enemy_ship_manager"] = enemy_ship_manager_->serialize();
  j["player_ability_manager"] = player_ability_manager_.serialize();
  j["player_settings"] = player_settings_.serialize();
  j["is_player_turn"] = is_player_turn_;
  return j;
}

// Метод десериализации
void GameState::deserialize(const nlohmann::json &json) {
  player_ship_manager_ = std::make_shared<ShipManager>(ShipManager::deserialize(json["player_ship_manager"]));
  enemy_ship_manager_ = std::make_shared<ShipManager>(ShipManager::deserialize(json["enemy_ship_manager"]));
  player_field_ = GameField::deserialize(json["player_field"]);
  enemy_field_ = GameField::deserialize(json["enemy_field"]);
  player_ability_manager_ = AbilityManager::deserialize(json["player_ability_manager"]);
  player_settings_ = PlayerSettings::deserialize(json["player_settings"]);
  is_player_turn_ = json["is_player_turn"].get<bool>();
}

std::ostream &GameState::operator<<(std::ostream &output) const {
  nlohmann::json j = this->serialize();
  output << j.dump(2);  // Записываем JSON в поток с отступами (4 пробела)
  return output;
}
std::istream &GameState::operator>>(std::istream &input) {
  nlohmann::json j;
  input >> j;
  this->deserialize(j);  // Преобразуем из JSON в объект GameState
  return input;
}
GameField &GameState::getPlayerField() {
  return player_field_;
}
void GameState::setPlayerField(const GameField &player_field) {
  player_field_ = player_field;
}
GameField &GameState::getEnemyField(){
  return enemy_field_;
}
void GameState::setEnemyField(const GameField &enemy_field) {
  enemy_field_ = enemy_field;
}
std::shared_ptr<ShipManager> GameState::getPlayerShipManager(){
  return player_ship_manager_;
}
void GameState::setPlayerShipManager(std::shared_ptr<ShipManager> player_ship_manager) {
  player_ship_manager_ = std::move(player_ship_manager);
}
std::shared_ptr<ShipManager> GameState::getEnemyShipManager(){
  return enemy_ship_manager_;
}
void GameState::setEnemyShipManager(std::shared_ptr<ShipManager> enemy_ship_manager) {
  enemy_ship_manager_ = std::move(enemy_ship_manager);
}
AbilityManager &GameState::getPlayerAbilityManager()  {
  return player_ability_manager_;
}
void GameState::setPlayerAbilityManager(const AbilityManager &player_ability_manager) {
  player_ability_manager_ = player_ability_manager;
}
 PlayerSettings &GameState::getPlayerSettings()  {
  return player_settings_;
}
void GameState::setPlayerSettings(const PlayerSettings &player_settings) {
  player_settings_ = player_settings;
}
bool GameState::isPlayerTurn() {
  return is_player_turn_;
}
void GameState::setIsPlayerTurn(bool is_player_turn) {
  is_player_turn_ = is_player_turn;
}
