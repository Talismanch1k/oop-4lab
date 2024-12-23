#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_FIELD_RENDER_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_FIELD_RENDER_CLASS_H_

#include "../../entities/game_field_class.h"
#include "../../abilities/ability_manager.h"

class ConsoleRender {
 private:
  GameField &game_field_;
 public:
  ConsoleRender(GameField &game_field) : game_field_(game_field) {}
  void renderField();
  void renderWin(bool is_player_turn);
  void renderTurn(bool is_player_turn);
  void renderShipField();
  void renderPlacementShip();
  void renderAbility(AbilityManager::AbilityType type, bool res);
};

#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_FIELD_RENDER_CLASS_H_
