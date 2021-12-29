#include "Widgets.h"

#include "Sofia/Log.h"
#include "Sofia/Widgets/State.h"
#include "Sofia/Widgets/Theme.h"

#include <functional>

namespace sf::widgets
{
    bool Button(const std::string& text)
    {
        auto& g = GraphicsContext::Instance();
        auto& s = State::Instance();
        auto& t = Theme::Instance();

        auto id = GenerateId(text);

        if(rect.Contains(s.MousePosition.X, s.MousePosition.Y))
        {
            g.SetColor(t.ButtonHoverColor);
            g.FillRectangle(rect);

            s.HotItem = id;

            if(!s.ActiveItem && s.IsMouseButtonPressed)
            {
                s.ActiveItem = id;
            }
        } 
        else
        {
            g.SetColor(t.ButtonBackgroundColor);
            g.FillRectangle(rect);
        }
        
        g.SetColor(t.TextColor);
        g.InsertText(rect, text);

        return !s.IsMouseButtonPressed && s.HotItem == id && s.ActiveItem == id;
    }
    
    void Cursor() 
    {
        auto& g = GraphicsContext::Instance();
        auto& s = State::Instance();
        
        g.SetColor(Colors::Black);
        g.DrawRectangle(Rectangle(s.MousePosition.X, s.MousePosition.Y, 10, 10));
    }
    
    unsigned int GenerateId(const std::string& key) 
    {
        std::hash<std::string> hasher;
        return hasher(key);
    }
}