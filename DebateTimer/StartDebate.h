#pragma once
#include "afxwin.h"


// CStartDebate dialog

class CStartDebate : public CDialogEx
{
	DECLARE_DYNAMIC(CStartDebate)

public:
	CStartDebate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStartDebate();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	long m_alTimer[4];			// 四个时钟
	CButton m_btnStart;		// 开始按钮
	CButton m_btnStop;			// 停止按钮
	CButton m_btnResetThis;	// 重置本节
	CButton m_btnResetAll;		// 重置比赛	
	CButton m_btnLeft;			// 上一节
	CButton m_btnRight;		// 下一节
	CButton m_btnShowList;		// 显示列表
	CButton m_btnExit;			// 退出按钮
	CStatic m_stcTitle;		// 环节标题框
	CStatic m_stcShowTime;		// 计数器显示框
	CBrush m_brushBlue;		// 蓝色画刷

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnResetThis();
	afx_msg void OnBnClickedBtnResetAll();
	afx_msg void OnBnClickedBtnLeft();
	afx_msg void OnBnClickedBtnRight();
	afx_msg void OnBnClickedBtnShowlist();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
