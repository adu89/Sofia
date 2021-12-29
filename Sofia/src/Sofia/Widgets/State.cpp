#include "State.h"

namespace sf
{
    State& State::Instance() 
    {
        static State state;
        return state;
    }

    
}
