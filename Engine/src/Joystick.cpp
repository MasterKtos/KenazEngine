//
// Created by MasterKtos on 07.11.2022.
//

#include "Engine/Joystick.h"

#include <cstdio>
#include <cmath>


bool Joystick::JoystickConnected() {
    return SDL_NumJoysticks() > 0;
}

void Joystick::Connect() {
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);
}

JoystickAction Joystick::HandleInput(SDL_Event &event) {
    if(!JoystickConnected()) return NONE;

    switch(event.jaxis.axis)
    {
        case 1:
            if(abs(event.jaxis.value) < deadzone) return STOP_VERTICAL;
            if(event.jaxis.value > 0) return MOVE_DOWN;
            if(event.jaxis.value < 0) return MOVE_UP;
        case 0:
            if(abs(event.jaxis.value) < deadzone) return STOP_HORIZONTAL;
            if(event.jaxis.value > 0) return MOVE_RIGHT;
            if(event.jaxis.value < 0) return MOVE_LEFT;
    }
}