//
// Created by MasterKtos on 07.11.2022.
//

#ifndef KENAZENGINEGAME_JOYSTICK_H
#define KENAZENGINEGAME_JOYSTICK_H

enum JoystickAction
{
    NONE,
    MOVE_UP,
    MOVE_DOWN,
    STOP_VERTICAL,
    MOVE_LEFT,
    MOVE_RIGHT,
    STOP_HORIZONTAL
};

#include <SDL_joystick.h>
#include <SDL_events.h>

class Joystick {
private:
    SDL_Joystick *joystick;
    int deadzone = 1000;

    static bool JoystickConnected();

public:

    void Connect();
    JoystickAction HandleInput(SDL_Event &event);
};


#endif //KENAZENGINEGAME_JOYSTICK_H
