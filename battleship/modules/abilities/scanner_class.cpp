#include "scanner_class.h"


Scanner::Scanner(GameField &game_field, int x, int y) : game_field_(game_field), x_(x), y_(y) {}

bool Scanner::use() {
  std::cout << "Scanning" << std::endl;
  for (int dx = 0; dx < scanner_settings::kX; ++dx) {
    for (int dy = 0; dy < scanner_settings::kY; ++dy) {
      if (game_field_.isShipSegment(x_ + dx, y_ + dy)) {
        return true;
      }
    }
  }
  return false;
}