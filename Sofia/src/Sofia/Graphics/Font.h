#pragma once

#include <string>

namespace sf
{
    class Font
    {
    public:
        Font(std::string name, float size)
            : name(name), size(size)
        {
        }

        std::string& GetName() { return name; }
        float GetSize() { return size; }

    private:
        std::string name;
        float size;
    };
}