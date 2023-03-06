// TaskBarView.cpp: 实现文件
//

#include "pch.h"
#include "WordHelper.h"
#include "TaskBarView.h"
#include <string>
using namespace std;
#include <cpr/cpr.h>




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

    // 字体
    m_font.Attach((HFONT)GetStockObject(DEFAULT_GUI_FONT));

    BOOL bCreate = __super::Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE, CRect(0, 0, 150, 32), CWnd::FromHandle(m_hTaskbar), 0, nullptr);
    if (!bCreate) {
        return FALSE;
    }

    AdjustWindowPos();

    SetTimer(MY_TIMER_TASKBAR_REPOSITION_ID, MY_TIMER_TASKBAR_REPOSITION, NULL);
    return bCreate;
}

BOOL CTaskBarView::AdjustWindowPos()
{
    if (this->GetSafeHwnd() == NULL || !IsWindow(this->GetSafeHwnd()))
        return false;

    CRect rcTaskbar, rcNotify;
    ::GetWindowRect(m_hTaskbar, rcTaskbar);   //获得任务栏的矩形区域
    ::GetWindowRect(m_hNotify, rcNotify);

    SetWindowPos(NULL, rcNotify.left - 100, (rcTaskbar.Height() - 32) / 2, 0, 0, SWP_NOSIZE);
    Invalidate(FALSE);

    cpr::Response r = cpr::Get(cpr::Url{ "https://ip.clearseve.com/api" },
        cpr::Authentication{ "user", "pass", cpr::AuthMode::BASIC },
        cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
    return TRUE;
}


BEGIN_MESSAGE_MAP(CTaskBarView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
END_MESSAGE_MAP()



void CTaskBarView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CFont* pOldFont = dc.SelectObject(&m_font);

    dc.DrawText(_T("one"), CRect(0, 0, 150, 32 / 2), DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS);
    dc.DrawText(_T("pron.一个人,任何人,本人，人家,东西;"), CRect(0, 32 / 2, 150, 32), DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS);

    dc.SelectObject(pOldFont);


}


void CTaskBarView::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == MY_TIMER_TASKBAR_REPOSITION_ID) {
        AdjustWindowPos();
    }
    CWnd::OnTimer(nIDEvent);
}
