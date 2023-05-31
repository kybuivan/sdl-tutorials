#ifndef JOYSTICKCONFIGSTATE_H
#define JOYSTICKCONFIGSTATE_H

#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"

class JoystickConfigState : public State
{
private:
    Sprite background, joystick_help, back_btn, test_btn, keyboard;
    Text *back_txt, *test_txt, *press, *select_text, *and_text, *start_text,
        *to_go_back;
    bool on_test, is_keyboard;
    Sound blocked, selected, changed;

public:
    JoystickConfigState(int joystick_id, bool ckeyboard = false);

    void update(float delta);
    void render();

    void pause();
    void resume();
};

#endif
