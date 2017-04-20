#pragma once


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
public:
	afx_msg void OnBnClickedButton5();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
