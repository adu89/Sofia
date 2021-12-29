#pragma once

namespace sf
{
    struct MousePosition
    {
        int X;
        int Y;
    };

    enum struct MouseButton
    {
        LEFT,
        RIGHT
    };

    class Input
    {
    public:
        Input(const Input&) = delete;
        Input(Input&&) = delete;
        Input& operator=(Input&&) = delete;
        Input& operator=(const Input&) = delete;

        virtual MousePosition GetMousePosition() = 0;
        virtual bool IsMouseButtonPressed(MouseButton mouseButton) = 0;

        static Input& Instance();
    };
}