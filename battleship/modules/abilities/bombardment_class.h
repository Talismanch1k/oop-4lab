#ifndef BATTLESHIP_MODULES_ABILITIES_BOMBARDMENT_CLASS_H_
#define BATTLESHIP_MODULES_ABILITIES_BOMBARDMENT_CLASS_H_

#include <random>

#include "ability_interface.h"

class Bombardment : public Ability {
 private:
  std::shared_ptr<ShipManager> ship_manager_;
 public:
  Bombardment(std::shared_ptr<ShipManager> ship_manager);
  bool use() override;
};

#endif //BATTLESHIP_MODULES_ABILITIES_BOMBARDMENT_CLASS_H_
