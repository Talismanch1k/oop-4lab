#ifndef BATTLESHIP_MODULES_SHIP_MANAGER_CLASS_H_
#define BATTLESHIP_MODULES_SHIP_MANAGER_CLASS_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include "ship_class.h"

class ShipManager {
 private:
  std::vector<Ship> ships_;
  int ships_destroyed_ = 0;
 public:
  ShipManager() : ships_(0) {}
  explicit ShipManager(const std::vector<int> &shipSizes);
  Ship &getShip(int index);
  int getShipCount() const;
  int countDestroyedShips() const;
  void updateDestroyedShips(int count);
  bool isNewShipDestroyed();
  void displayShips() const;
  Ship *getShipByIndex(int index);
  int getShipIndex(const Ship* ship) const;
  ~ShipManager() = default;
  nlohmann::json serialize() const;
  static ShipManager deserialize(const nlohmann::json& json);
  void addShip(const Ship& ship);

};

#endif //BATTLESHIP_MODULES_SHIP_MANAGER_CLASS_H_
