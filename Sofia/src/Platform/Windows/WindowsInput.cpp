#include "WindowsInput.h"

#include "Sofia/Application.h"

#include <Windows.h>
#include <WinUser.h>

namespace sf
{
    MousePosition Input::GetMousePosition()
    {
        auto windowHandle = (HWND)Application::Get()->GetWindow()->GetNativeWindow();

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(windowHandle, &pt);

        return { pt.x, pt.y };
    }

    bool Input::IsMouseButtonPressed(MouseButton mouseButton)
    {
        if(mouseButton == MouseButton::LEFT)
            return GetAsyncKeyState(VK_LBUTTON) != 0;
        else if(mouseButton == MouseButton::RIGHT)
            return GetAsyncKeyState(VK_RBUTTON) != 0;
        else
            return false;
    }
}