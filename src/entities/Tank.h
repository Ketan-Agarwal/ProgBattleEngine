#ifndef TANK_H
#define TANK_H

#include "enums.h"
#include <string>
#include <unordered_map>

class Tank {
public:

    Tank (const std::string& id, const Position& spawnPosition, Direction facing, int health, int maxHP, int actionPoints, bool isAlive, bool hasDodge);

    const std::string& getId() const { return id; }
    const Position& getPosition() const { return currentPosition; }
    Direction getFacing() const { return facing; }
    int getHealth() const { return health; }
    int getMaxHP() const { return maxHP; }
    int getActionPoints() const { return actionPoints; }
    bool getIsAlive() const { return isAlive; }
    bool getIsBlind() const { return isBlind; }
    
    bool canMove(Direction dir) const;
    bool canJump() const;
    bool canShoot(BulletRange type) const;
    bool canUseFog(int k) const;
    bool canUseStealth(int targetID, int k) const;

    void setPosition(const Position& pos) { currentPosition = pos; }
    void setFacing(Direction dir) { facing = dir; }
    void takeDamage(int amount);
    void heal(int amount);
    void addAP(int amount);
    bool spendAP(int amount);
    void setBlind(bool blind) { isBlind = blind; }
    void die();

    void updateCooldowns();

    bool hasPowerUp(PowerUpType type) const;


    void addDamageDealt(int damage) { damageDealt += damage; }
    void incrementKills() { kills++; }
    void incrementTicksAlive() { ticksAlive++; }
    void incrementPickups() { pickups++; }
    void incrementCollisions() { collisions++; }
    void addAPSpentOffence(int ap) { apSpentOffence += ap; }
    void addAPSpentUtility(int ap) { apSpentUtility += ap; }
    void addComboBonus() { comboBonus++; }
        

    int calculateMatchScore () const;


    // Helper functions

    int getFogStealthAPCost (int k) const {
        return (10 + k) * 3;
    }
    std::string toJSON() const;


private:
    std::string id;
    Position    currentPosition;
    Position    spawnPosition;
    Direction   facing;

    int         health;
    int         maxHP;
    int         actionPoints;

    bool        isAlive;
    bool        isBlind;
    bool        isStealthed;
    int         stealthTarget;
    
    // powerups
    bool        hasDodge;
    bool        hasMirror;
    bool        hasRespawn;

    std::unordered_map <BulletRange, int> bulletCooldowns;
    int         laserCooldown;
    int         fogCooldown;
    int         stealthCooldown;


    // Scoring
    int         damageDealt;
    int         kills;
    int         ticksAlive;
    int         pickups;
    int         collisions;
    int         apSpentOffence;
    int         apSpentUtility;
    int         comboBonus;


};

#endif