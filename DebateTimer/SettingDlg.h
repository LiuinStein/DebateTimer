#pragma once
#include "afxcmn.h"
#include <string>
#include "DataStruct.h"


// CSettingDlg dialog

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
private:
	// �����б�
	CListCtrl m_listRule;
	// ��ǰ�����ļ�
	std::string m_strOpenFile;
	// ��ǰҳ�����
	DebateRules m_drThisPage;
	// �Ƿ�����˲���
	bool m_bIsOper;

public:
	void RefreshList();
	void SaveToFile();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnSaveas();
	afx_msg void OnBnClickedBtnSetdefault();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();
};
