#ifndef ACTION_H
#define ACTION_H

#include "../utils/enums.h"
#include <string>

class GameState;
class Tank;

class Action {

protected:
  ActionType type;
  int tankId;

public:
  Action(ActionType type, const int &tankId) : type(type), tankId(tankId) {}

  virtual ~Action() = default;

  ActionType getType() const { return type; }
  const int &getTankId() const { return tankId; }

  // TODO: add proper validation and execution

  virtual bool validate(const GameState &state, const Tank &tank) const = 0;

  virtual bool execute(GameState &state) = 0;
};

#endif
