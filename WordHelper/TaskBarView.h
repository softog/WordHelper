#pragma once

#include "JsonHelper.h"

// CTaskBarView

class CTaskBarView : public CWnd
{
	DECLARE_DYNAMIC(CTaskBarView)

public:
	CTaskBarView();
	virtual ~CTaskBarView();

public:
	BOOL Create();

protected:
	DECLARE_MESSAGE_MAP()

private:
    BOOL AdjustWindowPos();

private:
	HWND m_hTaskbar;	// 任务栏窗口句柄
	HWND m_hNotify;     // 任务栏通知区域的句柄
	CFont m_font;

public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CJsonHelper m_jsonRoot;
};


