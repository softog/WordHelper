#pragma once
class CUtils
{
public:
    // ��ȡ�豸DPI����
    static float GetDPIScale();

    // ����DPI����
    static BOOL SetProcessDPIAware();

    static CAtlStringA UnicodeToAnsi(LPCWSTR pszContent);
    static CAtlStringA Int32ToAString(int value, int nRadix = 10);
    static int StringToInt32(LPCSTR pszValue, int nRadix = 10);
};

