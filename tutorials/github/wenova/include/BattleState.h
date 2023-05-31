#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include "BattleEnd.h"
#include "Fighter.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "TimeCounter.h"
#include "Timer.h"
#include "Vector.h"

#include <utility>
#include <vector>

#define N_PLAYERS 4

using std::pair;
using std::vector;

class BattleState : public State
{
private:
    vector<pair<Sprite, Vector>> backgrounds;
    Fighter *players[N_PLAYERS];
    Music music;
    Sound sound;
    void read_level_design(string stage);
    bool game_over;
    int alive[5];
    TimeCounter *time_counter;
    BattleEnd *battleEnd;

public:
    BattleState(string stage, vector<pair<string, string>> players_info);
    ~BattleState();

    void update(float delta);
    void render();

    void pause();
    void resume();
};

#endif
