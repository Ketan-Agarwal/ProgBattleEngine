#ifndef BULLET_H
#define BULLET_H

#include "../utils/enums.h"

class Bullet {
public:
  Bullet(int ownerID, int damage, Position position, BulletRange range,
         Direction direction, int cooldown);

  int getDamage() const;
  BulletRange getRange() const;
  int update();
  Position getPosition() const;

private:
  int ownerID;
  Position position;
  BulletRange range;
  Direction direction;
  int damage;
  int cooldown;
};

#endif
