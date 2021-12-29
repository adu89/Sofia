#pragma once

#include "Window.h"
#include "Graphics/GraphicsContext.h"
#include "Sofia/Events/ApplicationEvent.h"
#include "Sofia/Events/MouseEvent.h"

#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

namespace sf
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;
        virtual void OnUpdate() = 0;
        void Run();
        static Application* Get();
        const std::unique_ptr<Window>& GetWindow();
        virtual void OnEvent(Event& event) = 0;
    private:
        bool isRunning = true;
        void onEvent(Event& event);
        bool onWindowClose(Event& event);
        bool onAppUpdate(Event& event);
        bool onWindowResize(WindowResizeEvent& event);
        bool onMouseMoved(MouseMovedEvent& event);
        static Application* instance;
    protected:
        std::unique_ptr<Window> window;
    };

    Application* CreateApplication();
}