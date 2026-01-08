#ifndef MAIN_DISPLAY_HPP
#define MAIN_DISPLAY_HPP

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h> 
#include <vector>
#include <string>
#include <tuple>

#include "grid.hpp"
/**
 * Some of the code here is from microsoft
 */
enum ButtonAction {
    ACTION_NONE = 0,
    ACTION_NEXT_STEP
};

struct Button {
    D2D1_RECT_F rect;
    std::wstring text;
    ButtonAction action;
};

class App {
public:
    App();
    ~App();

    HRESULT Initialize();
    void SetData(const Grid* grid, const std::vector<std::tuple<int, int>>& path);
    void RunMessageLoop();

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();
    void DiscardDeviceResources();
    HRESULT OnRender();
    void OnResize(UINT width, UINT height);
    void OnLButtonDown(int pixelX, int pixelY);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;

    ID2D1Factory* m_pDirect2dFactory;
    IDWriteFactory* m_pDWriteFactory;
    IDWriteTextFormat* m_pTextFormat;

    ID2D1HwndRenderTarget* m_pRenderTarget;

    ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
    ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
    ID2D1SolidColorBrush* m_pBlackBrush;
    

    ID2D1SolidColorBrush* m_pSidebarBrush;
    ID2D1SolidColorBrush* m_pButtonBrush;
    ID2D1SolidColorBrush* m_pTextBrush;


    const Grid* m_pGrid;
    std::vector<std::tuple<int, int>> m_path;

    std::vector<Button> m_buttons; 
    int m_stepIndex;
    float m_sidebarWidth;
};

#endif