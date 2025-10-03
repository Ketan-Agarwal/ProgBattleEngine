#ifndef TILE_H
#define TILE_H

#include "enums.h"

class Tile {
public:
    Tile (TileType type = TileType::EMPTY, bool powerUpPresent);

    TileType getType() const;
    void setType (TileType type);
    bool isWalkable () const;
    bool blocksVision () const;

    bool setPowerUp (bool present)

private:
    TileType type;
    bool powerUpPresent;
};


#endif