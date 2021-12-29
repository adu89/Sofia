#pragma once

namespace sf 
{

class Rectangle
{
public:
    Rectangle(int x, int y, int width, int height)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
    {
    }

    Rectangle()
        : x(0)
        , y(0)
        , width(0)
        , height(0)
    {
    }

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetLeft() const { return x; }
    int GetRight() const { return x + width; }
    int GetTop() const { return y; }
    int GetBottom() const { return y + height; }

    bool Contains(int mouseX, int mouseY) const
    {
        if(mouseX >= GetLeft() && mouseX <= GetRight() &&
            mouseY >= GetTop() && mouseY <= GetBottom())
            return true;
    
        return false;
    }

private:
    int x;
    int y;
    int width;
    int height;
};

}