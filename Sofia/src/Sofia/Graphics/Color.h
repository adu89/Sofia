#pragma once

namespace sf
{
    class Color
    {
    public:
        Color(int r, int g, int b, float a = 1.0f)
            : r(r), g(g), b(b), a(a)
        {
        }

        int GetR() const { return r; }
        int GetG() const { return g; }
        int GetB() const { return b; }
        int GetA() const { return a; }

    private:
        float r;
        float g;
        float b;
        float a;
    };

    namespace Colors
    {
        static Color Red(255, 0, 0);
        static Color Blue(0, 0, 255);
        static Color Green(0, 255, 0);
        static Color Yellow(255, 255, 0);
        static Color Purple(128, 0, 128);
        static Color Cyan(0, 255, 255);
        static Color White(255, 255, 255);
        static Color Orange(255, 165, 0);
        static Color Black(0, 0, 0);
    }
}