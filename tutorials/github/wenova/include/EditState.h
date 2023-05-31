#ifndef EDITSTATE_H
#define EDITSTATE_H

#include "Fighter.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Vector.h"

#include <utility>
#include <vector>

using std::pair;
using std::vector;

class EditState : public State
{
private:
    vector<pair<Sprite, Vector>> backgrounds;
    Fighter *test_fighter;
    string stage;
    Music music;
    Sound sound;

    void read_level_design();
    void update_level_design();

public:
    EditState(string stage);

    void update(float delta);
    void render();

    void pause();
    void resume();
};

#endif
