// Game Engine 
#include <vector>
#include <math.h>
#include <string>
#include <unordered_map>

const int gridx = 100, gridy = 100;
enum class  TileType        { EMPTY, WALL, POWERUP, SPAWN, OCCUPIED};
enum class  Direction       { N, NW, W, SW, S, SE, E, NE };
enum class  ActionType      { MOVE, SHOOT, JUMP, FOG, STEALTH, IDLE };
enum class  BulletRange     { SHORT, MEDIUM, LONG };
enum class  PowerUpType     { HEALTH, AP, DODGE_BULLETS, MIRROR, RESPAWN };

struct Position { int x, y; }; // define coordinates of any entity;

class Tank {
    public:
        int         id;                 // tank_id
        Position    currentPosition;    // 
        Position    spawnPosition;      // spawn location
        Direction   facing;
        
        // stats
        int         hp;                 // current hp (max: 300)
        int         maxHP;
        int         actionPoints;    // action points it owns
        int         maxAP;

        // state
        bool        isAlive;
        bool        isBlind;
        bool        isStealthed;
        int         stealthTarget;
        
        // powerups
        bool        hasDodge;
        bool        hasMirror;
        bool        hasRespawn;

        // cooldowns
        std::unordered_map <BulletRange, int> bulletCooldowns;
        int         laserCooldown;
        int         fogCooldown;
        int         stealthCooldown;

        // TODO: armor crack??

        // Scoring
        int         damageDealt;
        int         kills;
        int         ticksAlive;
        int         pickups;
        int         collisions;
        int         apSpentOffence;
        int         apSpentUtility;
        int         comboBonus;
          
        void takeDamage (int amount) {          // take damage
            if (hasDodge || !isAlive) return;
            hp -= amount;
            if (hp <= 0) {
                hp = 0;
                isAlive = false;
            }
        }

        bool canUseWeapon (BulletRange type) const {
            return bulletCooldowns.at(type) <= 0;
        }

        void startCooldown (BulletRange type, int ticks) {
            bulletCooldowns[type] = ticks;
        }

        void updateCooldown () {
            for (auto& [type, cooldown] : bulletCooldowns) {
                if (cooldown > 0) cooldown--;
            }
            if (laserCooldown   > 0)  laserCooldown--;
            if (fogCooldown     > 0)  fogCooldown--;
            if (stealthCooldown > 0)  stealthCooldown--;
        }
};


class Move {
    public:
        Position position;
        Direction direction;
};

static Position dirToDelta(Direction d) {
    switch(d) {
        case Direction::N:  return { 0,  1};
        case Direction::NW: return {-1,  1};
        case Direction::W:  return {-1,  0};
        case Direction::SW: return {-1, -1};
        case Direction::S:  return { 0, -1};
        case Direction::SE: return { 1, -1};
        case Direction::E:  return { 1,  0};
        case Direction::NE: return { 1,  1};
    }
    return {0,0};
}

struct BulletConfig {
    BulletRange     range;
    int             damage;
    int             cooldown;

};

class Bullet {
    public:
        int         ownerID;       // who shot the bullet?
        Position    pos;            // position of bullet
        Direction   dir;            // direction of throw
        BulletRange range;          // 0 for short and 1 for long
        int         damage;         // -5 for short and -15 for long
        int         cooldown;       // 3 turns for long 0 for short

        Bullet (int owner, Position p, Direction d, const BulletConfig& config)
            : ownerID(owner), pos(p), dir(d), range(config.range), damage(config.damage), cooldown(config.cooldown) {}
        
};

class PowerUp {
    public:
        PowerUpType type;
        Position    pos;
        int         value;
};

class Action {
    ActionType      type;
    Direction       direction;
    Position        targetPostion;
    int             targetID;
    int             parameter1;
    int             parameter2;

    Action (Position target, int targetID, int p1, int p2)
        : type(ActionType::IDLE), direction(Direction::N),
          targetPostion(target), targetID(targetID), parameter1(p1), parameter2(p2)
          {}


};


// laser is implemented instead of the infinite bullet

class Laser {
    public:
        int         hp;             // -100 for a laser
        int         cooldown;       // 5 turns for the laser
};

class Fog {
    public:
        // Position indicates centre of square and side is the dimension of the square centred at(x,y)
        Position center;
        int side;
        int duration;
        int cost;

        Fog (Position pos, int k, int dur = 5)
            : center(pos), side(k), duration(dur) {}
        
            bool isActive() const { return duration > 0; }
            void tick() {duration--;}


        bool cover (const Position& pos) const { // checks if an enitity is inside the fog
            int dx = std::abs (pos.x - center.x);
            int dy = std::abs (pos.y - center.y);
            return dx <= side/2 && dy <= side/2;
        }
        // Decreases 10*(side+3) action points per use
};

class Spin_top_shot{
        Position position;
        Direction Dir;
        // in all 8 direction fire bullets and -50 hp for all tank hit
};

class GameState {
    public:
        

};

class Game {
    private: 
        std::vector <std::vector<TileType>> grid;
        std::vector <Tank> tanks;
        std::vector <Bullet> bullets;
        std::vector <PowerUp> powerUps;
        std::vector <Fog> fogs;


        // Safe Zone
        Position center;
        int side;
        int shrinkInterval;
        int shrinkAmount;


        
    public:
        int currentTurn;
        // currentTurn represents tick, after all the bots execute their moves then it gets incremented by 1
        bool move(int id, std::string change){
            if(!tanks[id].isAlive) return false;
            Move mv{Game::tanks[id].currentPosition,change};
            Position currentPosition = mv.position; 
            Position delta = dirToDelta(mv.direction);
            Position target {currentPosition.x + delta.x,currentPosition.y + delta.y};

            for(int i = 0; i<gridx; i++){
                for(int j = 0; j<gridy; j++){
                    if(grid[i][j] == TileType::WALL || grid[i][j] == TileType::OCCUPIED) return false;
                }
            }
            tanks[id].currentPosition = target;
            
        }


};

