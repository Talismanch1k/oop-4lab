#ifndef BATTLESHIP_MODULES_SHIP_CLASS_H_
#define BATTLESHIP_MODULES_SHIP_CLASS_H_

#include <vector>
#include <stdexcept>

#include "../additional/json.hpp"
#include "../settings.h"

class Ship {
 public:
  enum SegmentState {
    kDestroyed,
    kDamaged,
    kIntact
  };
  enum Orientation {
    kVertical,
    kHorizontal
  };
 private:

  int length_;
  bool is_vertical_;
  std::vector<int> segments_;

 public:
  Ship() : segments_(0) {}
  Ship(int length, bool is_vertical);
  Ship(int length, bool is_vertical, std::vector<int>& segments);
  ~Ship() = default;
  int getLength() const;
  bool isVertical() const;
  void setOrientation(bool orientation);
  void takeDamage(int segment_index, int damage);
  int getSegmentState(int segment_index) const;
  bool isDestroyed() const;
  bool operator==(const Ship& other) const;
  nlohmann::json serialize() const;
  static Ship deserialize(const nlohmann::json& json);
};

class IncorrectSegmentIndex : public std::runtime_error {
 public:
  IncorrectSegmentIndex() : std::runtime_error("Неверный индекс сегмента корабля!") {}
};


#endif //BATTLESHIP_MODULES_SHIP_CLASS_H_
