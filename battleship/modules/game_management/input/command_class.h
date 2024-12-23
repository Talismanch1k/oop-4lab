#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_INPUT_COMMAND_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_INPUT_COMMAND_CLASS_H_

#include <string>
#include <vector>

class Command {
 public:
  enum Type {
    kAttack,
    kUseAbility,
    kPlaceShip,
    kSave,
    kLoad,
    kQuit,
    kExit,
    kNumberOfCommands,
    kUnknown,
  };
 private:
  Type type_;
  std::vector<int> arguments_;
 public:
  Command(Type type, std::vector<int> args);
  std::vector<int> getArguments();
  Type getType();
};

#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_INPUT_COMMAND_CLASS_H_
