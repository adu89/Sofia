#include <Sofia.h>

class Example : public sf::Application
{
public:
    void OnUpdate() override
    {
        using sf::widgets::Button;
        
        auto& state = sf::State::Instance();
        auto& graphicsContext = sf::GraphicsContext::Instance();
        auto& input = sf::Input::Instance();

        auto mousePosition = input.GetMousePosition();

        state.MousePosition = { mousePosition.X, mousePosition.Y };
        state.IsMouseButtonPressed = input.IsMouseButtonPressed(sf::MouseButton::LEFT);
        state.HotItem = 0;

        graphicsContext.BeginScene();

        if(Button("File"))
        {
            comboBoxState = !comboBoxState;
        }

        if(comboBoxState)
        {
            if(Button("Option 1"))
            {
                comboBoxState = false;
            }

            if(Button("Option 2"))
            {
                comboBoxState = false;
            }
        }

        graphicsContext.EndScene();

        if(!state.IsMouseButtonPressed)
        {
            state.ActiveItem = 0;
        }
        else {
            if(!state.ActiveItem)
            {
                state.ActiveItem = -1;
            }
        }
    }

    void OnEvent(sf::Event& event) override
    {
        sf::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<sf::MouseMovedEvent>(std::bind(&Example::onMouseMoved, this, std::placeholders::_1));
    }

private:
    bool comboBoxState = false;
    bool onMouseMoved(sf::MouseMovedEvent& mouseMovedEvent) 
    {
        // state = { mouseMovedEvent.GetX(), mouseMovedEvent.GetY() };
        return true;
    }
};

sf::Application* sf::CreateApplication()
{
    return new Example();
}
