#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_STATE_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_STATE_CLASS_H_

#include "../abilities/ability_manager.h"
#include "../entities/game_field_class.h"
#include "../additional/json.hpp"
#include <fstream>
#include <iostream>

class GameState {
 private:
  GameField player_field_;   // Игровое поле
  GameField enemy_field_;   // Игровое поле

  std::shared_ptr<ShipManager> player_ship_manager_; // Менеджер кораблей
  std::shared_ptr<ShipManager> enemy_ship_manager_; // Менеджер кораблей

  AbilityManager player_ability_manager_;
  // Менеджер способностей
  PlayerSettings player_settings_; // Настройки игрока
  bool is_player_turn_;  // Флаг, чей сейчас ход
 public:
  GameField &getPlayerField();
  void setPlayerField(const GameField &player_field);
  GameField &getEnemyField();
  void setEnemyField(const GameField &enemy_field);
  std::shared_ptr<ShipManager> getPlayerShipManager();
  void setPlayerShipManager(std::shared_ptr<ShipManager> player_ship_manager);
  std::shared_ptr<ShipManager> getEnemyShipManager();
  void setEnemyShipManager(std::shared_ptr<ShipManager> enemy_ship_manager);
  AbilityManager &getPlayerAbilityManager();
  void setPlayerAbilityManager(const AbilityManager &player_ability_manager);
  PlayerSettings &getPlayerSettings();
  void setPlayerSettings(const PlayerSettings &player_settings);
  bool isPlayerTurn();
  void setIsPlayerTurn(bool is_player_turn);
  GameState() = default;

  // Конструктор Создания
  GameState(GameField player_field,
            std::shared_ptr<ShipManager> player_ship_manager,
            AbilityManager player_ability_manager, PlayerSettings player_settings,
            bool is_player_turn);

  GameState(GameField player_field, GameField enemy_field,
            std::shared_ptr<ShipManager> player_ship_manager, std::shared_ptr<ShipManager> enemy_ship_manager,
            AbilityManager player_ability_manager, PlayerSettings player_settings,
            bool is_player_turn);

  // Метод для загрузки состояния игры из файла
  nlohmann::json serialize() const;
  void deserialize(const nlohmann::json &json);

  std::ostream &operator<<(std::ostream &output) const;
  std::istream &operator>>(std::istream &input);
};

#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_STATE_CLASS_H_
