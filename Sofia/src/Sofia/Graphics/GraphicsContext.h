#pragma once

#include "Sofia/Window.h"
#include "Sofia/Geometry/Rectangle.h"
#include "Sofia/Graphics/Color.h"
#include "Sofia/Graphics/Font.h"

namespace sf
{
    class GraphicsContext
    {
    public:
        GraphicsContext();
        GraphicsContext(const GraphicsContext&) = delete;
        GraphicsContext(GraphicsContext&&) = delete;
        GraphicsContext& operator=(GraphicsContext&&) = delete;
        GraphicsContext& operator=(const GraphicsContext&) = delete;

        virtual void BeginScene() = 0;
        virtual void EndScene() = 0;
        virtual void Resize(int width, int height) = 0;

        virtual void DrawRectangle(int x, int y, int width, int height) = 0;
        virtual void DrawRectangle(const Rectangle& rectangle) = 0;
        virtual void FillRectangle(int x, int y, int width, int height) = 0;
        virtual void FillRectangle(const Rectangle& rectangle) = 0;
        virtual void InsertText(const Rectangle& rectangle, std::string text) = 0;

        virtual void SetColor(const Color& color) = 0;
        virtual void SetFont(const Font& font) = 0;
        virtual void SetClearColor(const Color& color) = 0;

        static GraphicsContext& Instance();
    };
}