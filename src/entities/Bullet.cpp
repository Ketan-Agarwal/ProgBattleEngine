#include "Bullet.h"

Bullet::Bullet (int ownerID, int damage, Position position, BulletRange range, Direction direction, int cooldown)
: ownerID(ownerID), damage(damage), range(range), position(position), direction(direction), cooldown(cooldown) {}

// TODO: does bullet have a velocity to move or it hits the target instantly?

Position Bullet::getPosition() const {
    return position;
}

int Bullet::getDamage() const {
    return damage;
}

BulletRange Bullet::getRange() const {
    return range;
}
