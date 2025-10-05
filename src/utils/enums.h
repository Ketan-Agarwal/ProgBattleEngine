enum class  TileType        { EMPTY, WALL, POWERUP, SPAWN, OCCUPIED};
enum class  Direction       { N, NW, W, SW, S, SE, E, NE };
enum class  ActionType      { MOVE, SHOOT, JUMP, FOG, STEALTH, IDLE };
enum class  BulletRange     { SHORT, MEDIUM, LONG };
enum class  PowerUpType     { HEALTH, AP, DODGE_BULLETS, MIRROR, RESPAWN };

// struct Position { int x, y; }; // define coordinates of any entity;

class Position {
public:
    int x;
    int y;

    Position () : x(0), y(0) {}
    Position (int x, int y) : x(x), y(y) {}

    Position operator+(const Position& other) {
        return Position(x+other.x, y+other.y);
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};