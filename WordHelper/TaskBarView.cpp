// TaskBarView.cpp: 实现文件
//

#include "pch.h"
#include "WordHelper.h"
#include "TaskBarView.h"
#include <string>
using namespace std;
#include <cpr/cpr.h>
#include "third_party/cJSON/cJSON.h"


// CTaskBarView

IMPLEMENT_DYNAMIC(CTaskBarView, CWnd)

CTaskBarView::CTaskBarView()
{

}

CTaskBarView::~CTaskBarView()
{
}

BOOL CTaskBarView::Create()
{
    m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL); //寻找类名是Shell_TrayWnd的窗口句柄
    m_hNotify = ::FindWindowEx(m_hTaskbar, 0, L"TrayNotifyWnd", NULL);

    CRect rcTaskbar;
    ::GetWindowRect(m_hTaskbar, rcTaskbar);   //获得任务栏的矩形区域

    // 字体
    m_font.Attach((HFONT)GetStockObject(DEFAULT_GUI_FONT));

    TCHAR szExePath[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, szExePath, MAX_PATH);
    CAtlString strPath = CUtils::PathToFolderPath(szExePath);

    // 加载单词文件
    CFile file(strPath + _T("Data\\新概念英语第一册.json"), CFile::modeRead);
    char* pszBuf = new char[file.GetLength() + 1];
    ZeroMemory(pszBuf, file.GetLength() + 1);
    file.Read(pszBuf, file.GetLength());
    file.Close();
    m_jsonRoot.Parse(pszBuf);
    delete[] pszBuf;
    m_pJsonList = m_jsonRoot.GetJsonArray("list");
    if (!m_pJsonList) {
        return FALSE;
    }


    // CJsonHelperPtr pJsonList1 = pJsonList->GetJsonObject("Lesson1");
    // if (!pJsonList1) {
    //     return FALSE;
    // }
    //  CJsonHelperPtr pJsonList = m_jsonRoot.GetJsonArray("Lesson1");
    //  if (!pJsonList) {
    //      return FALSE;
    //  }


     // string str = item1->Get("key","");


     // cJSON* pListJson = cJSON_GetObjectItem(pRootJson, "list");
     // if (pListJson == NULL) {
     //     return false;
     // }
     //

    BOOL bCreate = __super::Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE, CRect(0, 0, 150 * CUtils::GetDPIScale(), rcTaskbar.Height() * CUtils::GetDPIScale()), CWnd::FromHandle(m_hTaskbar), 0, nullptr);
    if (!bCreate) {
        return FALSE;
    }

    AdjustWindowPos();

    SetTimer(MY_TIMER_TASKBAR_REPOSITION_ID, MY_TIMER_TASKBAR_REPOSITION, NULL);
    SetTimer(MY_TIMER_TASKBAR_UPDATE_WORD_ID, MY_TIMER_TASKBAR_UPDATE_WORD, NULL);

    return bCreate;
}

BOOL CTaskBarView::AdjustWindowPos()
{
    if (this->GetSafeHwnd() == NULL || !IsWindow(this->GetSafeHwnd()))
        return false;

    CRect rcTaskbar, rcNotify, rcClient;
    ::GetWindowRect(m_hTaskbar, rcTaskbar);   //获得任务栏的矩形区域
    ::GetWindowRect(m_hNotify, rcNotify);
    GetWindowRect(rcClient);

    SetWindowPos(NULL, rcNotify.left - rcClient.Width(), (rcTaskbar.Height() - rcClient.Height()) / 2, 0, 0, SWP_NOSIZE);

    //Invalidate(TRUE);
    //  cpr::Response r = cpr::Get(cpr::Url{ "https://ip.clearseve.com/api" },
    //      cpr::Authentication{ "user", "pass", cpr::AuthMode::BASIC },
    //      cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
    //  r.status_code;                  // 200
    //  r.header["content-type"];       // application/json; charset=utf-8
    //  r.text;                         // JSON text string
    return TRUE;
}


BEGIN_MESSAGE_MAP(CTaskBarView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



void CTaskBarView::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect rcClient;
    GetWindowRect(rcClient);

    CFont* pOldFont = dc.SelectObject(&m_font);
    CString strWord = m_strWord;
    CString strDescribe = _T("n. 借口；理由；道歉；");

    // 计算文字绘制的开始位置
    SIZE size = dc.GetTextExtent(strDescribe);
    int nStart = (rcClient.Height() - size.cy * 2) / 2;
    if (size.cx > rcClient.Width()) {
        nStart = (rcClient.Height() - size.cy * 3) / 2;
    }


    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(255, 255, 255));
    dc.DrawText(strWord, CRect(0, nStart, rcClient.Width(), nStart + size.cy), DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS);
    dc.DrawText(strDescribe, CRect(0, nStart + size.cy + 1, rcClient.Width(), nStart + size.cy * 3), DT_WORDBREAK | DT_LEFT | DT_END_ELLIPSIS);


    dc.SelectObject(pOldFont);
}

void CTaskBarView::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == MY_TIMER_TASKBAR_REPOSITION_ID) {
        AdjustWindowPos();
    }
    else if (nIDEvent == MY_TIMER_TASKBAR_UPDATE_WORD_ID) {
        Invalidate(TRUE);

        static int nClock = 0;
        static int nWordIndex = 0;
        static int nWordMeanIndex = 0;

        // 加载单词
        if (nClock == 0) {
            CJsonHelperPtr jsonItem = m_pJsonList->GetArrayItemAt(0);
            string name = jsonItem->Get("name", "");
            CJsonHelperPtr wordArr = jsonItem->GetJsonArray("words");

            // words / 2
            int nWordCount = wordArr->GetArrayCount();

            
            wordArr->GetArrayItemAt(nWordIndex);
            CJsonHelperPtr pWordItem = wordArr->GetArrayItemAt(nWordIndex);
            m_strWord = pWordItem->GetStringWithUTF8("word", _T(""));

        }

        // 60 更换单词



       // 
       //  int nCount = m_pJsonList->GetArrayCount();
       // 
       //  CJsonHelperPtr jsonItem = m_pJsonList->GetArrayItemAt(0);
       //  string name = jsonItem->Get("name", "");
       //  CJsonHelperPtr words = jsonItem->GetJsonArray("words");
       // 
       //  int nWordCount = words->GetArrayCount();

        // for (size_t i = 0; i < nCount; i++)
        // {
        //     CJsonHelperPtr jsonItem = m_pJsonList->GetArrayItemAt(i);
        //     string name = jsonItem->Get("name", "");
        //     CJsonHelperPtr words = jsonItem->GetJsonArray("words");
        // 
        //     int nWordCount = words->GetArrayCount();
        //     for (size_t i = 0; i < nWordCount; i++) {
        // 
        //     }
        // 
        // }

        if (nClock++ > 60) {
            nClock = 0;
        }
    }
    CWnd::OnTimer(nIDEvent);
}



BOOL CTaskBarView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    //CRect draw_rect;
    //GetClientRect(draw_rect);
    //pDC->FillSolidRect(draw_rect, GetSysColor(COLOR_WINDOW));
    CBrush brush;
    brush.FromHandle((HBRUSH)GetStockObject(GRAY_BRUSH));
 
    CRect rect;
    GetClientRect(rect);
    pDC->FillRect(rect, &brush);


    return TRUE;
    //return CWnd::OnEraseBkgnd(pDC);
}


BOOL CTaskBarView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CWnd::PreCreateWindow(cs);
}
