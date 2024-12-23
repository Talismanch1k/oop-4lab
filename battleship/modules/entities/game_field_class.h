#ifndef BATTLESHIP_CMAKE_BUILD_DEBUG_GAME_FIELD_CLASS_H_
#define BATTLESHIP_CMAKE_BUILD_DEBUG_GAME_FIELD_CLASS_H_

#include <vector>
#include <iostream>
#include <stdexcept>
#include "ship_manager_class.h"
#include "player_settings.h"

class GameField {
 private:
  struct Cell {
    int cell_status;
    Ship *ship;
    int segment_index;
    Cell();
  };

  PlayerSettings player_settings_;
  std::vector<std::vector<int>> game_field_;
  std::vector<std::vector<Cell>> ship_field_;
  int height_, width_;
//  ShipManager *ship_manager_;
  std::shared_ptr<ShipManager> ship_manager_;
  bool canPlaceShip(int x, int y, int length, bool isVertical);

 public:
  enum CellStatus {
    kUnknown,
    kEmpty,
    kDamaged,
    kDestroyed
  };
  GameField() = default;
  GameField(int width, int height, std::shared_ptr<ShipManager> ship_manager, PlayerSettings &player_settings);
  GameField(const GameField &other);
  GameField(GameField &&other) noexcept;
  GameField &operator=(GameField &&other) noexcept;
  GameField &operator=(const GameField &other);

//  bool placeShip(Ship &ship, int x, int y);
  bool placeShip(int ship_index, int x, int y);
  bool placeLastShip(int x, int y);
  void placeShipsRandomly();

  bool attack(int x, int y);
  bool isShipSegment(int x, int y);
  int getWidth() const;
  int getHeight() const;
  PlayerSettings getPlayerSettings();
  std::vector<std::vector<int>> getGameField() const;
  std::vector<std::vector<Cell>> getShipField() const;

  void displayShipField() const;
  nlohmann::json serialize() const;
  static GameField deserialize(const nlohmann::json& json);
  ~GameField() = default;
};

class ShipPlacementException : public std::runtime_error {
 public:
  ShipPlacementException() : std::runtime_error("Неверное размещение корабля.") {}
};

class OutOfBoundsAttackException : public std::runtime_error {
 public:
  OutOfBoundsAttackException() : std::runtime_error("Атака за пределами поля.") {}
};

class OutOfBoundsActionException : public std::runtime_error {
 public:
  OutOfBoundsActionException() : std::runtime_error("Действие за пределами поля.") {}
};

#endif //BATTLESHIP_CMAKE_BUILD_DEBUG_GAME_FIELD_CLASS_H_
