#include "Blood.h"

#include "Game.h"
#include "HealEffect.h"
#include "UltimateEffect.h"

#define CROUCH_COOLDOWN 50.0

#include <algorithm>

using std::min;

Blood::Blood(string skin, float x, float y, int cid, Fighter *cpartner)
    : Fighter(cid, x, cpartner)
{
    path = "characters/blood/" + skin + "/";
    sound_path = "characters/blood/sound/";

    sprite[IDLE] = Sprite(path + "idle.png", 12, 10);
    sprite[RUNNING] = Sprite(path + "running.png", 8, 10);
    sprite[JUMPING] = Sprite(path + "jumping.png", 6, 10);
    sprite[FALLING] = Sprite(path + "falling.png", 2, 10);
    sprite[CROUCH] = Sprite(path + "crouch.png", 3, 20);
    sprite[IDLE_ATK_NEUTRAL_1] = Sprite(path + "idle_atk_neutral_1.png", 4, 10);
    sprite[IDLE_ATK_NEUTRAL_2] = Sprite(path + "idle_atk_neutral_2.png", 4, 10);
    sprite[IDLE_ATK_NEUTRAL_3] = Sprite(path + "idle_atk_neutral_3.png", 3, 10);
    sprite[IDLE_ATK_FRONT] = Sprite(path + "idle_atk_front.png", 5, 10);
    sprite[IDLE_ATK_UP] = Sprite(path + "idle_atk_up.png", 5, 10);
    sprite[IDLE_ATK_DOWN] = Sprite(path + "idle_atk_down.png", 6, 10);
    sprite[CROUCH_ATK] = Sprite(path + "crouch_atk.png", 3, 10);
    sprite[JUMP_ATK_DOWN] = Sprite(path + "jump_atk_down.png", 4, 10);
    sprite[JUMP_ATK_NEUTRAL] = Sprite(path + "jump_atk_neutral.png", 5, 10);
    sprite[JUMP_ATK_UP] = Sprite(path + "jump_atk_up.png", 4, 10);
    sprite[DEFENDING] = Sprite(path + "defending.png", 2, 10);
    sprite[STUNNED] = Sprite(path + "stunned.png", 2, 10);
    sprite[SPECIAL_1_1] = Sprite(path + "special_1_1.png", 7, 10);
    sprite[SPECIAL_1_2] = Sprite(path + "special_1_2.png", 11, 10);
    sprite[SPECIAL_2] = Sprite(path + "special_2.png", 8, 10);
    sprite[DYING] = Sprite(path + "dying.png", 12, 10);

    sound[JUMPING] = Sound(sound_path + "jump.ogg");
    sound[IDLE_ATK_NEUTRAL_1] = Sound(sound_path + "attack_1.ogg");
    sound[IDLE_ATK_NEUTRAL_2] = Sound(sound_path + "attack_2.ogg");
    sound[IDLE_ATK_NEUTRAL_3] = Sound(sound_path + "slash.ogg");
    sound[IDLE_ATK_FRONT] = Sound(sound_path + "attack_2.ogg");
    sound[IDLE_ATK_DOWN] = Sound(sound_path + "idle_atk_down.ogg");
    sound[IDLE_ATK_UP] = Sound(sound_path + "slash.ogg");
    sound[JUMP_ATK_NEUTRAL] = Sound(sound_path + "slash.ogg");
    sound[JUMP_ATK_UP] = Sound(sound_path + "slash.ogg");
    sound[CROUCH_ATK] = Sound(sound_path + "slash.ogg");
    sound[SPECIAL_1_1] = Sound(sound_path + "special_1_1.ogg");
    sound[SPECIAL_1_2] = Sound(sound_path + "special_1_2.ogg");
    sound[SPECIAL_2] = Sound(sound_path + "heal.ogg");

    ultimate_sound = Sound(sound_path + "ultimate.ogg");
    land_sound = Sound(sound_path + "land.ogg");
    hit_sounds[0] = Sound(sound_path + "hit_slash.ogg");
    hit_sounds[1] = Sound(sound_path + "hit_1.ogg");
    hit_sounds[2] = Sound(sound_path + "hit_2.ogg");
    hit_sounds[3] = Sound(sound_path + "hit_3.ogg");

    crouching_size = Vector(84, 59);
    not_crouching_size = Vector(84, 84);

    tags["blood"] = true;
    tags[skin] = true;
    box = Rectangle(x, y, 84, 84);
}

