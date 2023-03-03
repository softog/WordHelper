#pragma once


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

	//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnPaint();
};


