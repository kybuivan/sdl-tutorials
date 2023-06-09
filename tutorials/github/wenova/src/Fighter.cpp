#include "Fighter.h"

#include "Floor.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

#define LAYER 0

#define ii pair<int, int>

#define PI 3.14159265358979
#define INVALID_ID -100
#define CROUCH_COOLDOWN 100.0

using std::min;
using std::pair;
using std::vector;

Fighter::Fighter(int cid, float x, Fighter *cpartner)
{
    partner = cpartner;

    MAX_LIFE = 2000;

    state = FighterState::IDLE;
    id = cid;
    remaining_life = MAX_LIFE;

    special = 0;
    attack_damage = 0;
    vertical_speed = rotation = 0;
    speed = Vector(0, 0);
    acceleration = Vector(0, 0.1);
    max_speed = 9;
    attack_mask = 0;
    sprite = vector<Sprite>(LAST);
    sound = vector<Sound>(LAST);
    temporary_state = state;
    pass_through_timer.set(100);
    played = false;

    orientation = (x > 640 ? LEFT : RIGHT);

    on_floor = false;
    last_collided_floor = 0;
    grab = false;

    ultimate_ready = false;

    n_sprite_start = 0;
    tags["player"] = true;
}

Fighter::~Fighter()
{
}

void Fighter::process_input()
{
    if (!is("game_over"))
    {
        InputManager *input_manager = InputManager::get_instance();
        vector<pair<int, int>> joystick_buttons = {
            ii(JUMP_BUTTON, InputManager::A),
            ii(UP_BUTTON, InputManager::UP),
            ii(DOWN_BUTTON, InputManager::DOWN),
            ii(LEFT_BUTTON, InputManager::LEFT),
            ii(RIGHT_BUTTON, InputManager::RIGHT),
            ii(ATTACK_BUTTON, InputManager::X),
            ii(SPECIAL1_BUTTON, InputManager::B),
            ii(SPECIAL2_BUTTON, InputManager::RB),
            ii(BLOCK_BUTTON, InputManager::LB),
            ii(ULTIMATE_BUTTON, InputManager::Y)};

        bool alive = !is("dying");

        for (ii button : joystick_buttons)
        {
            pressed[button.first] =
                alive &&
                input_manager->joystick_button_press(button.second, id);
            is_holding[button.first] =
                alive &&
                input_manager->is_joystick_button_down(button.second, id);
            released[button.first] =
                alive &&
                input_manager->joystick_button_release(button.second, id);
        }
    }
    else
    {
        memset(pressed, false, sizeof pressed);
        memset(is_holding, false, sizeof is_holding);
    }
}

void Fighter::update(float delta)
{
    process_input();

    temporary_state = state;

    sprite[state].update(delta);
    pass_through_timer.update(delta);

    update_machine_state(delta);

    speed.y = std::min(speed.y + !on_floor * acceleration.y * delta, max_speed);
    box.x += speed.x * delta;
    if (!on_floor)
        box.y += speed.y * delta;

    test_limits();

    crouch_timer.update(delta);

    change_state(temporary_state);

    speed.x = 0;
    grab = false;
    attack_damage *= delta;
    on_floor = false;
}

void Fighter::notify_collision(GameObject &object)
{
    int partner_id = (partner ? partner->get_id() : INVALID_ID);
    int not_in_ultimate = (tags["in_ultimate"] ? 0 : 1);

    //FIXME tá feio
    float floor_y = object.box.y +
                    (box.x - object.box.x) * tan(object.rotation) -
                    object.box.height * 0.5;
    if (object.is("floor") && speed.y >= 0 &&
        abs(floor_y - (box.y + box.height * 0.5)) < 10)
    {
        if (pass_through_timer.get() < 30 && object.is("platform"))
            return;

        int floor_id = ((Floor &)object).get_id();
        speed.y = 0;
        float new_y = object.box.y +
                      (box.x - object.box.x) * tan(object.rotation) -
                      (box.height + object.box.height) * 0.5;
        if (last_collided_floor != floor_id)
            box.y = min(box.y, new_y);
        else
            box.y = new_y;


        on_floor = true;
        last_collided_floor = ((Floor &)object).get_id();
    }
    else if (object.is("player") && !is("dying") && !(object.is("dying")))
    {
        Fighter &fighter = (Fighter &)object;

        if (fighter.is_attacking() && fighter.get_id() != partner_id)
        {
            int left = AttackDirection::ATK_LEFT * (fighter.box.x > box.x);
            int right = AttackDirection::ATK_RIGHT * (fighter.box.x <= box.x);
            int up = AttackDirection::ATK_UP * (fighter.box.y > box.y);
            int down = AttackDirection::ATK_DOWN * (fighter.box.y <= box.y);
            int position_mask = left | right | up | down;
            if (position_mask & fighter.get_attack_mask())
            {
                float damage = fighter.get_attack_damage() *
                               ((state == FighterState::DEFENDING) ? 0.5 : 1);
                increment_life(-damage);
                float m_increment_special =
                    (fighter.get_attack_damage() / 3) *
                    ((state == FighterState::DEFENDING) ? 0 : 1) *
                    not_in_ultimate;
                this->increment_special(m_increment_special);
                if (state != FighterState::DEFENDING)
                    check_stunned();
            }
        }
        else if (is_attacking() && fighter.get_id() != partner_id)
        {
            int left = AttackDirection::ATK_LEFT * (fighter.box.x <= box.x);
            int right = AttackDirection::ATK_RIGHT * (fighter.box.x > box.x);
            int up = AttackDirection::ATK_UP * (fighter.box.y <= box.y);
            int down = AttackDirection::ATK_DOWN * (fighter.box.y > box.y);
            int position_mask = left | right | up | down;
            if (position_mask & get_attack_mask())
            {
                grab = true;
                play_hit();
                this->increment_special((attack_damage / 2) * not_in_ultimate);
            }
        }
    }

    change_state(temporary_state);
}