void Blood::update_machine_state(float delta)
{
    switch (state)
    {
    case FighterState::IDLE_ATK_NEUTRAL_1:
    {
        attack_damage = 3 * (sprite[state].get_current_frame() == 1);
        attack_mask = get_attack_orientation();
        if (sprite[state].is_finished())
        {
            check_idle();
            check_defense();
            check_crouch();
            check_idle_atk_neutral_2();
        }
        else if (pressed[ATTACK_BUTTON])
        {
            combo++;
        }
        break;
    }
    case FighterState::IDLE_ATK_NEUTRAL_2:
    {
        attack_damage = 5 * (sprite[state].get_current_frame() == 1);
        attack_mask = get_attack_orientation();
        if (sprite[state].is_finished())
        {
            check_idle();
            check_defense();
            check_crouch();
            check_idle_atk_neutral_3();
        }
        else if (pressed[ATTACK_BUTTON])
        {
            combo++;
        }
        break;
    }
    case FighterState::IDLE_ATK_FRONT: //2
    {
        attack_damage = 10 * (sprite[state].get_current_frame() == 2);
        attack_mask = get_attack_orientation();
        if (sprite[state].is_finished())
        {
            check_idle();
            check_defense();
            check_crouch();
        }
        break;
    }
    case FighterState::IDLE_ATK_DOWN: //3
    {
        attack_damage = 10 * (sprite[state].get_current_frame() == 3);
        attack_mask = AttackDirection::ATK_DOWN;
        if (sprite[state].is_finished())
        {
            check_idle();
            check_defense();
            check_crouch();
        }
        break;
    }
    case FighterState::CROUCH_ATK: //1
    {
        attack_damage = 3 * (sprite[state].get_current_frame() == 1);
        attack_mask = get_attack_orientation() | AttackDirection::ATK_DOWN;
        if (sprite[state].is_finished())
        {
            check_idle();
            check_defense();
            check_crouch();
        }
        break;
    }
    case FighterState::IDLE_ATK_NEUTRAL_3: //1
    case FighterState::IDLE_ATK_UP:        //1
    {
        attack_damage = 3 * (sprite[state].get_current_frame() == 1);
        attack_mask = get_attack_orientation();
        if (sprite[state].is_finished())
        {
            check_idle();
            check_defense();
            check_crouch();
        }
        break;
    }
    case FighterState::JUMP_ATK_DOWN:
    {
        attack_damage = 2;
        attack_mask = AttackDirection::ATK_DOWN;
        check_left(false);
        check_right(false);
        if (on_floor)
        {
            n_sprite_start = 2;
            check_idle_atk_down(true, true);
        }
        break;
    }
    case FighterState::JUMP_ATK_NEUTRAL:
    {
        attack_damage = 7 * (sprite[state].get_current_frame() < 1);
        attack_mask = get_attack_orientation();
        check_right(false);
        check_left(false);
        if (sprite[state].is_finished())
        {
            check_fall();
        }
        if (on_floor)
        {
            check_idle();
            check_right();
            check_defense();
            check_crouch();
            check_left();
        }
        break;
    }
    case FighterState::JUMP_ATK_UP:
    {
        attack_damage = 7 * (sprite[state].get_current_frame() == 1);
        attack_mask = AttackDirection::ATK_UP;
        check_left(false);
        check_right(false);
        if (sprite[state].is_finished())
        {
            speed.y = 0.1;
            check_fall();
            check_crouch();
            check_defense();
            check_idle();
        }
        break;
    }
    case FighterState::STUNNED:
    {
        attack_damage = 0;
        attack_mask = 0;
        if (sprite[state].is_finished())
        {
            check_fall();
            check_defense();
            check_crouch();
            check_idle();
            check_dead();
        }
        break;
    }
    case FighterState::SPECIAL_1_1:
    {
        attack_damage = 0.1 * (sprite[state].get_current_frame() > 3);
        if (grab)
            increment_life(attack_damage);
        attack_mask = get_attack_orientation();
        if (sprite[state].is_finished())
        {
            if (grab)
            {
                check_special_1_2();
            }
            else
            {
                check_fall();
                check_defense();
                check_crouch();
                check_idle();
            }
        }
        break;
    }
    case FighterState::SPECIAL_1_2:
    {
        attack_damage = 0.5;
        if (grab)
            increment_life(attack_damage);
        attack_mask = get_attack_orientation();
        if (sprite[state].is_finished() || !grab)
        {
            check_fall();
            check_defense();
            check_crouch();
            check_idle();
        }
        break;
    }
    case FighterState::SPECIAL_2:
    {
        increment_special(0.2 * delta);
        increment_life(-0.2 * delta);
        if (sprite[state].is_finished())
        {
            Game::get_instance().get_current_state().add_object(
                new HealEffect(partner,
                               "characters/blood/heal_effect.png",
                               "has_sprite",
                               9,
                               0.2));
            check_idle();
            check_defense();
            check_crouch();
        }
        break;
    }
    case FighterState::IDLE:
    {
        attack_damage = 0;
        attack_mask = 0;
        combo = 0;
        check_jump();
        check_left(on_floor);
        check_right(on_floor);
        check_crouch();
        check_defense();
        check_idle_atk_neutral_1();
        check_idle_atk_front();
        check_idle_atk_up();
        check_idle_atk_down();
        check_special_1_1();
        check_special_2();
        check_ultimate();
        check_pass_through_platform();
        check_fall();
        check_dead();
        break;
    }
    case FighterState::JUMPING:
    {
        attack_damage = 0;
        attack_mask = 0;
        check_left(on_floor);
        check_right(on_floor);
        check_fall();
        check_idle();
        check_defense();
        check_crouch();
        check_jump_atk_neutral();
        check_jump_atk_up();
        check_jump_atk_down();
        check_ultimate();
        break;
    }
    case FighterState::FALLING:
    {
        attack_damage = 0;
        attack_mask = 0;
        check_idle();
        check_left(on_floor);
        check_right(on_floor);
        check_fall();
        check_defense();
        check_crouch();
        check_jump_atk_neutral();
        check_jump_atk_up();
        check_jump_atk_down();
        check_ultimate();
        break;
    }
    case FighterState::RUNNING:
    {
        attack_damage = 0;
        attack_mask = 0;
        combo = 0;
        check_jump();
        check_left(false);
        check_right(false);
        check_idle();
        check_crouch();
        check_defense();
        check_idle_atk_neutral_1();
        check_idle_atk_front();
        check_special_1_1();
        check_special_2();
        check_idle_atk_up();
        check_idle_atk_down();
        check_ultimate();
        check_pass_through_platform();
        check_fall();
        break;
    }
    case FighterState::DEFENDING:
    {
        attack_damage = 0;
        attack_mask = 0;
        check_idle();
        check_fall();
        break;
    }
    case FighterState::CROUCH:
    {
        attack_damage = 0;
        attack_mask = 0;
        check_idle();
        check_crouch_atk();
        check_defense();
        check_fall();
        break;
    }
    case FighterState::DYING:
    {
        if (sprite[state].is_finished())
        {
            remaining_life = 0;
        }
        break;
    }
    case FighterState::JUMP_ATK_DOWN_FALLLOOP:
    case FighterState::JUMP_ATK_DOWN_DMG:
    case FighterState::SPECIAL_1:
    case FighterState::LAST:
        printf("Invalid blood %d %d state\n", id, state);
        exit(-1);
        break;
    }
}

