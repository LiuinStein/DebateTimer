#pragma once
#include "afxcmn.h"
#include <string>
#include "DataStruct.h"
#include "afxwin.h"


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
	// 规则列表
	CListCtrl m_listRule;
	// List的浮动编辑框
	CEdit m_editListEdit;
	CEdit m_editListEditNum;
	CEdit * m_editopt;
	// 当前操作文件
	std::string m_strOpenFile;
	// 当前页面规则
	DebateRules m_drThisPage;
	// 是否进行了操作
	bool m_bIsOper;
	// 选中的行数
	int m_nClickListLine;
	// 选中的列数
	int m_nClickListCol;

public:
	void RefreshList();
	void SaveToFile();
	void ChangeList();
	void OnApplyList();
	void RefreshRules();
	void RefreshLineNum();
	void OnMoveLine(int __m);
	void OnInsertLine(int __m);
	afx_msg void OnBnClickedBtnSave();

public:
	afx_msg void OnBnClickedBtnImport();
public:
	afx_msg void OnBnClickedBtnSaveas();
	afx_msg void OnBnClickedBtnSetdefault();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeList();
	afx_msg void OnInsertUp();
	afx_msg void OnInsertDown();
	afx_msg void OnDeleteLine();
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEditList();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	afx_msg void OnKillfocusEditListNum();
};
