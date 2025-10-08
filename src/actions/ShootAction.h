#ifndef SHOOT_ACTION_H
#define SHOOT_ACTION_H

#include "Action.h"

class ShootAction : public Action {

private:
  Direction direction;
  BulletRange range;

public:
  ShootAction(int tankId, const Direction &direction, BulletRange range);

  bool validate(const GameState &state, const Tank &tank) const override;
  bool execute(GameState &state) override;

  Direction getDirection() const { return direction; }
  BulletRange getRange() const { return range; }

  int getBulletRange() const;

private:
  const Position getDirectionVector(Direction dir) const;
  int getBulletDamage(BulletRange range) const;
  int getBulletCooldown(BulletRange range) const;
  int getAPCost(BulletRange range) const;
};

#endif
