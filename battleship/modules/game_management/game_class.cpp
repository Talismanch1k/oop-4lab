#include "game_class.h"
#include "input/command_handler_class.h"
#include "input/terminal_input_handler_class.h"

Game::Game() {
  startNewGame();
}

void Game::startNewGame() {
  TerminalInputHandler terminal_input_handler(settings::kBindFile);
  std::shared_ptr<ShipManager> manager = std::make_shared<ShipManager>();
  PlayerSettings player_settings;
  GameField field(10, 10, manager, player_settings);
  AbilityManager ability_manager;
  game_state_ = GameState(field, manager, ability_manager, player_settings, true);

  GameRender<ConsoleRender> player_render(game_state_.getPlayerField());
  CommandHandler<TerminalInputHandler> handler(*this, terminal_input_handler);
  player_render.renderPlacementShip();
  while (true) {
    try {
      bool res = handler.processInput();
      if (!res) break;
      player_render.renderShipField();
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
  startNewRound();
  is_game_started_ = true;
}

void Game::saveGame(const std::string &filename) {
  GameSaver saver(&game_state_);
  saver.saveToFile(filename);
}

void Game::loadGame(const std::string &filename) {
  GameSaver saver(&game_state_);
  saver.loadFromFile(filename);
}

void Game::startGameLoop() {
  TerminalInputHandler terminal_input_handler(settings::kBindFile);
  CommandHandler<TerminalInputHandler> handler(*this, terminal_input_handler);
  GameRender<ConsoleRender> player_render(game_state_.getPlayerField());
  GameRender<ConsoleRender> enemy_render(game_state_.getEnemyField());

  while (true) {
    try {
      if (game_state_.isPlayerTurn()) {
        player_render.renderTurn(game_state_.isPlayerTurn());
        bool res = handler.processInput();
        if (!res) break;
        enemy_render.renderField();
      } else {
        computerTurn();
        enemy_render.renderTurn(game_state_.isPlayerTurn());
        player_render.renderField();
      }
      if (checkVictory() == 1) {
        player_render.renderWin(game_state_.isPlayerTurn());
      }
      this->switchTurn();
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
}

void Game::startNewRound() {
  std::vector<int> sizes;
  std::shared_ptr<ShipManager> ship_manager = game_state_.getPlayerShipManager();
  for (int i = 0; i < ship_manager->getShipCount(); ++i) {
    sizes.push_back(ship_manager->getShipByIndex(i)->getLength());
  }
  GameRender<ConsoleRender> player_render(game_state_.getPlayerField());

  game_state_.setEnemyShipManager(std::make_shared<ShipManager>(sizes));
  std::shared_ptr<ShipManager> enemy_manager = game_state_.getEnemyShipManager();
  GameField enemy_field(game_state_.getPlayerField().getWidth(),
                        game_state_.getPlayerField().getHeight(),
                        game_state_.getEnemyShipManager(),
                        game_state_.getPlayerSettings());
  enemy_field.placeShipsRandomly();
  game_state_.setEnemyField(enemy_field);

  game_state_.setIsPlayerTurn(true);
}

void Game::computerTurn() {
  GameField player_field = game_state_.getPlayerField();

  int x = std::rand() % player_field.getWidth();
  int y = std::rand() % player_field.getHeight();
  player_field.attack(x, y);

  game_state_.setPlayerField(player_field);
}
void Game::switchTurn() {
  game_state_.setIsPlayerTurn(!game_state_.isPlayerTurn());
}

bool Game::checkVictory() {
  // Проверяем, уничтожены ли все корабли игрока
  std::shared_ptr<ShipManager> player_manager = game_state_.getPlayerShipManager();
  if (player_manager->countDestroyedShips() == player_manager->getShipCount()) {
    return true;
  }

  std::shared_ptr<ShipManager> enemy_manager = game_state_.getEnemyShipManager();
  // Проверяем, уничтожены ли все корабли компьютера
  if (enemy_manager->countDestroyedShips() == enemy_manager->getShipCount()) {
    return true;
  }

  return 0;
}
bool Game::isGameStarted() {
  return is_game_started_;
}
void Game::attack(int x, int y) {
  bool attack_result = game_state_.getEnemyField().attack(x, y);
}
void Game::placeShip(int size, bool is_vertical, int x, int y) {
  if (is_game_started_)
    throw std::runtime_error("Cannot place ship, game already started");
  GameField player_field = game_state_.getPlayerField();
  std::shared_ptr<ShipManager> ship_manager = game_state_.getPlayerShipManager();
  ship_manager->addShip(Ship(size, is_vertical));
  player_field.placeLastShip(x, y);
  game_state_.setPlayerField(player_field);
}

void Game::useAbility(int x, int y) {
  GameField enemy_field = game_state_.getEnemyField();
  std::shared_ptr<ShipManager> ship_manager = game_state_.getEnemyShipManager();
  PlayerSettings player_settings = enemy_field.getPlayerSettings();
  GameRender<ConsoleRender> player_render(game_state_.getPlayerField());
  AbilityManager::AbilityType type = game_state_.getPlayerAbilityManager().getAbilityType();
  player_render.renderAbility(type,
                              game_state_.getPlayerAbilityManager().useFirstAbility(enemy_field,
                                                                                    ship_manager,
                                                                                    player_settings,
                                                                                    x,
                                                                                    y));
  game_state_.setEnemyField(enemy_field);
  game_state_.setPlayerSettings(player_settings);
}

