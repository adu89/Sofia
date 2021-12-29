#include "WindowsGraphicsContext.h"

#include "Sofia/Application.h"
#include "Sofia/Log.h"
#include "Sofia/Graphics/Color.h"

#include <dwrite.h>

namespace sf 
{
    WindowsGraphicsContext::WindowsGraphicsContext()
        : factory(nullptr)
        , renderTarget(nullptr)
        , currentBrush(nullptr)
        , currentColor(Colors::Black)
        , currentFont("Segoe UI", 14.0f)
        , clearColor(Colors::White)
    {
        HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

        SF_CORE_ASSERT(!result, "Unable to initialise Direct2D factory.");
    }

    WindowsGraphicsContext::~WindowsGraphicsContext()
    {
        if(factory)
        {
            factory->Release();
            factory = nullptr;
        }

        if(currentBrush)
        {
            currentBrush->Release();
            currentBrush= nullptr;
        }

        if(renderTarget)
        {
            renderTarget->Release();
            renderTarget = nullptr;
        }
    }
    
    void WindowsGraphicsContext::BeginScene() 
    {
        CreateResources();

        renderTarget->BeginDraw();
        renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        renderTarget->Clear(D2D1::ColorF(clearColor.GetR(), clearColor.GetG(), clearColor.GetB(), clearColor.GetA()));
    }
    
    void WindowsGraphicsContext::EndScene() 
    {
        HRESULT result = renderTarget->EndDraw();

        if(result == D2DERR_RECREATE_TARGET)
        {
            DiscardResources();
        }
    }
    
    void WindowsGraphicsContext::Resize(int width, int height) 
    {
        DiscardResources();
    }
    
    void WindowsGraphicsContext::DrawRectangle(int x, int y, int width, int height) 
    {
        D2D1_RECT_F rectangle= D2D1::RectF(x, y, x + width, y + height);
        renderTarget->DrawRectangle(&rectangle, currentBrush);
    }
    
    void WindowsGraphicsContext::DrawRectangle(const Rectangle& rectangle) 
    {
        DrawRectangle(rectangle.GetX(), rectangle.GetY(), rectangle.GetWidth(), rectangle.GetHeight()); 
    }
    
    void WindowsGraphicsContext::FillRectangle(int x, int y, int width, int height) 
    {
        D2D1_RECT_F rectangle = D2D1::RectF(x, y, x + width, y + height);
        renderTarget->FillRectangle(&rectangle, currentBrush);
    }
    
    void WindowsGraphicsContext::FillRectangle(const Rectangle& rectangle) 
    {
        FillRectangle(rectangle.GetX(), rectangle.GetY(), rectangle.GetWidth(), rectangle.GetHeight()); 
    }
    
    void WindowsGraphicsContext::InsertText(const Rectangle& rectangle, std::string text) 
    {
        IDWriteTextFormat* textFormat;
        IDWriteFactory* writeFactory;
        IDWriteTextLayout* textLayout;

        HRESULT result = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED, 
            __uuidof(writeFactory), 
            reinterpret_cast<IUnknown**>(&writeFactory)
        );

        SF_CORE_ASSERT(!result, "Failed to create write factory");
        
        std::wstring fontName(currentFont.GetName().begin(), currentFont.GetName().end());
                
        result = writeFactory->CreateTextFormat(
            fontName.c_str(),
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            currentFont.GetSize(),
            L"",
            &textFormat
        );

        SF_CORE_ASSERT(!result, "Failed to create text format");
        
        std::wstring wideText(text.begin(), text.end());
        
        writeFactory->CreateTextLayout(
            wideText.c_str(),
            wcslen(wideText.c_str()),
            textFormat,
            rectangle.GetWidth(),
            rectangle.GetHeight(),
            &textLayout
        );

        DWRITE_TEXT_METRICS metrics;
        textLayout->GetMetrics(&metrics);

        float widthDiff = rectangle.GetWidth() - metrics.width;
        float heightDiff = rectangle.GetHeight() - metrics.height;
        float x = rectangle.GetX() + widthDiff / 2;
        float y = rectangle.GetY() + heightDiff / 2;

        renderTarget->DrawTextLayout(
            D2D1::Point2F(x, y),
            textLayout,
            currentBrush
        );

        writeFactory->Release();
        textFormat->Release();
        textLayout->Release();
    }
    
    void WindowsGraphicsContext::SetColor(const Color& color) 
    {
        currentColor = color;

        if(currentBrush)
        {
            currentBrush->SetColor(D2D1::ColorF(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
        }
    }
    
    void WindowsGraphicsContext::SetFont(const Font& font) 
    {
        currentFont = font;
    }
    
    void WindowsGraphicsContext::SetClearColor(const Color& color) 
    {
        clearColor = color;
    }
    
    void WindowsGraphicsContext::CreateResources() 
    {
        if(renderTarget)
            return;

        Window* applicationWindow = Application::Get()->GetWindow().get();
        Rectangle clientRectangle = applicationWindow->GetClientRectangle();
        HWND windowHandle = (HWND)applicationWindow->GetNativeWindow();

        RECT rc;

        GetClientRect(windowHandle, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        HRESULT result = factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(windowHandle, size),
            &renderTarget
        );

        SF_CORE_ASSERT(!result, "Failed to create render target")

        result = renderTarget->CreateSolidColorBrush(
            D2D1::ColorF(currentColor.GetR(), currentColor.GetG(), currentColor.GetB(), currentColor.GetA()), 
            &currentBrush
        );
        
        SF_CORE_ASSERT(!result, "Failed to create current brush")
    }
    
    void WindowsGraphicsContext::DiscardResources() 
    {
        currentBrush->Release();
        currentBrush = nullptr;
        
        renderTarget->Release();
        renderTarget = nullptr;
    }
}