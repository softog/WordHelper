#pragma once

#include <string>
#include <memory>

class CJsonHelper;
typedef std::shared_ptr<CJsonHelper> CJsonHelperPtr;

class CJsonHelper
{
public:
    CJsonHelper();
    CJsonHelper(LPCSTR pszJson);
    CJsonHelper(LPVOID pJson);
    virtual ~CJsonHelper();

public:
    BOOL CreateJsonObject();
    BOOL CreateJsonArray();
    BOOL Parse(LPCSTR pszJson);
    CAtlStringA Encode(BOOL bIsFormat = FALSE);
    BOOL IsArray();
    UINT GetArrayCount();
    // 是否存在key
    BOOL HasKey(LPCSTR pszKey);

public:
    BOOL Set(LPCSTR key, CJsonHelper& jsonObject);
    BOOL Set(LPCSTR key, LPCSTR value);
    BOOL Set(LPCSTR pszKey, LPCWSTR pszValue);
    BOOL Set(LPCSTR pszKey, int nValue);

public:
    CJsonHelperPtr GetJsonObject(LPCSTR key);
    CJsonHelperPtr GetJsonArray(LPCSTR key);
    CJsonHelperPtr GetArrayItemAt(UINT nPos);
    CAtlStringA Get(LPCSTR key, LPCSTR defaultValue);
    int GetInt32(LPCSTR key, int defaultValue = 0);

public:
    // 数组字符串
    BOOL GetJsonArrayString(UINT nPos, std::string& strValue);

    // BOOL GetStringWithUTF8(LPCSTR pszKey, CString& strValue);
protected:
    LPVOID m_pJsonRoot = NULL;
    BOOL m_bIsDeleteRoot = TRUE;
};


