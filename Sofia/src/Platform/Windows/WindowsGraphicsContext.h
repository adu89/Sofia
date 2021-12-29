#pragma once

#include "Sofia/Graphics/GraphicsContext.h"

#include <d2d1.h>
#include <d2d1_1.h>
#include <string>

namespace sf {

class WindowsGraphicsContext 
    : public GraphicsContext
{
    public:
        WindowsGraphicsContext();
        ~WindowsGraphicsContext();
    
        void BeginScene() override;
        void EndScene() override;
        void Resize(int width, int height) override;
    
        void DrawRectangle(int x, int y, int width, int height) override;
        void DrawRectangle(const Rectangle& rectangle) override;
        void FillRectangle(int x, int y, int width, int height) override;
        void FillRectangle(const Rectangle& rectangle) override;       

        void InsertText(const Rectangle& rectangle, std::string text) override; 

        void SetColor(const Color& color) override;
        void SetFont(const Font& font) override;
        void SetClearColor(const Color& color) override;
    private:
        ID2D1Factory* factory;
        ID2D1HwndRenderTarget* renderTarget;
        ID2D1Multithread* multiThread;
        
        ID2D1SolidColorBrush* currentBrush;
        Color currentColor;
        Color clearColor;
        Font currentFont;

        void CreateResources();
        void DiscardResources();
    };
}