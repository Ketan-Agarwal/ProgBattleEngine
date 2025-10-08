#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../actions/Action.h"
#include "../entities/Bullet.h"
#include "../entities/Tank.h"
#include "../grid/Grid.h"
#include <vector>

// TODO: add powerups

class GameState {

public:
  GameState(int numPlayers);

  void initialize();
  void processTick();
  bool isGameOver() const;
  int getWinnerId() const;

  Tank *getTank(const int &id);

  const Grid &getGrid() const { return *grid; }

  // Position update
  void updateTankPosition(const int &tankId, const Position &oldPos,
                          const Position &newPos);

  int getCurrentTick() const { return currentTick; }
  int getAliveTankCount() const;
  void update();

  void addTank(const Tank &tank);
  void addBullet(Bullet *bullet);
  const std::vector<Bullet *> &getBullets() const { return bullets; }
  void removeTank(int TankId);
  bool isTankAt(Position &pos) const;

private:
  std::vector<Tank> tanks;
  std::vector<Bullet *> bullets;
  int numPlayers;
  int currentTick;
  bool gameOver;

  Grid *grid;

  // Internal game logic

  void processActions();
};

#endif
