#include "Tank.h"
#include "../utils/constants.h"



Tank::Tank (const int& id, const Position& spawnPosition, Direction facing, int health, int maxHP, int actionPoints, bool isAlive, bool hasDodge)
    : id(id), spawnPosition(spawnPosition), facing(facing), health(health), maxHP(maxHP), actionPoints(actionPoints), isAlive(isAlive), hasDodge(hasDodge) {
        bulletCooldowns[BulletRange::SHORT] = 0;
        bulletCooldowns[BulletRange::MEDIUM] = 0;
        bulletCooldowns[BulletRange::LONG] = 0;
    }


bool Tank::canMove (Direction dir) const {
    // move is free i.e. no action points required
    if (!isAlive) return false;
    return true;

}

bool Tank::canJump() const {
    if (!isAlive) return false;

    if (actionPoints < JUMP_AP_COST) return false;

    return true;
}

bool Tank::canShoot (BulletRange type) const {
    if (!isAlive) return false;
    auto it = bulletCooldowns.find(type);
    if (it != bulletCooldowns.end() && it->second > 0) {
        return false;
    }

    // TODO: is there inventory for bullets or do we get it from AP?


    return true;
}


bool Tank::canUseFog(int k) const {
    if (!isAlive) return false;
    if (k <= 0) return false;
    if (fogCooldown > 0) return false;

    int apCost = getFogStealthAPCost(k);
    if (actionPoints < apCost) return false;

    return true;
    
}

bool Tank::canUseStealth (int targetID, int k) const {
    if (!isAlive) return false;

    // TODO: validate target ID

    // cannot stealth from yourself
    if (targetID == id) return false;

    if (k <= 0) return false;

    if (stealthCooldown > 0) return false;

    int apCost = getFogStealthAPCost(k);
    if (actionPoints < apCost) return false;

    return true;
}


void Tank::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void Tank::heal (int amount) {
    if (!isAlive) return;

    health += amount;

    if (health > getMaxHP()) health = getMaxHP();
}

void Tank::addAP(int amount) {
    actionPoints += amount;
    int maxAP = MAX_AP;
    if (actionPoints > maxAP) {
        actionPoints = maxAP;
    }
}

bool Tank::spendAP(int amount) {
    if (actionPoints - amount < 0) {
        return false;
    }
    actionPoints -= amount;
    return true;
}

void Tank::die() {
    isAlive = false;
    health = 0;
}


// Cooldown Management

void Tank::updateCooldowns(){
    
    for (auto& [type, cooldown] : bulletCooldowns) {
        if (cooldown > 0) cooldown--;
    }
    if (laserCooldown > 0) laserCooldown--;
    if (fogCooldown > 0) fogCooldown--;
    if (stealthCooldown > 0) stealthCooldown--;

}



bool Tank::hasPowerUp(PowerUpType type) const {
    switch (type) {
        case PowerUpType::HEALTH:
        return false;
        case PowerUpType::AP:
        return false;
        case PowerUpType::DODGE_BULLETS:
        return hasDodge;
        case PowerUpType::MIRROR:
        return hasMirror;
        case PowerUpType::RESPAWN:
        return hasRespawn;

        default:
        return false;
    }
}

int Tank::calculateMatchScore () const {
    int score = 0;
    score += kills*KILL_SCORE;
    score += static_cast<int> (ticksAlive * TICKS_ALIVE_MILTIPLIER);
    if (isAlive) score += SURVIVAL_SCORE;
    score += pickups * PICKUP_SCORE;
    score += collisions * COLLISION_PENALTY;
    score += apSpentOffence * AP_SPENT_OFFENCE_SCORE;
    score += apSpentUtility * AP_SPENT_UTILITY_SCORE;
    score += actionPoints * AP_BANK_SCORE;
    score += comboBonus * COMBO_BONUS_SCORE;

    // TODO: if a person kills a person, will there be 300 damage score and 10 kill score? doesn't make sense
    score += damageDealt;

    return score;

}