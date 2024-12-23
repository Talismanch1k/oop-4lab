#ifndef BATTLESHIP_MODULES_GAME_MANAGEMENT_TERMINAL_INPUT_HANDLER_CLASS_H_
#define BATTLESHIP_MODULES_GAME_MANAGEMENT_TERMINAL_INPUT_HANDLER_CLASS_H_

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

#include "command_class.h"

// Класс обработки ввода из терминала
class TerminalInputHandler {
  std::unordered_map<char, Command::Type> key_bindings_;
  std::unordered_map<Command::Type, char> reversed_key_bindings_;
 public:
  TerminalInputHandler(const std::string& config_path);
  Command getCommand();

 private:
  bool loadConfig(const std::string& configFilePath);
  void setDefaultBindings();
  Command::Type stringToCommand(const std::string &command_str);
};


#endif //BATTLESHIP_MODULES_GAME_MANAGEMENT_TERMINAL_INPUT_HANDLER_CLASS_H_
