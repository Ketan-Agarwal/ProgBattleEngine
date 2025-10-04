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
    
}