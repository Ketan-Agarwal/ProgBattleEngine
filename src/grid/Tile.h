#ifndef TILE_H
#define TILE_H

#include "../utils/enums.h"

class Tile {
public:
  Tile(TileType type = TileType::EMPTY, bool powerUpPresent = false);

  TileType getType() const;
  void setType(TileType type);
  bool isWalkable() const;
  bool blocksVision() const;

  // Fog management
  void addFog(int amount);
  void clearFog();
  void decrementFog();

  void setPowerUp(bool present) { powerUpPresent = present; }
  char toChar() const;

private:
  TileType type;
  bool powerUpPresent; // if a tile has powerup aka is tiletype == powerup
  int fogLevel;        // decrements each tick
};

#endif
