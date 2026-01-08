#define UNICODE
#define _UNICODE

#include "main_display.hpp"
#include <cmath>
#include <iostream>
#include "utils_display.hpp"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib") //linker, maybe need to modify later to make it cleaner but thats the best way I found rn
/**
 * Most of the code here is from the example of the d2d documentation
 */
App::App() :
    m_hwnd(NULL),
    m_pDirect2dFactory(NULL),
    m_pDWriteFactory(NULL),
    m_pTextFormat(NULL),
    m_pRenderTarget(NULL),
    m_pLightSlateGrayBrush(NULL),
    m_pCornflowerBlueBrush(NULL),
    m_pBlackBrush(NULL),
    m_pSidebarBrush(NULL),
    m_pButtonBrush(NULL),
    m_pTextBrush(NULL),
    m_pGrid(nullptr),
    m_stepIndex(-1),
    m_sidebarWidth(200.0f)
{
}

App::~App() {
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pDWriteFactory);
    SafeRelease(&m_pTextFormat);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pSidebarBrush);
    SafeRelease(&m_pButtonBrush);
    SafeRelease(&m_pTextBrush);
}

void App::SetData(const Grid* grid, const std::vector<std::tuple<int, int>>& path) {
    m_pGrid = grid;
    m_path = path;
    m_stepIndex = 0; // On commence par n'afficher aucun chemin (ou le premier pas)
    if (m_hwnd) InvalidateRect(m_hwnd, NULL, FALSE);
}

void App::RunMessageLoop() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HRESULT App::Initialize() {
    HRESULT hr = CreateDeviceIndependentResources();

    if (SUCCEEDED(hr)) {
        HINSTANCE hInstance = GetModuleHandle(nullptr);
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wcex.lpfnWndProc = App::WndProc;
        wcex.hInstance = hInstance;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = NULL;
        wcex.lpszClassName = L"D2DApp";

        RegisterClassEx(&wcex);

        m_hwnd = CreateWindow(
            L"D2DApp", L"Pathfinding Visualization",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            1000, 600, nullptr, nullptr, hInstance, this
        );

        if (m_hwnd) {
            ShowWindow(m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
        } else {
            hr = E_FAIL;
        }
    }
    return hr;
}

HRESULT App::CreateDeviceIndependentResources() {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

    if (SUCCEEDED(hr)) {
        // Création de la factory pour le texte
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
    }

    if (SUCCEEDED(hr)) {
        hr = m_pDWriteFactory->CreateTextFormat(
            L"Arial", NULL,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            14.0f, L"en-us",
            &m_pTextFormat
        );
    }

    if (SUCCEEDED(hr)) {
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    return hr;
}

HRESULT App::CreateDeviceResources() {
    HRESULT hr = S_OK;

    if (!m_pRenderTarget) {
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = m_pDirect2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
        );

        if (SUCCEEDED(hr)) hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGrayBrush);
        if (SUCCEEDED(hr)) hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &m_pCornflowerBlueBrush);
        if (SUCCEEDED(hr)) hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
        
        // Pinceaux UI
        if (SUCCEEDED(hr)) hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0xDDDDDD), &m_pSidebarBrush); // Gris clair fond
        if (SUCCEEDED(hr)) hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkOrange), &m_pButtonBrush);
        if (SUCCEEDED(hr)) hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pTextBrush);
    }
    return hr;
}

void App::DiscardDeviceResources() {
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pSidebarBrush);
    SafeRelease(&m_pButtonBrush);
    SafeRelease(&m_pTextBrush);
}

