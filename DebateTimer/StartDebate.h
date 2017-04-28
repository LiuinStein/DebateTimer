#pragma once
#include "afxwin.h"
#include "afxcmn.h"


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
	int m_aTimer[2];			// 定义两个时钟
	bool m_bActiveFirst;		// 为true的时候第一个时钟激活,为false的时候第二个时钟激活
	bool m_bStartFirst;		// 为true的时候为第一次启动项目,为false的时候为第二次启动项目
	bool m_bIsStop;			// 点击暂停按钮会将其置为true
	int m_nItemNum;			// 进行到第几个环节
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
	CStatic m_stcTimerName;	// 计数器名称框
	CBrush m_brushBlue;		// 蓝色画刷
	CFont m_font;				// 字体
	CListCtrl m_listRule;		// 规则列表框


	// 设置静态文本框的字体大小
	void SetStaticCtlFontSize(CStatic & __s, double __nps);
	// 打印项目标题
	void PrintTitle();
	// 打印计数器名称
	void PrintTimerName();
	// 重置时钟
	void ResetTimer();
	// 打印时钟信息
	void PrintTimer();
	// 重置本节
	void ResetItem();

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
	afx_msg void OnDblclkListShowrulelist(NMHDR *pNMHDR, LRESULT *pResult);
};
