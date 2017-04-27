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
	long m_alTimer[4];			// �ĸ�ʱ��
	CButton m_btnStart;		// ��ʼ��ť
	CButton m_btnStop;			// ֹͣ��ť
	CButton m_btnResetThis;	// ���ñ���
	CButton m_btnResetAll;		// ���ñ���	
	CButton m_btnLeft;			// ��һ��
	CButton m_btnRight;		// ��һ��
	CButton m_btnShowList;		// ��ʾ�б�
	CButton m_btnExit;			// �˳���ť
	CStatic m_stcTitle;		// ���ڱ����
	CStatic m_stcShowTime;		// ��������ʾ��
	CBrush m_brushBlue;		// ��ɫ��ˢ

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
