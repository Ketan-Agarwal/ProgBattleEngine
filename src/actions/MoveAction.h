#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "./Action.h"

class MoveAction : public Action {
public:
  MoveAction(int tankId, const Direction &direction, int steps);
  bool validate(const GameState &state, const Tank &tank) const override;
  bool execute(GameState &state) override;
  Direction getDirection() const { return direction; }
  int getSteps() const { return steps; }

private:
  Direction direction;
  int steps;

  Position getDirectionVector(Direction dir) const;
};

#endif