void Fighter::render()
{
    int x = box.get_draw_x() +
            (orientation == RIGHT ? 0 : -1) * (sprite[state].get_width() - 84);
    int y = box.get_draw_y();

    SDL_RendererFlip flip = (orientation == Orientation::LEFT)
                                ? SDL_FLIP_HORIZONTAL
                                : SDL_FLIP_NONE;
    sprite[state].render(x, y, rotation, flip);
}

bool Fighter::is_dead()
{
    bool dead = remaining_life <= 0;
    if (dead && partner)
        partner->set_partner(nullptr);
    return remaining_life <= 0;
}

float Fighter::get_remaining_life()
{
    return remaining_life;
}

float Fighter::get_special()
{
    return special;
}

//only use in the end of update
void Fighter::change_state(FighterState cstate)
{
    if (state == cstate)
        return;

    float old_height = box.height;
    played = false;

    if ((state == FALLING || state == JUMPING) &&
        (cstate == IDLE || cstate == RUNNING))
        land_sound.play();
    state = cstate;
    Vector csize;
    if (cstate == CROUCH || cstate == CROUCH_ATK || cstate == SPECIAL_1 ||
        cstate == JUMP_ATK_DOWN_FALLLOOP || cstate == JUMP_ATK_DOWN_DMG)
        csize = crouching_size;
    else
        csize = not_crouching_size;
    float new_height = csize.y;

    sprite[state].restart_count(n_sprite_start);
    n_sprite_start = 0;
    play_sound();

    float y = box.y - (new_height - old_height) * 0.5;

    box = Rectangle(box.x, y, csize.x, csize.y);
}

void Fighter::test_limits()
{
    if (box.x < box.width / 2)
        box.x = box.width / 2;
    if (box.x > 1280 - box.width / 2)
        box.x = 1280 - box.width / 2;
    if (box.y < -100)
    {
        box.y = -100;
    }

    if (box.y > 900)
    {
        if (is("test"))
            box.y = -100;
        else
            increment_life(-10000);
    }
}

Fighter::AttackDirection Fighter::get_attack_orientation()
{
    return (orientation == Orientation::LEFT ? AttackDirection::ATK_LEFT
                                             : AttackDirection::ATK_RIGHT);
}

void Fighter::reset_position(float x, float y)
{
    box.x = x;
    box.y = y;
    speed.y = 0;
}

bool Fighter::is_attacking()
{
    return attack_damage > 0;
}

float Fighter::get_attack_damage()
{
    return attack_damage;
}

int Fighter::get_attack_mask()
{
    return attack_mask;
}

int Fighter::get_id()
{
    return id;
}

void Fighter::increment_life(float increment)
{
    remaining_life += increment;
    if (remaining_life < 1)
    {
        remaining_life = 1;
        special = 0;
        if (partner)
            partner->set_partner(nullptr);
        add_tags("dying");
    }

    if (remaining_life > MAX_LIFE)
        remaining_life = MAX_LIFE;
}

void Fighter::increment_special(float increment)
{
    special += increment;
    if (special < 0)
        special = 0;
    if (special > MAX_SPECIAL)
        special = MAX_SPECIAL;
}

void Fighter::set_partner(Fighter *cpartner)
{
    partner = cpartner;
}

Fighter *Fighter::get_partner()
{
    return partner;
}

string Fighter::get_path()
{
    return path;
}

void Fighter::play_sound()
{
    if (sound[state].is_open())
    {
        sound[state].play(0);
    }
}
int Fighter::get_max_life()
{
    return MAX_LIFE;
}

void Fighter::play_hit()
{
    if (played)
        return;
    played = true;
    string sound_file = sound[state].get_file();
    int sound_index = -1;
    if (sound_file == sound_path + "slash.ogg")
        sound_index = 0;
    else if (sound_file == sound_path + "attack_1.ogg")
        sound_index = 1;
    else if (sound_file == sound_path + "attack_2.ogg")
        sound_index = 2;
    else if (sound_file == sound_path + "attack_3.ogg")
        sound_index = 3;
    if (sound_index != -1)
        hit_sounds[sound_index].play();
}

void Fighter::kill()
{
    remaining_life = 0;
}
