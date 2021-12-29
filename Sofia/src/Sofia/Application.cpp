#include "Application.h"

#include "Log.h"
#include "Window.h"

#include <cassert>

namespace sf
{
    Application* Application::instance = nullptr;

    Application::Application() 
    {   
        SF_CORE_ASSERT(!instance, "Application alread exists!");

        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }
    
    void Application::Run() 
    {
        while(isRunning) {
            window->PollEvents();

            if(isRunning)
                OnUpdate();
        }
    }

    Application* Application::Get()
    {
        SF_CORE_ASSERT(instance, "Application does not exist!");

        return instance;
    }
    
    const std::unique_ptr<Window>& Application::GetWindow() 
    {
        SF_CORE_ASSERT(window.get(), "Window does not exists!");

        return window;
    }
    
    void Application::onEvent(Event& event) 
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<AppUpdateEvent>(std::bind(&Application::onAppUpdate, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));

        OnEvent(event);
    }
    
    bool Application::onWindowClose(Event& event) 
    {
        SF_CORE_TRACE("Exiting Application");

        isRunning = false;
        return true;
    }
    
    bool Application::onAppUpdate(Event& event) 
    {
        OnUpdate();

        return false;
    }
    
    bool Application::onWindowResize(WindowResizeEvent& event) 
    {
        GraphicsContext::Instance().Resize(event.GetWidth(), event.GetHeight());

        return false;
    }
}