void Blood::check_jump(bool change)
{
    if (pressed[JUMP_BUTTON])
    {
        if (change)
            temporary_state = FighterState::JUMPING;
        speed.y = -5;
        on_floor = false;
    }
}

void Blood::check_fall(bool change)
{
    if (speed.y > 0)
    {
        if (change)
            temporary_state = FighterState::FALLING;
    }
}

void Blood::check_left(bool change)
{
    if (is_holding[LEFT_BUTTON])
    {
        if (change)
            temporary_state = FighterState::RUNNING;
        speed.x = -3;
        orientation = Orientation::LEFT;
    }
}

void Blood::check_right(bool change)
{
    if (is_holding[RIGHT_BUTTON])
    {
        if (change)
            temporary_state = FighterState::RUNNING;
        speed.x = 3;
        orientation = Orientation::RIGHT;
    }
}

void Blood::check_idle(bool change)
{
    if (speed.x == 0 && on_floor && !is_holding[DOWN_BUTTON] &&
        !is_holding[BLOCK_BUTTON])
    {
        if (change)
            temporary_state = FighterState::IDLE;
    }
}

void Blood::check_crouch(bool change)
{
    if (is_holding[DOWN_BUTTON] && on_floor)
    {
        if (change)
            temporary_state = FighterState::CROUCH;
    }
}

