#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Tile.h"
#include <string>

// TODO: incomplete
class Grid {
public:
    Grid (int width, int height);
    ~Grid();
    int getWidth() const {return width;}
    int getHeight() const {return height; }

    Tile* getTile (const Position& pos);
    const Tile* getTile (const Position& pos) const;


    // validation
    bool isValid (const Position& pos) const;
    bool isWalkable (const Position& pos) const; // checks for a wall at the tile of given position

    void addWall(const Position& pos);
    void addSpawnPoint(const Position& pos);

    const std::vector<Position>& getSpawnPoints () const { return spawnPoints; }

    // TODO: add Map Generation Logic

    void generateMap();
    void clear();



    // TODO: implement line of sight and safe zone logic

    // Fog management

    void addFog (const Position& center, int side, int amount);
    void decrementAllFog();


    // Visualization Logic
    std::vector <std::string> toStringRepresentation () const;
    void printGrid() const;
    
    
    
private:
    int                                 width;
    int                                 height;
    std::vector <std::vector <Tile*>>    tiles;
    std::vector <Position>              spawnPoints;
    
    void initialize();
    // TODO: add update
    void update();
    
};


#endif