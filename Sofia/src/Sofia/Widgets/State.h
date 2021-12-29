#pragma once

#include "Sofia/Input.h"

namespace sf
{
    struct State
    {
        State();
        State(const State&) = delete;
        State(State&&) = delete;
        State& operator=(State&&) = delete;
        State& operator=(const State&) = delete;

        MousePosition MousePosition = { 0, 0 };
        bool IsMouseButtonPressed = false;
        int HotItem = 0;
        int ActiveItem = 0;

        static State& Instance();
    };
}