HRESULT App::OnRender() {
    HRESULT hr = CreateDeviceResources();
    if (FAILED(hr)) return hr;

    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

    // --- 1. DESSINER LA SIDEBAR (DROITE) ---
    D2D1_RECT_F sidebarRect = D2D1::RectF(rtSize.width - m_sidebarWidth, 0, rtSize.width, rtSize.height);
    m_pRenderTarget->FillRectangle(sidebarRect, m_pSidebarBrush);
    // Ligne de séparation
    m_pRenderTarget->DrawLine(
        D2D1::Point2F(rtSize.width - m_sidebarWidth, 0),
        D2D1::Point2F(rtSize.width - m_sidebarWidth, rtSize.height),
        m_pBlackBrush, 1.0f
    );

    //nuttons
    m_buttons.clear();
    float btnX = rtSize.width - m_sidebarWidth + 20.0f;
    float btnY = 50.0f;
    float btnW = m_sidebarWidth - 40.0f;
    float btnH = 40.0f;
    
    Button nextBtn;
    nextBtn.rect = D2D1::RectF(btnX, btnY, btnX + btnW, btnY + btnH);
    nextBtn.text = L"Next Step >";
    nextBtn.action = ACTION_NEXT_STEP;
    m_buttons.push_back(nextBtn);

    for (const auto& btn : m_buttons) {
        m_pRenderTarget->FillRectangle(btn.rect, m_pButtonBrush);
        m_pRenderTarget->DrawText(
            btn.text.c_str(),
            static_cast<UINT32>(btn.text.length()),
            m_pTextFormat,
            btn.rect,
            m_pTextBrush
        );
    }

    //drawing 
    if (m_pGrid != nullptr) {
        float gridDisplayWidth = rtSize.width - m_sidebarWidth;
        float gridDisplayHeight = rtSize.height;

        int gridW = m_pGrid->getWidth();
        int gridH = m_pGrid->getHeight();

        if (gridW > 0 && gridH > 0 && gridDisplayWidth > 0) {
            float cellWidth = gridDisplayWidth / static_cast<float>(gridW);
            float cellHeight = gridDisplayHeight / static_cast<float>(gridH);

            for (int x = 0; x < gridW; ++x) {
                for (int y = 0; y < gridH; ++y) {
                    D2D1_RECT_F rect = D2D1::RectF(
                        x * cellWidth, y * cellHeight,
                        (x + 1) * cellWidth, (y + 1) * cellHeight
                    );

                    if (m_pGrid->getCell(x, y) == Grid::BLOCKED) {
                        m_pRenderTarget->FillRectangle(rect, m_pBlackBrush);
                    }
                    m_pRenderTarget->DrawRectangle(rect, m_pLightSlateGrayBrush, 0.5f);
                }
            }

            int stepsToShow = m_stepIndex;
            if (stepsToShow > (int)m_path.size()) stepsToShow = (int)m_path.size();

            for (int i = 0; i < stepsToShow; ++i) {
                auto [x, y] = m_path[i];
                D2D1_RECT_F rect = D2D1::RectF(
                    x * cellWidth, y * cellHeight,
                    (x + 1) * cellWidth, (y + 1) * cellHeight
                );
                m_pRenderTarget->FillRectangle(rect, m_pCornflowerBlueBrush);
                m_pRenderTarget->DrawRectangle(rect, m_pLightSlateGrayBrush, 0.5f);
            }
        }
    }

    hr = m_pRenderTarget->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
        hr = S_OK;
        DiscardDeviceResources();
    }
    return hr;
}

void App::OnResize(UINT width, UINT height) {
    if (m_pRenderTarget) {
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}

void App::OnLButtonDown(int pixelX, int pixelY) {
    for (const auto& btn : m_buttons) {
        if (pixelX >= btn.rect.left && pixelX <= btn.rect.right &&
            pixelY >= btn.rect.top && pixelY <= btn.rect.bottom) {
            if (btn.action == ACTION_NEXT_STEP) {
                m_stepIndex++;
                InvalidateRect(m_hwnd, NULL, FALSE);
            }
        }
    }
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    if (message == WM_CREATE) {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        App *pApp = (App *)pcs->lpCreateParams;
        ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp));
        result = 1;
    } else {
        App *pApp = reinterpret_cast<App *>(static_cast<LONG_PTR>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)));
        bool wasHandled = false;

        if (pApp) {
            switch (message) {
            case WM_SIZE:
                {
                    UINT width = LOWORD(lParam);
                    UINT height = HIWORD(lParam);
                    pApp->OnResize(width, height);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_DISPLAYCHANGE:
                InvalidateRect(hwnd, NULL, FALSE);
                result = 0;
                wasHandled = true;
                break;

            case WM_PAINT:
                pApp->OnRender();
                ValidateRect(hwnd, NULL);
                result = 0;
                wasHandled = true;
                break;

            case WM_LBUTTONDOWN:
            case WM_LBUTTONDBLCLK:
                {
                    int x = LOWORD(lParam);
                    int y = HIWORD(lParam);
                    pApp->OnLButtonDown(x, y);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                result = 1;
                wasHandled = true;
                break;
            }
        }

        if (!wasHandled) {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }
    return result;
}