// TaskBarView.cpp: 实现文件
//

#include "pch.h"
#include "WordHelper.h"
#include "TaskBarView.h"




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

    BOOL bCreate = __super::Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 32), CWnd::FromHandle(m_hTaskbar), 0, nullptr);
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

    return TRUE;
}


BEGIN_MESSAGE_MAP(CTaskBarView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
END_MESSAGE_MAP()



void CTaskBarView::OnPaint()
{

    CPaintDC dc(this); // device context for painting
    dc.TextOut(0, 0, _T("Hello World!"));
}


void CTaskBarView::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == MY_TIMER_TASKBAR_REPOSITION_ID) {
        AdjustWindowPos();
    }
    CWnd::OnTimer(nIDEvent);
}
