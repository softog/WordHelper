#pragma once

#include <string>
#include <memory>
#include <vector>

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
    CStringA Encode(BOOL bIsFormat = FALSE);
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
    CStringA Get(LPCSTR key, LPCSTR defaultValue);
    int GetInt32(LPCSTR key, int defaultValue = 0);
    CString GetStringWithUTF8(LPCSTR pszKey, LPCWSTR defaultValue);

public:
    // 数组字符串
    BOOL GetJsonArrayString(UINT nPos, std::string& strValue);
    BOOL GetJsonArrayStringWithUTF8(UINT nPos, CString& strValue);
    BOOL GetJsonArrayStringWithUTF8(LPCSTR key, std::vector<CString>& listString);

protected:
    LPVOID m_pJsonRoot = NULL;
    BOOL m_bIsDeleteRoot = TRUE;
};


