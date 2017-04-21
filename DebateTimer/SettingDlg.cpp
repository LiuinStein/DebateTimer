// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "DataStruct.h"
#include "Core.h"
#include <algorithm>


// CSettingDlg dialog

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listRule);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSettingDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CSettingDlg message handlers


BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_strOpenFile = g_strRuleFile;	// 设置默认操作文件
	// 初始化List
	m_listRule.SetExtendedStyle(m_listRule.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRule.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 60, 50);
	m_listRule.InsertColumn(1, _T("项目名称"), LVCFMT_CENTER, 150, 50);
	m_listRule.InsertColumn(2, _T("每个时钟的时间(秒)"), LVCFMT_CENTER, 150, 50);
	m_listRule.InsertColumn(3, _T("时钟数目"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(4, _T("时钟1说明"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(5, _T("时钟2说明"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(6, _T("时钟3说明"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(7, _T("时钟4说明"), LVCFMT_CENTER, 120, 50);
	// 刷新列表
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// 刷新列表
void CSettingDlg::RefreshList()
{
	sort(g_drAllRules.begin(), g_drAllRules.end());
	CString tmp;
	for (int i = 0; i < g_drAllRules.size(); i++)
	{
		// 编号
		tmp.Format(_T("%d"), i + 1);
		m_listRule.InsertItem(i, tmp);
		// 项目名称
		tmp = g_drAllRules[i].m_strChapter.c_str();
		m_listRule.SetItemText(i, 1, tmp);
		// 每个时钟的时间
		tmp.Format(_T("%d"), g_drAllRules[i].m_nTime);
		m_listRule.SetItemText(i, 2, tmp);
		// 时钟数目
		tmp.Format(_T("%d"), g_drAllRules[i].m_nTimerNum);
		m_listRule.SetItemText(i, 3, tmp);
		// 时钟说明
		for (int j = 0; j < g_drAllRules[i].m_nTimerNum && j < g_drAllRules[i].m_vecTimerName.size(); j++)
		{
			tmp = g_drAllRules[i].m_vecTimerName[j].c_str();
			m_listRule.SetItemText(i, 4 + j, tmp);
		}
	}
}

// 保存按钮,如果是从别的文件导入的,那么将其保存到这个文件,如果是默认设置就将其保存至rule.json文件
void CSettingDlg::OnBnClickedBtnSave()
{

}
