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

void Tile::setType (TileType newType) {
    type = newType;
    if (newType == TileType::WALL) {
        fogLevel = 0;
        powerUpPresent = false;
    }
}

bool Tile::isWalkable() const {
    return type != TileType::WALL;
}

bool Tile::blocksVision () const {
    if (type == TileType::WALL || fogLevel > 0) {
        return true;
    }
    return false;
}

// Fog management

void Tile::addFog(int amount) {
    fogLevel += amount;
}

void Tile::clearFog() {
    if (fogLevel > 0) fogLevel = 0;
}

void Tile::decrementFog() {
    if (fogLevel > 0) fogLevel--;
}


char Tile::toChar() const {
    if (fogLevel > 0) return 'F';

    switch (type) {
        case TileType::EMPTY:
            return '.';
        case TileType::WALL:
            return '#';
        case TileType::POWERUP:
            return '*';
        case TileType::SPAWN:
            return 'S';
        default:
            return '?';
    }
}