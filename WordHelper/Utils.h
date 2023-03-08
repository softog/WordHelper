#pragma once
class CUtils
{
public:
    // 获取设备DPI缩放
    static float GetDPIScale();

    // 设置DPI缩放
    static BOOL SetProcessDPIAware();

    static CString PathToFolderPath(LPCTSTR pszFullPath);
    static CStringA UnicodeToAnsi(LPCWSTR pszContent);
    static CStringW AnsiToUnicode(LPCSTR pszContent);
    static CStringW UTF8ToUnicode(LPCSTR pszContent);
    static CStringA UnicodeToUTF8(LPCWSTR pszContent);
    static CStringA Int32ToAString(int value, int nRadix = 10);
    static int StringToInt32(LPCSTR pszValue, int nRadix = 10);
};

