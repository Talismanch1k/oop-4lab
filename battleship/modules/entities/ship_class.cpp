#include "ship_class.h"

Ship::Ship(int length, bool is_vertical = false) {
  if (length >= 0 && length <= settings::kShipMaxLength) {
    length_ = length;
  } else throw std::runtime_error("Size bigger than max");
  is_vertical_ = is_vertical;
  segments_ = std::vector<int>(length, kIntact);
}

int Ship::getLength() const {
  return length_;
}

bool Ship::isVertical() const {
  return is_vertical_;
}

void Ship::takeDamage(int segment_index, int damage = 1) {
  if (segment_index >= 0 && segment_index <= length_) {
    segments_[segment_index] = std::max(segments_[segment_index] - damage, 0);
  } else throw IncorrectSegmentIndex();
}

int Ship::getSegmentState(int segment_index) const {
  if (segment_index >= 0 && segment_index <= length_) {
    return segments_[segment_index];
  }
  throw IncorrectSegmentIndex();
}

bool Ship::isDestroyed() const {
  // TODO: replace all_of
  for (const auto &segment : segments_) {
    if (segment != kDestroyed) {
      return false;
    }
  }
  return true;
}
void Ship::setOrientation(bool orientation) {
  if (orientation == kVertical) is_vertical_ = true;
  else is_vertical_ = false;
}

bool Ship::operator==(const Ship& other) const {
  return length_ == other.length_ &&
      is_vertical_ == other.is_vertical_ &&
      segments_ == other.segments_;
}

nlohmann::json Ship::serialize() const {
  nlohmann::json json;
  json["length"] = length_;
  json["is_vertical"] = is_vertical_;
  json["segments"] = segments_;
  return json;
}

// Функция десериализации Ship
Ship Ship::deserialize(const nlohmann::json& json) {
  int length = json.at("length").get<int>();
  bool is_vertical = json.at("is_vertical").get<bool>();
  std::vector<int> segments = json.at("segments").get<std::vector<int>>();
  return Ship(length, is_vertical, segments);
}
Ship::Ship(int length, bool is_vertical, std::vector<int>& segments) {
  if (length >= 0 && length <= settings::kShipMaxLength) {
    length_ = length;
  }
  is_vertical_ = is_vertical;
  segments_ = segments;
}




