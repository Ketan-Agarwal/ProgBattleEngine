#include "Tile.h"

Tile::Tile (TileType type, bool powerUpPresent) : type(type), powerUpPresent(powerUpPresent) {
    switch (type) {
        case TileType::EMPTY:
            break;
        case TileType::WALL:
            break;
        case TileType::POWERUP:
            powerUpPresent = true;
            break;
        case TileType::SPAWN:
        break;
        
    }
}

TileType Tile::getType() const {
    return type;
}

