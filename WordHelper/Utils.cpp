#include "pch.h"
#include "Utils.h"
#include <memory>

std::shared_ptr<WCHAR> MultiByteToWideChar(UINT codePage, LPCSTR pszMultiByte)
{
    int nLength = ::MultiByteToWideChar(codePage, NULL, pszMultiByte, -1, NULL, 0);
    std::shared_ptr<WCHAR> pwBuffer(new wchar_t[nLength + 1]);
    ZeroMemory(pwBuffer.get(), (nLength + 1) * 2);

    ::MultiByteToWideChar(codePage, NULL, pszMultiByte, -1, pwBuffer.get(), nLength);
    return pwBuffer;
}

std::shared_ptr<CHAR> WideCharToMultiByte(UINT codePage, LPCWSTR pszWideChar)
{
    int nLength = ::WideCharToMultiByte(codePage, NULL, pszWideChar, -1, NULL, 0, NULL, NULL);
    std::shared_ptr<CHAR> pBuffer(new char[nLength + 1]);
    ZeroMemory(pBuffer.get(), nLength + 1);

    ::WideCharToMultiByte(codePage, 0, pszWideChar, -1, pBuffer.get(), nLength, NULL, NULL);
    return pBuffer;
}


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

CString CUtils::PathToFolderPath(LPCTSTR pszFullPath)
{
    CString strTemp(pszFullPath);
    int nPos = -1;
    nPos = strTemp.ReverseFind(_T('\\'));
    if (-1 == nPos)
        nPos = strTemp.ReverseFind(_T('/'));
    if (-1 == nPos)
        return _T("");
    return strTemp.Left(nPos + 1);
}

CStringA CUtils::UnicodeToAnsi(LPCWSTR pszContent)
{
    CStringA anscii;
    if (NULL == pszContent) {
        return anscii;
    }

    std::shared_ptr<CHAR> pConvertContent = WideCharToMultiByte(CP_ACP, pszContent);
    if (NULL == pConvertContent) {
        return anscii;
    }

    anscii = pConvertContent.get();
    return anscii;
}

CStringW CUtils::AnsiToUnicode(LPCSTR pszContent)
{
    CStringW unicode;
    if (NULL == pszContent) {
        return unicode;
    }

    std::shared_ptr<WCHAR> pConvertContent = MultiByteToWideChar(CP_ACP, pszContent);
    if (NULL == pConvertContent) {
        return unicode;
    }

    unicode = pConvertContent.get();
    return unicode;
}

CStringW CUtils::UTF8ToUnicode(LPCSTR pszContent)
{
    CStringW unicode;
    if (NULL == pszContent) {
        return unicode;
    }

    std::shared_ptr<WCHAR> pConvertContent = MultiByteToWideChar(CP_UTF8, pszContent);
    if (NULL == pConvertContent) {
        return unicode;
    }

    unicode = pConvertContent.get();
    return unicode;
}

CStringA CUtils::UnicodeToUTF8(LPCWSTR pszContent)
{
    CStringA utf8;
    if (NULL == pszContent) {
        return utf8;
    }

    std::shared_ptr<CHAR> pConvertContent = WideCharToMultiByte(CP_UTF8, pszContent);
    if (NULL == pConvertContent) {
        return utf8;
    }

    utf8 = pConvertContent.get();
    return utf8;
}

CStringA CUtils::Int32ToAString(int value, int nRadix)
{
    CHAR tcResult[35] = { 0 };
    _itoa_s(value, tcResult, 35, nRadix);
    return CStringA(tcResult);
}

int CUtils::StringToInt32(LPCSTR pszValue, int nRadix)
{
    return strtol(pszValue, NULL, nRadix);
}
