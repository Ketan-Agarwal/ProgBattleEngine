

---
# ProgBattle Game Design

Doc contains a basic game idea for now, will keep updating this time to time

---

Grid‑based tank shooter with multiple strategies:

* **Match ground**: 2D square grid.
* **Match Style**: All actions in sync i.e tick‑based (one action per tick).
* **Timeout**: 500 ms response time per turn (inlcuding everything required in one move)
 
Bots submit one action each tick; if no valid response is received within a set timeout time, a default `previous move` would be applied irrespective of whether they loose points or gain points.
(About timeout and match style, I read the doc of [battlesnake](https://play.battlesnake.com), so they are tentative)

Suppose at the start, there is no move taken, then `previous move`  will be taken as `forward`.

`previous move`  only includes moving in that direction, upon hitting a boundary, if the bot is unresponsive, ``reflect back`` would be used.

---

## Grid and Tiles

* **Dimensions**: Something between a $20 \times 20$ and $30 \times 30$ grid. It will help ensure that there is a good balance between close range and mid range play and thus enough room for fog and other stealth tactics. Though will need to ensure that number of powerups are sufficent so that the board doesn't look sparse. 
* **Tiles**:

  * `.` Empty
  * `#` Wall (blocks movement & vision)
  * `*` Special power-up (health, ammo, special)
  * `P` Spawn point
  
* Visibility would be fixed, before every move, a tank will have the locations of the tank in its visibility, and which way they are facing. 
* **Spawn**: Symmetric positioning (fairness)
Also could shrink the map eventually like Pub-g to accelerate endings.
(could also notify the tank about nearby tank resources or previous moves used)

---

## Tank Properties

* **Health**: Some fixed HP say 300 for now (subject to change)
* **Ammo**: Varies by weapon type; can collect ammo at special power-up points
* **Cooldowns**: Each weapon/action has its own cooldown timer in ticks
* **Blind** : Any tank can block a tanks vision, so a boolean whether it can have access to the tanks nearby.
* **FP** : Fog Power (further details in the table)
* **Direction** : Which direction is the tank facing


Clarifications about **Blind**: 
Before making its move, a tank checks whether it is **blinded**.

* If `blind = true`, it **does not receive any information** about nearby tanks and must act based on **incomplete knowledge**, considering multiple possible scenarios.
* If `blind = false`, it receives **full information** about surrounding tanks and can make decisions accordingly.

Tanks can strategically **blind their opponents**, forcing them to act without full visibility basically gaining a good advantage.


---


## Action Points (AP)
* **Action Points (AP)** function as a shared resource that your tank uses each turn. Except for free moves like MOVE or PASS, AP is utilized when performing more impactful actions, effectively regulating powerful plays instead of relying on individual cooldown timers for each action. Initially the users can be provided with 100 AP (subject to change)
* With AP: You might have only 3 AP in a turn, so you can choose : 1 MOVE (1 AP) + 1 SHOOT (2 AP), or 1 JUMP (2 AP) + 1 PASS (0 AP) + save 1 AP for next turn, or 1 FOG (3 AP, no move this turn). 
* **Dynamic Pacing**: Early in the match, tanks may be cautious—“banking” AP to unleash a multi‑AP combo later (e.g. JUMP + SPIN‑TOP + FOG). Late‑game, if you’re low on HP, you’re more likely to spend your AP immediately on evasive moves (MOVE) or a last‑ditch STEALTH, rather than hoard it.
---


## Idea of Shrinking Game Zone

* **Positional Trade-Offs :** Bots need to balance maintaining a strong position now versus the risk of moving late to stay within the safe zone. Saving action points (AP) and resources early can be wasted if caught outside the ring.
* **Prevents Camping** Without a time‑pressure mechanic, bots can simply hole up behind walls and wait out opponents. A shrinking boundary forces them to move, increasing encounters.
* **Time of shrinking** shrink the game zone every 20 ticks by 2 rows maybe and final death zone be set to maybe a $6\times 6$ grid gearing up for a dramatic finish.
---


## Actions

On each turn, a bot chooses **one** action:

| Category    | Action               | Description                                                                     | Cooldown/Cost            |
| ----------- | -------------------- | ------------------------------------------------------------------------------- | ------------------------ |
| **Move**    | `MOVE <U/D/L/R>`     | Step one tile up/down/left/right.                                               | Available at all turns.                     |
| **Jump**    | `JUMP <dx> <dy>`     | Leap two tiles in chosen direction. Bypasses any obstacles and other tanks   | 2 AP          |
| **Shoot**   | `SHOOT <type> <dir>` | Fire a bullet of given type in one of 8 directions (or infinite-range special). | See bullet types (uses AP again)        |
| **Fog**     | `FOG <x> <y> <k>`    | Cast stackable fog onto the $k	\times k$ square centred at (x,y).                | Uses $(10+k)\times 3$ AP |
| **Stealth** | `STEALTH <targetID>` | Hide from target tank within radius $R$ for next 2 turns.                       |  Uses $(10+k)\times 3$ AP         |
| **Idle**    | `IDLE`               | Do nothing (skip turn).                                                         | —                        |

---

## Power-ups/ Collectibles:
Power-ups will spawn randomly at grid  $x$  per tick. It will be reduced to  per tick, if the current map area is halved from the original. 

(will be adding a proper function based on number of tanks, number of power-ups already placed, relative grid size)

1. **Health packet**: Increases HP by x.(Infrequent)
2. **AP packet**: Increases AP by y.(Infrequent)
3. **Dodge bullets**: No bullets will attack for 2/3 turns(Common)
4. **Mirror**: Instantly used, reflects any bullets that comes(Common)
5. **Respawn**: instantly used in the next turn. Good combo for "Nuke Farthest"(Rare)


**Respawn:**
This is an instantly-activated power-up. When a tank steps onto a cell containing `Respawn`, it can **teleport to any location on the grid**.

This power-up can be tactically combined with abilities like **`Nuke Farthest`**, which deals heavy damage to all enemy tanks that are at the **maximum distance** from the user. By choosing a respawn location such that **multiple enemies are equally far**, the tank can **strike all of them at once**, turning `Nuke Farthest` into a powerful area attack and gaining a significant tactical advantage.

**Mirror:**
This is an instantly-used defensive power-up, not meant for long-term planning. When a tank picks it up, it **automatically reflects any bullets fired at it in that turn**, saving it from damage.

The strategy comes in while **firing at others**. You need to consider if the enemy has `Mirror`, and your bullet's `damage` is more than your own `HP`, then **you'll end up dying instead**.

**Dodge Bullets:**
When a tank picks this up, **it becomes untargetable by bullets** for the next **2 or 3 turns** (randomly decided).

* Bullets already in motion will **still hit** if they were fired **before** the pickup.
* **New bullets** fired **after** the pickup will **ignore** the tank for the duration.
* The bullet will simply ignore the tank, and wouldn't stop at that location.



---
## Damaging tanks

### 1. Bullets

Bullets have two main parameters:

* **Range**: Maximum tiles the bullet travels before disappearing.
* **Speed**: Tiles traveled per tick.

>  If `speed * remaining_ticks > range`, the bullet will stop once traveling its maximum range, even if its speed would allow further movement.

| Type     | Range (tiles) | Speed (tiles/tick) | Cooldown | Damage |
| -------- | ------------- | ------------------ | -------- | ------ |
| Short    | 3             | 3                  | 2 ticks  | 5 HP  |
| Medium   | 5             | 5                  | 3 ticks  | 10 HP  |
| Long     | 8             | 4                  | 4 ticks  | 15 HP  |
| Infinite | ∞             | 2                  | 10 ticks | 20 HP  |

* Bullets move at their **speed** each tick, up to their **range**. Walls and fog block bullets.
* On hitting a tank: bullet disappears and deals damage.

### 2. Tank Collisions

1. If **two tanks** move into the **same tile** on the same tick: both lose 20% of their current HP (i.e.20 HP). But if the HP is less than some threshold, they will immediately die.
(maybe this idea is quite bad so not tentative either)
2.  Maybe we can resolve collisions like battlesnake by maintaining some counter, if more then that tank survives else dies. But for multiple users, the collisions might be frequent. And instead we can add points for having collisions instead of killing instantly.
3.  Another idea is that collisions don’t deal direct HP damage, instead they “crack” your armor layer. After N cracks (e.g. 3), your next shot or hit does +50% damage. It can add a strategic buildup and can help the players to set up a big finish after the required number of collision. (not very sure about this..might be complex to implement..also further need to define collision..head on head or head to back..need further suggestions on this!)
---

## Special Moves

| Ability           | Description                                                                                          | Cooldown/Cost                                    |
| ----------------- | ---------------------------------------------------------------------------------------------------- | ------------------------------------------------ |
| **Spin‑Top Shot** | Shoot medium-range bullets simultaneously in all 8 directions.(N,S,E,W,NE,NW,SE,SW)                                       | 15 turn cooldown,15 AP; damage 50 AP          |
| **Mine**          | Place a timed mine on current tile; explodes after `t` ticks (player-set, max 5 ticks).              | Costs some `points` to set timer; radius also using points|
| **Freeze Self**   | Skip your next move to double next-turn cooldown reduction for all weapons.                          | (not very sure about this either)              |
| **Nuke Farthest** | Damage the farthest tank(s) on the map by fixed amount. If multiple share max distance, all are hit. | 10 AP, damage 50 HP 
| **Read others** | Copy the JSON data that someone is supposed to receive in the next turn | 15 turn cooldown, 20 AP
* Nuke farthest would be interesting, like for 3 users, someone might try to be in their perpendicular bisector somehow. We could change this to nuke all tanks in range [max_distance - s, max_distance], keeping s small. like of 1/10th or 1/20th order of max_distance
* Mine: Can use AP as currency to use mine, and set timer and radius. Will keep a max cap for both timer and radius.
* Freeze Self: Could possibly also add, freeze others, but the move will still stack, so that there are both pros and cons of using it (again a slightly rudimentary idea needs further refinement)

---

## Scoring

There will be two kinds of score: Match Score and Placement Score. Match Score is obtained during a match and Placement Score is the score based on the final rankings after one match is over,

$$
\begin{aligned}
\text{Match Score} = \\
&+ (\text{Damage Dealt}) \\
&+ 10·(\text{kills}) \\
&+ 0.5·(\text{turnsAlive}) \\
&+ 25·(\text{aliveAtEnd ? 1 : 0}) \\
&+ 5·(\#healthPickups) \\
&+ 3·(\#ammoPickups) \\
&+ 3·(\#dodgePickups) \\
&− 5·(\#collisions) \\
&+ 2·(\text{AP_spent_offence}) \\
&− 1·(\text{AP_spent_utility}) \\
&+ 3·(\text{AP_bank_at_end}) \\
&+ 15·(\text{ComboBonus}) \\
\end{aligned}
$$

- `AP_spent_offence` – AP used on actions that can damage or kill (Shoot, Spin-Top, Nuke, Mine, etc.)
- `AP_spent_utility` – AP used on purely tactical or defensive moves (Fog, Stealth, Jump, …)
- `AP_bank_at_end` – AP you still hold when the game ends (max 12 counted, anything above is ignored)
- `ComboBonus` is 1 whenever you spend ≥4 AP in a single turn and hit at least one enemy that same tick. 
- The weights of each term can be changed later.  

$$
\begin{aligned}
\text{Placement Score} = \\
\text{1st Position}\quad -\quad \text{Depends on the Round} \\
\text{2nd Position}\quad -\quad \text{Depends on the Round} \\
\text{2nd Position}\quad -\quad \text{Depends on the Round} \\
\end{aligned}
$$

- Placement score makes winning still matters most.

Also the weights in the score fucnction can be set variable as levels progress so that the user optimise their actions depending on the maximum weight in score calculation variable. (again needs to be worked upon..can be implemented in the higher levels of the game)

**Per-turn**:

1. Decide action (move, shoot types, jump, etc.).
2. **Compute game scores** for each action (distance-to-enemies, cover, pickups, cooldown status, etc.).
3. **Respond** with chosen action JSON under 500 ms.

---

### What will happen every move

* **Info a user will get before moving**:

  ```json
  {
    "turn": 42,
    "info": {"x": 5, "y": 10, "hp": 80, "ammo": {...}, "cooldowns": {...}},
    "visibleTanks": [ {"id":1, "x":3, "y":7, "hp":100}, ... ],
    "visible_speical_points": [ {"type":"health", "x":4, "y":9}, ... ],
    "grid_current_state": ["................", "..##......##....", ...]
  }
  ```
* **Response** (JSON) within timeout

  ```json
  { "action": "MOVE", "direction": "UP" }
  ```

> If the response is missing or invalid by 500 ms, then automatically applies `previous move` by default irrespective if it gains points or looses

---

### Game Start

* **Initial view :** At tick 0, each player receives two things, the full board layout with the location of all the powerups, walls and empty spaces and its own info block containing information regarding its HP,AP,powerups,etc.
* As the game progresses the bots move according to the tick timeout and the game proceeds according to the rules mentioned above in the doc. As soon as the HP drops to 0, the bot is eliminated.
---
### Game End

* **End conditions :** The game ends when there is only one tank remaining, i.e. the last tank standing. If all the tanks are eliminated outside of the final game zone then the last tank to be eliminated is the winner.
* **Final Game broadcast :** each bot is sent its final position, HP bank, AP bank and other end of game stats.
* **Leaderboard updation :** the final leaderboard is updaed on the basis of the placement scores of the bots.
* **Cleanup** deallocate the memory for theemap and per-match data
---

## Tournament Structure

### Round 0 (Checking)

|      | Setting                                                                |
|-----------|------------------------------------------------------------------------|
| Purpose   | Make sure each bot can parse input, act within 500 ms, and shoot once. |
| Map       | 10 × 10 empty grid, 1 stationary dummy.                                |
| Duration  | 5 ticks        |

All players advance to the next round. Score is not counted.

### Round 1 (Player vs AI)

|         |Setting                                                 |
|------------------|--------------------------------------------------------|
|Number of Matches       | 5            |
| Opponents        | 4 scripted tanks that only MOVE and SHOOT.             |
| Map              | 20 × 20 with few walls.                       |
| Win Condition    | Destroy all bots **or** survive 60 ticks.              |

Top 70% of the players advance to the next round.

### Round 2 (Player vs Player)

|       | Setting                                                      |
|------------------|--------------------------------------------------------------|
|Number of Matches       | $^xC_4$ where $x$ is the number of players left.           |
| Groups            | Players grouped into groups of four.          |
| Map              | 20 × 20 symmetrical arena; no shrinking zone.                |
| Tick Cap         | 120 ticks; last tank standing wins, else most HP wins.       |

Top 25% of the players move to next and final round.

### Round 3 (Grand Finale)
| | Setting                                                                              |
|--------------|---------------------------------------------------------------------------------------|
|Number of Matches       | $^xC_8$ where $x$ is the number of players left.           |
| Groups | Players grouped into groups of 8                                                               |
| Map          | 25 × 25; ring begins shrinking by 2 tiles every 25 ticks after tick 75.               |
| Victory      | After all matches, the top 8 players play the final match to decide the winner.                                                                   |

### Final Winners
1st, 2nd, 3rd based purely on survival order of the last match of last round irrespective of the previous points obtained. 

### Overall Leaderboard

Everyone participating in a match earns points based on the match (Match Points) and on their final rank in each match(Placement Points). For each round:

* Everyone match in Round 1: Earn

  $$
\begin{aligned}
\text{Placement Score} = \\
\text{1st Position}\quad -\quad \text{100 pts} \\
\text{2nd Position}\quad -\quad \text{40 pts} \\
\text{2nd Position}\quad -\quad \text{20 pts} \\
\end{aligned}
$$
* Everyone match in Round 2: Earn

  $$
\begin{aligned}
\text{Placement Score} = \\
\text{1st Position}\quad -\quad \text{200 pts} \\
\text{2nd Position}\quad -\quad \text{80 pts} \\
\text{2nd Position}\quad -\quad \text{40 pts} \\
\end{aligned}
$$
* Everyone match in Round 3: Earn

  $$
\begin{aligned}
\text{Placement Score} = \\
\text{1st Position}\quad -\quad \text{400 pts} \\
\text{2nd Position}\quad -\quad \text{300 pts} \\
\text{2nd Position}\quad -\quad \text{200 pts} \\
\end{aligned}
$$

* Note: No points are awarded for rounds a bot does not enter (i.e. eliminated before that round).
* If the bot disconnects mid-game, it will be considered as eliminated from that round, but would still be awarded previous round points.
