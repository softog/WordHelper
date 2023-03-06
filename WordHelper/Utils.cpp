#include "pch.h"
#include "Utils.h"

float CUtils::GetDPIScale()
{
    static float scale_factor = 1.0f;
    static bool initialized = false;
    if (!initialized) {
        HDC screen_dc = ::GetDC(NULL);
        int dpi_x = GetDeviceCaps(screen_dc, LOGPIXELSX);
        scale_factor = static_cast<float>(dpi_x) / 96.0f;
        ::ReleaseDC(NULL, screen_dc);
        initialized = true;
    }
    return scale_factor;

}

BOOL CUtils::SetProcessDPIAware()
{
    typedef  BOOL(WINAPI* pFunSetProcessDPIAware)();
    pFunSetProcessDPIAware pFun = (pFunSetProcessDPIAware)GetProcAddress(GetModuleHandle(L"user32.dll"), "SetProcessDPIAware");
    if (pFun) {
        return pFun();
    }
    return FALSE;

}
