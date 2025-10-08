#ifndef CONSTANTS_H
#define CONSTANTS_H

// TODO: add grid height and width
const int GRID_HEIGHT = 20;
const int GRID_WIDTH = 20;
const int INITIAL_HP = 300;
// TODO: add initial AP
const int INITIAL_AP = 50;

// TODO: add timeout for bot response
const int TIMEOUT_MS = 50;

const int JUMP_AP_COST = 2;
const int SHOOT_AP_COST = 2;

const int SHORT_BULLET_RANGE = 3;
const int MEDIUM_BULLET_RANGE = 5;
const int LONG_BULLET_RANGE = 8;

// cooldowns

const int SHORT_BULLET_COOLDOWN = 2;
const int MEDIUM_BULLET_COOLDOWN = 3;
const int LONG_BULLET_COOLDOWN = 4;

const int DAMAGE_SCORE = 1;
const int KILL_SCORE = 10;

// TODO: add turnsAlive_SCORE
const double TICKS_ALIVE_MILTIPLIER = 0.5;
const int SURVIVAL_SCORE = 25;
const int PICKUP_SCORE = 5;
const int COLLISION_PENALTY = -5;
const int AP_SPENT_OFFENCE_SCORE = 2;
const int AP_SPENT_UTILITY_SCORE = 1;
const int AP_BANK_SCORE = 3;
const int COMBO_BONUS_SCORE = 15;

// TODO: add power up spawn rate
const int POWERUP_SPAWN_RATE = 15;

const int MAX_AP = 100;

#endif
