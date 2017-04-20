// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


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
	// ��ʼ��List
	m_listRule.SetExtendedStyle(m_listRule.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRule.InsertColumn(0, _T("���"), LVCFMT_CENTER, 60, 50);
	m_listRule.InsertColumn(1, _T("��Ŀ����"), LVCFMT_CENTER, 150, 50);
	m_listRule.InsertColumn(2, _T("ÿ��ʱ�ӵ�ʱ��(��)"), LVCFMT_CENTER, 150, 50);
	m_listRule.InsertColumn(3, _T("ʱ����Ŀ"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(4, _T("ʱ��1˵��"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(5, _T("ʱ��2˵��"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(6, _T("ʱ��3˵��"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(7, _T("ʱ��4˵��"), LVCFMT_CENTER, 120, 50);

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}