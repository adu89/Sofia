#include "Theme.h"

namespace sf
{
    Theme& Instance()
    {
        static Theme theme;
        return theme;
    }
}