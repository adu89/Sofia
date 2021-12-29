#include "WindowsWindow.h"

#include <Windowsx.h>

#include "Sofia/Log.h"
#include "Sofia/Events/ApplicationEvent.h"
#include "Sofia/Events/MouseEvent.h"

namespace sf 
{    
    WindowsWindow::WindowsWindow(const WindowProperties& windowProperties)
        : callback([](Event&){})
    {
        WNDCLASS wc = {};

        wc.lpfnWndProc = WindowsWindow::MessageHandler;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "Application Window Class";
        wc.cbWndExtra = sizeof(WindowsWindow);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);

        RegisterClass(&wc);

        windowHandle = CreateWindowEx(0,                              
            "Application Window Class",                     
            windowProperties.Title.c_str(),    
            WS_OVERLAPPEDWINDOW,            
            CW_USEDEFAULT, 
            CW_USEDEFAULT, 
            windowProperties.Width, 
            windowProperties.Height,
            NULL,          
            NULL,       
            GetModuleHandle(NULL),  
            NULL
        );

        SetWindowLongPtrW(windowHandle, 0, reinterpret_cast<LONG_PTR>(this));

        ShowWindow(windowHandle, SW_SHOW);

        //ShowCursor(false);
    }
    
    void WindowsWindow::PollEvents() 
    {
        MSG msg = { };
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    Rectangle WindowsWindow::GetClientRectangle() 
    {
        RECT rc;
        GetClientRect(windowHandle, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        return Rectangle(rc.left, rc.top, size.width, size.height);
    }
    
    void* WindowsWindow::GetNativeWindow() 
    {
        return windowHandle;
    }
    
    void WindowsWindow::SetEventCallback(const EventCallbackFunction& cb) 
    {
        callback = cb;
    }
    
    bool WindowsWindow::IsReady() 
    {
        return isReady;
    }

    LRESULT CALLBACK WindowsWindow::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WindowsWindow* windowHandle = (WindowsWindow*)(GetWindowLongPtrW(hwnd, 0));

        switch(message)
        {
            case WM_MOUSEMOVE:
            {
                auto xPosition = GET_X_LPARAM(lParam);
                auto yPosition = GET_Y_LPARAM(lParam);

                if(windowHandle)
                {
                    MouseMovedEvent event(xPosition, yPosition);
                    windowHandle->callback(event);
                }

                break;
            }
            case WM_SIZE:
            {
                auto width = LOWORD(lParam);
                auto height = HIWORD(lParam);

                if(windowHandle) 
                {
                    WindowResizeEvent event(width, height);
                    windowHandle->callback(event);
                }

                break;
            }
            case WM_DESTROY:
            {
                WindowCloseEvent event;
                windowHandle->callback(event);

                break;
            }        
        }

        if(windowHandle) 
        {
            AppUpdateEvent event;
            windowHandle->callback(event);
        }
        
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}