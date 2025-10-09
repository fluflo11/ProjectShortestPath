#ifndef MAIN_DISPLAY_HPP
#define MAIN_DISPLAY_HPP

//Windows Header Files :
#include <windows.h>
#include "utils_display.hpp"
// C Runtime Header Files : 
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

class App{
public:
    App();
    ~App();
    // Register the window class and call methods for instantiating drawing resources
    HRESULT Initialize();
    // Process and dispatch messages
    void RunMessageLoop();
private:
    HWND m_hwnd;
    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
    ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
    // Initialize device-independent resources.
    HRESULT CreateDeviceIndependentResources();
    // Initialize device-dependent resources.
    HRESULT CreateDeviceResources();
    // Release device-dependent resource.
    void DiscardDeviceResources();
    // Draw content.
    HRESULT OnRender();

    // Resize the render target.
    void OnResize(
        UINT width,
        UINT height
    );
    // The windows procedure.
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );
};


#endif