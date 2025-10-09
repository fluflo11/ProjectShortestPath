#ifndef UTILS_DISPLAY_HPP
#define UTILS_DISPLAY_HPP

#include "main_display.hpp"

/**
 * Code from Microsoft
 */

#include <windows.h> 
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>


template<class Interface>
inline  void SafeRelease(Interface **ppInterfaceToRelease){
    if(*ppInterfaceToRelease != NULL){
        (
            (*ppInterfaceToRelease)->Release();
            (*ppInterfaceToRelease) = NULL;
        )
    }
}

int WINAPI WinMain(
    HINSTANCE /* hInstance */,
    HINSTANCE /* hPrevInstance */,
    LPSTR /* lpCmdLine */,
    int /* nCmdShow */
    )
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            App app;

            if (SUCCEEDED(app.Initialize()))
            {
                app.RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return 0;
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");} } while(0)
#else 
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#endif //UTILS_DISPLAY_HPP