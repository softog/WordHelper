#pragma once
class CUtils
{
public:
    // 获取设备DPI缩放
    static float GetDPIScale();

    // 设置DPI缩放
    static BOOL SetProcessDPIAware();

    static CAtlString PathToFolderPath(LPCTSTR pszFullPath);
    static CAtlStringA UnicodeToAnsi(LPCWSTR pszContent);
    static CAtlStringW AnsiToUnicode(LPCSTR pszContent);
    static CAtlStringW UTF8ToUnicode(LPCSTR pszContent);
    static CAtlStringA UnicodeToUTF8(LPCWSTR pszContent);
    static CAtlStringA Int32ToAString(int value, int nRadix = 10);
    static int StringToInt32(LPCSTR pszValue, int nRadix = 10);
};