void Blood::check_idle_atk_neutral_1(bool change)
{
    if (pressed[ATTACK_BUTTON])
    {
        speed.y = 0;
        if (change)
            temporary_state = FighterState::IDLE_ATK_NEUTRAL_1;
    }
}

void Blood::check_idle_atk_neutral_2(bool change)
{
    if (combo)
    {
        combo--;
        if (change)
            temporary_state = FighterState::IDLE_ATK_NEUTRAL_2;
    }
}

void Blood::check_idle_atk_neutral_3(bool change)
{
    if (combo)
    {
        combo--;
        if (change)
            temporary_state = FighterState::IDLE_ATK_NEUTRAL_3;
    }
}

void Blood::check_idle_atk_front(bool change)
{
    if (pressed[ATTACK_BUTTON] &&
        (is_holding[LEFT_BUTTON] || is_holding[RIGHT_BUTTON]))
    {
        if (change)
            temporary_state = FighterState::IDLE_ATK_FRONT;
        orientation =
            is_holding[LEFT_BUTTON] ? Orientation::LEFT : Orientation::RIGHT;
    }
}

void Blood::check_idle_atk_up(bool change)
{
    if (pressed[ATTACK_BUTTON] && is_holding[UP_BUTTON])
    {
        if (change)
            temporary_state = FighterState::IDLE_ATK_UP;
    }
}

void Blood::check_idle_atk_down(bool change, bool condition)
{
    if ((pressed[ATTACK_BUTTON] && is_holding[DOWN_BUTTON]) || condition)
    {
        if (change)
            temporary_state = FighterState::IDLE_ATK_DOWN;
    }
}

void Blood::check_pass_through_platform(bool change)
{
    if (pressed[DOWN_BUTTON] && !is_holding[ATTACK_BUTTON])
    {
        if (crouch_timer.get() < CROUCH_COOLDOWN)
        {
            if (change)
                temporary_state = FighterState::FALLING;
            pass_through_timer.restart();
        }
        crouch_timer.restart();
    }
}

void Blood::check_crouch_atk(bool change)
{
    if (pressed[ATTACK_BUTTON])
    {
        if (change)
            temporary_state = FighterState::CROUCH_ATK;
    }
}

void Blood::check_jump_atk_down(bool change)
{
    if (pressed[ATTACK_BUTTON] && is_holding[DOWN_BUTTON])
    {
        if (change)
            temporary_state = FighterState::JUMP_ATK_DOWN;
    }
}

void Blood::check_jump_atk_neutral(bool change)
{
    if (pressed[ATTACK_BUTTON])
    {
        if (change)
            temporary_state = FighterState::JUMP_ATK_NEUTRAL;
    }
}

void Blood::check_jump_atk_up(bool change)
{
    if (pressed[ATTACK_BUTTON] && is_holding[UP_BUTTON])
    {
        if (combo)
            return;
        combo++;
        speed.y = -5;
        if (change)
            temporary_state = FighterState::JUMP_ATK_UP;
    }
}

void Blood::check_defense(bool change)
{
    if (is_holding[BLOCK_BUTTON] && on_floor)
    {
        if (change)
            temporary_state = FighterState::DEFENDING;
    }
}

void Blood::check_stunned(bool change)
{
    speed.x = 0;
    if (change)
        temporary_state = FighterState::STUNNED;
}

void Blood::check_special_1_1(bool change)
{
    if (pressed[SPECIAL1_BUTTON])
    {
        if (change)
            temporary_state = FighterState::SPECIAL_1_1;
    }
}

void Blood::check_special_1_2(bool change)
{
    attack_damage = 0.5;
    if (change)
        temporary_state = FighterState::SPECIAL_1_2;
}

void Blood::check_special_2(bool change)
{
    if (pressed[SPECIAL2_BUTTON] && partner)
    {
        if (change)
            temporary_state = FighterState::SPECIAL_2;
    }
}

void Blood::check_dead(bool change)
{
    if (is("dying"))
    {
        if (change)
            temporary_state = FighterState::DYING;
    }
}

void Blood::check_ultimate()
{
    if (pressed[ULTIMATE_BUTTON] && special == MAX_SPECIAL)
    {
        Game::get_instance().get_current_state().add_object(
            new UltimateEffect(this,
                               path + "ult_effect.png",
                               path + "aura.png",
                               "has_sprite",
                               1));
        ultimate_sound.play();
    }
}
