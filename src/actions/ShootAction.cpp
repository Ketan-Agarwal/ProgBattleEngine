#include "./ShootAction.h"
#include "../core/GameState.h"
#include "../entities/Tank.h"
#include "../utils/constants.h"
#include "Action.h"
ShootAction::ShootAction(int tankId, const Direction &direction,
                         BulletRange range)
    : Action(ActionType::SHOOT, tankId), direction(direction), range(range) {}

bool ShootAction::validate(const GameState &state, const Tank &tank) const {
  if (!tank.canShoot(range))
    return false;

  int apCost = getAPCost(range);
  if (apCost > tank.getActionPoints())
    return false;

  if (tank.getBulletCooldown(range) > 0)
    return false;

  // TODO: add validation for line of sight / visibility
  //
  return true;
}

bool ShootAction::execute(GameState &state) {
  Tank *tank = state.getTank(tankId);

  if (!tank)
    return false;

  if (!validate(state, *tank))
    return false;

  Position bulletPos =
      (Position)tank->getPosition() + (Position)getDirectionVector(direction);

  int damage = getBulletDamage(range);
  BulletRange range = getRange();

  Bullet *bullet = new Bullet(tankId, damage, bulletPos, range, direction,
                              getBulletCooldown(range));

  state.addBullet(bullet);

  int apCost = getAPCost(range);
  tank->spendAP(apCost);

  tank->setBulletCooldown(range);

  tank->setFacing(direction);

  // TODO: log the shot in console?

  return true;
}

// Helper Functions

int ShootAction::getBulletCooldown(BulletRange range) const {
  switch (range) {
  case BulletRange::SHORT:
    return SHORT_BULLET_COOLDOWN;
  case BulletRange::MEDIUM:
    return MEDIUM_BULLET_COOLDOWN;
  case BulletRange::LONG:
    return LONG_BULLET_COOLDOWN;
  }
}

int ShootAction::getBulletRange() const {
  switch (range) {
  case BulletRange::SHORT:
    return SHORT_BULLET_RANGE;
  case BulletRange::MEDIUM:
    return MEDIUM_BULLET_RANGE;
  case BulletRange::LONG:
    return LONG_BULLET_RANGE;
  }
}
