#include "Sofia/Window.h"

#include "Sofia/Geometry/Rectangle.h"

#include <Windows.h>
#include <WinUser.h>
#include <d2d1.h>

namespace sf 
{
    class WindowsWindow 
        : public Window
    {
    public:
        WindowsWindow(const WindowProperties& windowProperties);

        void PollEvents() override;
        Rectangle GetClientRectangle() override;
        void* GetNativeWindow() override;
        void SetEventCallback(const EventCallbackFunction& callback) override;
        bool IsReady();

    private:
        bool isReady = false;
        EventCallbackFunction callback;
        HWND windowHandle;
        static LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    };
}