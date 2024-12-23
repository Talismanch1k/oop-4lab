#include "command_class.h"

#include <utility>

Command::Command(Command::Type type, std::vector<int> args) : type_(type), arguments_(std::move(args))
{}

std::vector<int> Command::getArguments() {
  return arguments_;
}

Command::Type Command::getType() {
  return type_;
}

