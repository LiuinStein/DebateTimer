// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "Core.h"
#include <algorithm>
#include "ParseJson.h"


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
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CSettingDlg::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_SAVEAS, &CSettingDlg::OnBnClickedBtnSaveas)
	ON_BN_CLICKED(IDC_BTN_SETDEFAULT, &CSettingDlg::OnBnClickedBtnSetdefault)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CSettingDlg::OnBnClickedBtnApply)
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
	m_drThisPage = g_drAllRules;		// 拷贝配置
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
	sort(m_drThisPage.begin(), m_drThisPage.end());
	CString tmp;
	for (int i = 0; i < m_drThisPage.size(); i++)
	{
		// 编号
		tmp.Format(_T("%d"), i + 1);
		m_listRule.InsertItem(i, tmp);
		// 项目名称
		tmp = m_drThisPage[i].m_strChapter.c_str();
		m_listRule.SetItemText(i, 1, tmp);
		// 每个时钟的时间
		tmp.Format(_T("%d"), m_drThisPage[i].m_nTime);
		m_listRule.SetItemText(i, 2, tmp);
		// 时钟数目
		tmp.Format(_T("%d"), m_drThisPage[i].m_nTimerNum);
		m_listRule.SetItemText(i, 3, tmp);
		// 时钟说明
		for (int j = 0; j < m_drThisPage[i].m_nTimerNum && j < m_drThisPage[i].m_vecTimerName.size(); j++)
		{
			tmp = m_drThisPage[i].m_vecTimerName[j].c_str();
			m_listRule.SetItemText(i, 4 + j, tmp);
		}
	}
}

// 保存按钮,如果是从别的文件导入的,那么将其保存到这个文件,如果是默认设置就将其保存至rule.json文件
void CSettingDlg::OnBnClickedBtnSave()
{
	if (!write_rule_to_file(m_drThisPage, m_strOpenFile.c_str()))
		MessageBoxW(_T("保存到文件失败"), 0, MB_OK | MB_ICONERROR);
	else
		MessageBoxW(CString{ ("成功保存至文件" + m_strOpenFile).c_str() }, 0, MB_OK | MB_ICONINFORMATION);
}

// 从文件导入规则按钮
void CSettingDlg::OnBnClickedBtnImport()
{
	// 弹出一个打开对话框
	CFileDialog openFile(TRUE, 0, NULL, OFN_HIDEREADONLY | OFN_READONLY, _T("配置文件 (*.json)|*.json||"), NULL);
	openFile.DoModal();
	CString cstrFilePath{ openFile.GetPathName() };
	if(cstrFilePath != _T(""))
	{
		USES_CONVERSION;
		m_strOpenFile = W2A(cstrFilePath);
		if (!get_rule_from_file(m_drThisPage, m_strOpenFile.c_str()))
		{
			MessageBoxW(_T("从文件中读取规则失败,请检查文件的合法性"), 0, MB_OK | MB_ICONERROR);
			return;
		}
		RefreshList();
	}
}

// 规则另存为按钮
void CSettingDlg::OnBnClickedBtnSaveas()
{
	// 弹出一个另存为对话框
	CFileDialog saveFile(FALSE, 0, 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("配置文件 (*.json)|*.json||"), NULL);
	saveFile.DoModal();
	CString cstrFilePath{ saveFile.GetPathName() };
	if (cstrFilePath != _T(""))
	{
		USES_CONVERSION;
		if (!write_rule_to_file(m_drThisPage, std::string(W2A(cstrFilePath)).c_str()))
		{
			MessageBoxW(_T("写入文件失败"), 0, MB_OK | MB_ICONERROR);
			return;
		}
		MessageBoxW(_T("规则成功写入文件"), 0, MB_OK | MB_ICONINFORMATION);
	}
}

// 载入默认规则按钮
void CSettingDlg::OnBnClickedBtnSetdefault()
{
	if(!get_rule_from_json(m_drThisPage, g_strDefaultRule))
	{
		MessageBoxW(_T("载入默认规则失败"), 0, MB_OK | MB_ICONERROR);
		return;
	}
	MessageBoxW(_T("载入默认规则成功"), 0, MB_OK | MB_ICONINFORMATION);
}

// 应用按钮
void CSettingDlg::OnBnClickedBtnApply()
{
	g_drAllRules = m_drThisPage;
	MessageBoxW(_T("应用规则成功"), 0, MB_OK | MB_ICONINFORMATION);
}
