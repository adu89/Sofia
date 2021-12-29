#include "Input.h"

#include "Platform/Windows/WindowsInput.h"

namespace sf
{
    Input& Input::Instance() 
    {
        static WindowsInput input;
        return input;   
    }
}
