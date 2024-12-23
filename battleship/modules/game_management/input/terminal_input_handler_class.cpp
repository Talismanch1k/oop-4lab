#include "terminal_input_handler_class.h"

void TerminalInputHandler::setDefaultBindings() {
  key_bindings_['a'] = Command::Type::kAttack;
  key_bindings_['u'] = Command::Type::kUseAbility;
  key_bindings_['p'] = Command::Type::kPlaceShip;
  key_bindings_['q'] = Command::Type::kQuit;
  key_bindings_['s'] = Command::Type::kSave;
  key_bindings_['l'] = Command::Type::kLoad;
  key_bindings_['x'] = Command::Type::kExit;
}

Command::Type TerminalInputHandler::stringToCommand(const std::string &command_str) {
  if (command_str == "attack") return Command::Type::kAttack;
  if (command_str == "use_ability") return Command::Type::kUseAbility;
  if (command_str == "place_ship") return Command::Type::kPlaceShip;
  if (command_str == "save") return Command::Type::kSave;
  if (command_str == "load") return Command::Type::kLoad;
  if (command_str == "quit") return Command::Type::kQuit;
  if (command_str == "exit") return Command::Type::kExit;
  return Command::Type::kUnknown;
}

bool TerminalInputHandler::loadConfig(const std::string &config_path) {
  std::ifstream config_file(config_path);
  if (!config_file.is_open()) { return false; }

  key_bindings_.clear();
  char key_command;
  std::string command;

  while (config_file >> key_command >> command) {
    Command::Type command_type = stringToCommand(command);
    bool key_not_in_table = (key_bindings_.find(key_command) == key_bindings_.end());
    bool command_not_in_table = (reversed_key_bindings_.find(command_type) == reversed_key_bindings_.end());
    if (command_type != Command::Type::kUnknown && key_not_in_table && command_not_in_table) {
      key_bindings_[key_command] = command_type;
      reversed_key_bindings_[command_type] = key_command;
    } else return false;
  }
  return reversed_key_bindings_.size() == Command::Type::kNumberOfCommands;
}
TerminalInputHandler::TerminalInputHandler(const std::string &config_path) {
  if (!loadConfig(config_path))
    setDefaultBindings();
}
Command TerminalInputHandler::getCommand() {
  char key;
  std::cin >> key;

  if (key_bindings_.find(key) != key_bindings_.end()) {
    Command::Type type = key_bindings_[key];

    if (type == Command::Type::kAttack || type == Command::Type::kUseAbility) {
      int x, y;
      std::cin >> x >> y;
      return Command(type, {x, y});
    }
    if (type == Command::Type::kPlaceShip) {
      int size, is_vertical, x, y;
      std::cin >> size >> is_vertical >> x >> y;
      return Command(type, {size, is_vertical, x, y});
    }
    return Command(type, {});
  }
  return Command(Command::Type::kUnknown, {});
}
