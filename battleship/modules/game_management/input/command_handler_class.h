#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_COMMAND_HANDLER_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_COMMAND_HANDLER_CLASS_H_

#include "../game_class.h"
#include <stdexcept>
#include "command_class.h"

template<typename InputHandler>
class CommandHandler {
 private:
  Game &game_;
  InputHandler input_handler_;
 public:
  CommandHandler(Game &game, InputHandler &handler) : game_(game), input_handler_(handler) {};
  bool processInput() {
    Command command = input_handler_.getCommand();

    switch(command.getType()) {
      case Command::Type::kAttack: {
        std::pair<int, int> p = parseCoordinates(command);
        int x = p.first, y = p.second;
        game_.attack(x, y);
        break;
      }
      case Command::Type::kUseAbility: {
        std::pair<int, int> p = parseCoordinates(command);
        int x = p.first, y = p.second;
        game_.useAbility(x, y);
        game_.switchTurn();
        break;
      }
      case Command::Type::kPlaceShip: {
        if (game_.isGameStarted()) break;
        std::vector<int> v = parseShip(command);
        int size = v[0], is_vertical = v[1], x = v[2], y = v[3];
        game_.placeShip(size, is_vertical, x, y);
        break;
      }
      case Command::Type::kLoad: {
        game_.loadGame(settings::kSaveFile);
        game_.switchTurn();
        break;
      }
      case Command::Type::kSave: {
        game_.saveGame(settings::kSaveFile);
        game_.switchTurn();
        break;
      }
      case Command::Type::kExit: {
        return false;
        break;
      }
      case Command::Type::kQuit: {
        exit(0);
      }
      default:throw std::runtime_error("Unknown command");
    }
    return true;
  }


  std::pair<int, int> parseCoordinates(Command &command) {
    int x = command.getArguments()[0];
    int y = command.getArguments()[1];
    return std::pair<int, int>(x, y);
  }
  std::vector<int> parseShip(Command &command) {
    return command.getArguments();
  }

};


#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_COMMAND_HANDLER_CLASS_H_
