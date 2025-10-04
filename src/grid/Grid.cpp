#include "Grid.h"

Grid::Grid (int width, int height)
    : width(width), height(height) {
        initialize();
    };


// destructor
Grid::~Grid() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            delete tiles[y][x];
        }
    }
}


// iinitializer
void Grid::initialize() {
    tiles.resize(height);
    for (int y = 0; y < height; y++){
        tiles[y].resize(width);
        for (int x = 0; x < width; x++){
            tiles[y][x] = new Tile(TileType::EMPTY);
        }
    }
}


Tile* Grid::getTile(const Position& pos) {
    if (!isValid(pos)) return nullptr;
    return tiles[pos.y][pos.x];
}

const Tile* Grid::getTile(const Position& pos) const {
    if (!isValid(pos)) return nullptr;
    return tiles[pos.y][pos.x];
}


bool Grid::isValid(const Position& pos) const {
    int x = pos.x;
    int y = pos.y;
    return x >= 0 && y >= 0 && x < width && y < height;
}

bool Grid::isWalkable(const Position& pos) const {
    if (!isValid(pos)) return false;
    const Tile* tile = getTile(pos);
    return tile && tile->isWalkable();
}



// set tile type to wall
void Grid::addWall(const Position& pos) {
    if (isValid(pos)) {
        tiles[pos.y][pos.x]->setType(TileType::WALL);
    }
}


// set tile type to spawn point
void Grid::addSpawnPoint(const Position& pos) {
    if (isValid(pos)) {
        tiles[pos.y][pos.x]->setType(TileType::SPAWN);
        spawnPoints.push_back(pos);
    }
}

// clear the grid
void Grid::clear() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles[y][x]->setType(TileType::EMPTY);
            tiles[y][x]->clearFog();
        }
    }

    // clear spawn points
    spawnPoints.clear();
}


void Grid::addFog(const Position& center, int side, int amount) {
    if (!isValid(center) || side<= 0 || amount <= 0) return;


    // square fog
    int radius = side / 2;

    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            Position FogPos;
            FogPos.x = center.x + dx;
            FogPos.y = center.y + dy;

            if (isValid(FogPos)) {
                Tile* tile = getTile(FogPos);
                
                if (tile && tile->getType() != TileType::WALL) {
                    tile->addFog(amount);
                }

            }
        }
    }

}

void Grid::decrementAllFog() {
    // decrement all fog each tick

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles[y][x]->decrementFog();
        }
    }
}



std::vector <std::string> Grid::toStringRepresentation () const {
    std::vector <std::string> result;

    for (int y = 0; y < height; y++) {
        std::string row;
        for (int x = 0; x < width; x++) {
            row += tiles[y][x]->toChar();
        }
        result.push_back(row);
    }
    return result;
}

void Grid::printGrid() const {
    auto representation = toStringRepresentation();
    // TODO: add print 
}


