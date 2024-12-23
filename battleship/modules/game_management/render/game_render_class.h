#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_RENDER_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_RENDER_CLASS_H_
#include "../../entities/game_field_class.h"
#include "../../abilities/ability_manager.h"

template<typename Renderer>
class GameRender {
 private:
  Renderer renderer_;
 public:
  GameRender(GameField &game_field) : renderer_(game_field) {}
  void renderField() {
    renderer_.renderField();
  }
  void renderShipField() {
    renderer_.renderShipField();
  }

  void renderTurn(bool is_player_turn) {
    renderer_.renderTurn(is_player_turn);
  }

  void renderWin(bool is_player_turn) {
    renderer_.renderWin(is_player_turn);
  }

  void renderPlacementShip() {
    renderer_.renderPlacementShip();
  }

  void renderAbility(AbilityManager::AbilityType type, bool res) {
    renderer_.renderAbility(type, res);
  }
};

#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_GAME_RENDER_CLASS_H_
