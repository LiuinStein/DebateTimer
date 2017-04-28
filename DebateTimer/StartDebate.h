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
	int m_aTimer[2];			// ��������ʱ��
	bool m_bActiveFirst;		// Ϊtrue��ʱ���һ��ʱ�Ӽ���,Ϊfalse��ʱ��ڶ���ʱ�Ӽ���
	bool m_bStartFirst;		// Ϊtrue��ʱ��Ϊ��һ��������Ŀ,Ϊfalse��ʱ��Ϊ�ڶ���������Ŀ
	bool m_bIsStop;			// �����ͣ��ť�Ὣ����Ϊtrue
	int m_nItemNum;			// ���е��ڼ�������
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
	CStatic m_stcTimerName;	// ���������ƿ�
	CBrush m_brushBlue;		// ��ɫ��ˢ
	CFont m_font;				// ����
	CListCtrl m_listRule;		// �����б��


	// ���þ�̬�ı���������С
	void SetStaticCtlFontSize(CStatic & __s, double __nps);
	// ��ӡ��Ŀ����
	void PrintTitle();
	// ��ӡ����������
	void PrintTimerName();
	// ����ʱ��
	void ResetTimer();
	// ��ӡʱ����Ϣ
	void PrintTimer();
	// ���ñ���
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
