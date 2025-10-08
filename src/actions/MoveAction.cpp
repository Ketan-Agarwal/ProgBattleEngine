#include "MoveAction.h"
#include "../core/GameState.h"
#include "../entities/Tank.h"
#include "../utils/constants.h"

MoveAction::MoveAction(int tankId, const Direction &direction, int steps)
    : Action(ActionType::MOVE, tankId), direction(direction), steps(steps) {}

bool MoveAction::validate(const GameState &state, const Tank &tank) const {

  // if tank says it cannot move. fair.
  if (!tank.canMove(direction)) {
    return false;
  }

  Position currentPos = tank.getPosition();
  Position dirVec = getDirectionVector(direction);
  Position newPos = currentPos + dirVec;

  if (!state.getGrid().isValid(newPos) || !state.getGrid().isWalkable(newPos))
    return false;

  // TODO: handle tank collisions
  //      currently tanks cannot collide

  if (state.isTankAt(newPos)) {
    return false;
  }

  return true;
}

bool MoveAction::execute(GameState &state) {
  Tank *tank = state.getTank(tankId);

  if (!tank || !validate(state, *tank))
    return false;

  Position oldPos = tank->getPosition();
  Position newPos = oldPos + getDirectionVector(direction);

  tank->setPosition(newPos);
  tank->setFacing(direction);

  state.updateTankPosition(tankId, oldPos, newPos);

  return true;
}

// helper functions

Position MoveAction::getDirectionVector(Direction dir) const {
  switch (dir) {
  case Direction::N:
    return Position(0, 1);
  case Direction::E:
    return Position(1, 0);
  case Direction::W:
    return Position(-1, 0);
  case Direction::S:
    return Position(0, -1);
  case Direction::NW:
    return Position(-1, 1);
  case Direction::NE:
    return Position(1, 1);
  case Direction::SW:
    return Position(-1, -1);
  case Direction::SE:
    return Position(1, -1);
  }
}
