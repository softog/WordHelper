#pragma once

#include "JsonHelper.h"
#include <map>

// CTaskBarView
struct WORD_PACK {
	



};

class CTaskBarView : public CView
{
	DECLARE_DYNAMIC(CTaskBarView)

public:
	CTaskBarView();
	virtual ~CTaskBarView();

public:
	BOOL Create(HWND hWnd);

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
	CJsonHelperPtr m_pJsonList;

	CString m_strWord;
	CString m_strWordPart;
	CString m_strWordMean;
	CString m_strWordMeanAll;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* /*pDC*/);
};


