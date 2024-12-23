#include "bombardment_class.h"

#include <utility>

Bombardment::Bombardment(std::shared_ptr<ShipManager> ship_manager) : ship_manager_(std::move(ship_manager)) {}

bool Bombardment::use() {
  std::cout << "Boardment" << std::endl;
  int random_id = std::rand() % ship_manager_->getShipCount();
  Ship &ship = ship_manager_->getShip(random_id);
  int random_sector = std::rand() % ship.getLength();
  ship.takeDamage(random_sector, 1);
  return true;
}