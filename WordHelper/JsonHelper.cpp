#include "pch.h"
#include "JsonHelper.h"
#include "third_party/cJSON/cJSON.h"


CJsonHelper::CJsonHelper()
{
    m_bIsDeleteRoot = FALSE;
}

CJsonHelper::CJsonHelper(LPCSTR pszJson)
{
    Parse(pszJson);
}

CJsonHelper::CJsonHelper(LPVOID pJson)
{
    m_pJsonRoot = pJson;
    m_bIsDeleteRoot = FALSE;
}

CJsonHelper::~CJsonHelper()
{
    if (m_bIsDeleteRoot) {
        cJSON_Delete((cJSON*)m_pJsonRoot);
    }
}

BOOL CJsonHelper::CreateJsonObject()
{
    m_pJsonRoot = cJSON_CreateObject();
    return TRUE;
}

BOOL CJsonHelper::CreateJsonArray()
{
    m_pJsonRoot = cJSON_CreateArray();
    return TRUE;
}

BOOL CJsonHelper::Parse(LPCSTR pszJson)
{
    if (!pszJson) {
        return FALSE;
    }

    m_pJsonRoot = cJSON_Parse(pszJson);
    if (!m_pJsonRoot) {
        return FALSE;
    }

    m_bIsDeleteRoot = TRUE;
    return TRUE;
}

CAtlStringA CJsonHelper::Encode(BOOL bIsFormat/* = FALSE*/)
{
    char* pszPrintJsonTmp = NULL;
    if (bIsFormat) {
        pszPrintJsonTmp = cJSON_Print((cJSON*)m_pJsonRoot);
    }
    else {
        pszPrintJsonTmp = cJSON_PrintUnformatted((cJSON*)m_pJsonRoot);

    }

    if (NULL == pszPrintJsonTmp) {
        return "";
    }

    CAtlStringA strRefJson;
    strRefJson = pszPrintJsonTmp;
    delete pszPrintJsonTmp;

    return strRefJson;
}

BOOL CJsonHelper::IsArray()
{
    cJSON* pJson = (cJSON*)m_pJsonRoot;
    return pJson && pJson->type == cJSON_Array;
}

UINT CJsonHelper::GetArrayCount()
{
    if (!IsArray()) {
        return 0;
    }
    return cJSON_GetArraySize((cJSON*)m_pJsonRoot);
}

BOOL CJsonHelper::HasKey(LPCSTR pszKey)
{
    cJSON* pJson = (cJSON*)m_pJsonRoot;
    return pJson && cJSON_HasObjectItem(pJson, pszKey);
}

BOOL CJsonHelper::Set(LPCSTR key, CJsonHelper& jsonObject)
{
    BOOL bAddSuccess = cJSON_AddItemToObject((cJSON*)m_pJsonRoot, key, (cJSON*)jsonObject.m_pJsonRoot);
    jsonObject.m_bIsDeleteRoot = FALSE;
    return bAddSuccess;
}

BOOL CJsonHelper::Set(LPCSTR key, LPCSTR value)
{
    if (!m_pJsonRoot || !key) {
        return FALSE;
    }
    return cJSON_AddItemToObject((cJSON*)m_pJsonRoot, key, cJSON_CreateString(value));
}

BOOL CJsonHelper::Set(LPCSTR pszKey, LPCWSTR pszValue)
{
    return Set(pszKey, CUtils::UnicodeToAnsi(pszValue));
}

BOOL CJsonHelper::Set(LPCSTR pszKey, int nValue)
{
    if (!m_pJsonRoot || !pszKey) {
        return FALSE;
    }
    return cJSON_AddItemToObject((cJSON*)m_pJsonRoot, pszKey, cJSON_CreateNumber(nValue));
}

CJsonHelperPtr CJsonHelper::GetJsonObject(LPCSTR key)
{
    if (!m_pJsonRoot || !key) {
        return NULL;
    }

    cJSON* pJson = cJSON_GetObjectItem((cJSON*)m_pJsonRoot, key);
    if (pJson == NULL) {
        return NULL;
    }

    if (pJson->type != cJSON_Object) {
        return NULL;
    }

    return std::make_shared<CJsonHelper>(pJson);
}

CJsonHelperPtr CJsonHelper::GetJsonArray(LPCSTR key)
{
    if (!m_pJsonRoot || !key) {
        return NULL;
    }

    cJSON* pJson = cJSON_GetObjectItem((cJSON*)m_pJsonRoot, key);
    if (pJson == NULL) {
        return NULL;
    }

    if (pJson->type != cJSON_Array) {
        return NULL;
    }

    return std::make_shared<CJsonHelper>(pJson);
}
CJsonHelperPtr CJsonHelper::GetArrayItemAt(UINT nPos)
{
    if (!IsArray()) {
        return NULL;
    }

    cJSON* item = cJSON_GetArrayItem((cJSON*)m_pJsonRoot, nPos);
    return std::make_shared<CJsonHelper>(item);
}
CAtlStringA CJsonHelper::Get(LPCSTR key, LPCSTR defaultValue)
{
    CAtlStringA strRefValue = defaultValue;

    if (!m_pJsonRoot) {
        return strRefValue;
    }

    cJSON* pJson = cJSON_GetObjectItem((cJSON*)m_pJsonRoot, key);
    if (pJson == NULL) {
        return strRefValue;
    }

    if (pJson->type == cJSON_Number) {
        strRefValue = CUtils::Int32ToAString(pJson->valueint);
    }
    else if (pJson->type == cJSON_String && pJson->valuestring) {
        strRefValue = pJson->valuestring;
    }
    return strRefValue;
}

int CJsonHelper::GetInt32(LPCSTR key, int defaultValue/* = 0*/)
{
    if (!m_pJsonRoot) {
        return defaultValue;
    }

    cJSON* pJson = cJSON_GetObjectItem((cJSON*)m_pJsonRoot, key);
    if (pJson == NULL) {
        return defaultValue;
    }

    if (pJson->type == cJSON_Number || pJson->type == cJSON_True || pJson->type == cJSON_False) {
        return pJson->valueint;
    }

    if (pJson->type == cJSON_String) {
        return CUtils::StringToInt32(pJson->valuestring);
    }

    return defaultValue;
}

CString CJsonHelper::GetStringWithUTF8(LPCSTR pszKey, LPCWSTR defaultValue)
{
    CAtlStringA val = Get(pszKey, CUtils::UnicodeToAnsi(defaultValue));
    return CUtils::UTF8ToUnicode(val);
}

BOOL CJsonHelper::GetJsonArrayString(UINT nPos, std::string& strValue)
{
    if (!IsArray()) {
        return FALSE;
    }

    cJSON* item = cJSON_GetArrayItem((cJSON*)m_pJsonRoot, nPos);
    strValue = item->valuestring;
    return TRUE;
}
