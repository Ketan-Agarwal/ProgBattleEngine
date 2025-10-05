#include "GameState.h"
#include "constants.h"

GameState::GameState(int numPlayers)
    : numPlayers(numPlayers), currentTick(0), gameOver(false)
    {
        grid = new Grid(GRID_WIDTH, GRID_HEIGHT);
    }

GameState::~GameState() {
    delete grid;

    for (Bullet* bullet: bullets) {
        delete bullet;
    }
}



// GameState initializer
void GameState::initialize() {
    
    grid->generateMap();
    const std::vector <Position>& spawnPoints = spawnPoints;

    for (int i = 0; i < numPlayers && i < spawnPoints.size(); i++) {
        Tank tank(i, spawnPoints[i], Direction::N, INITIAL_HP, INITIAL_HP, INITIAL_AP, true, false);
        tanks.push_back(tank);
    }
}

void GameState::processTick() {
    if (gameOver) return;

    currentTick++;

    // process everything
    processActions();

    // TODO: add zone shrink and Logging

    if (getAliveTankCount() <= 1) {
        gameOver = true;
        // TODO: add winner log        
    }
}

bool GameState::isGameOver() const {
    return gameOver;
}

int GameState::getWinnerId() const {
    if (tanks.size() > 1) return -1; // Draw
    for (const Tank& tank : tanks) {
        if (tank.getIsAlive()) {
            return tank.getId();
        }
    }
}

bool GameState::isTankAt(Position& pos) const {
    for (const Tank& tank : tanks) {
        if (tank.getIsAlive() && tank.getPosition() == pos) return true;
    }
    return false;
}

Tank* GameState::getTank (const int& id) {
    for (Tank& tank: tanks) {
        if (tank.getId() == id) {
            return &tank;
        }
    }
    return nullptr;
}

void GameState::updateTankPosition(const int& tankId, const Position& oldPos, const Position& newPos) {
    // TODO: log print
}

int GameState::getAliveTankCount() const {
    int count = 0;
    for (const Tank& tank: tanks) {
        if (tank.getIsAlive()) count++;
    }
    return count;
}

