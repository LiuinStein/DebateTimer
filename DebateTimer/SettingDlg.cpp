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
	m_strOpenFile = g_strRuleFile;	// ����Ĭ�ϲ����ļ�
	m_drThisPage = g_drAllRules;		// ��������
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
	// ˢ���б�
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// ˢ���б�
void CSettingDlg::RefreshList()
{
	sort(m_drThisPage.begin(), m_drThisPage.end());
	CString tmp;
	for (int i = 0; i < m_drThisPage.size(); i++)
	{
		// ���
		tmp.Format(_T("%d"), i + 1);
		m_listRule.InsertItem(i, tmp);
		// ��Ŀ����
		tmp = m_drThisPage[i].m_strChapter.c_str();
		m_listRule.SetItemText(i, 1, tmp);
		// ÿ��ʱ�ӵ�ʱ��
		tmp.Format(_T("%d"), m_drThisPage[i].m_nTime);
		m_listRule.SetItemText(i, 2, tmp);
		// ʱ����Ŀ
		tmp.Format(_T("%d"), m_drThisPage[i].m_nTimerNum);
		m_listRule.SetItemText(i, 3, tmp);
		// ʱ��˵��
		for (int j = 0; j < m_drThisPage[i].m_nTimerNum && j < m_drThisPage[i].m_vecTimerName.size(); j++)
		{
			tmp = m_drThisPage[i].m_vecTimerName[j].c_str();
			m_listRule.SetItemText(i, 4 + j, tmp);
		}
	}
}

// ���水ť,����Ǵӱ���ļ������,��ô���䱣�浽����ļ�,�����Ĭ�����þͽ��䱣����rule.json�ļ�
void CSettingDlg::OnBnClickedBtnSave()
{
	if (!write_rule_to_file(m_drThisPage, m_strOpenFile.c_str()))
		MessageBoxW(_T("���浽�ļ�ʧ��"), 0, MB_OK | MB_ICONERROR);
	else
		MessageBoxW(CString{ ("�ɹ��������ļ�" + m_strOpenFile).c_str() }, 0, MB_OK | MB_ICONINFORMATION);
}

// ���ļ��������ť
void CSettingDlg::OnBnClickedBtnImport()
{
	// ����һ���򿪶Ի���
	CFileDialog openFile(TRUE, 0, NULL, OFN_HIDEREADONLY | OFN_READONLY, _T("�����ļ� (*.json)|*.json||"), NULL);
	openFile.DoModal();
	CString cstrFilePath{ openFile.GetPathName() };
	if(cstrFilePath != _T(""))
	{
		USES_CONVERSION;
		m_strOpenFile = W2A(cstrFilePath);
		if (!get_rule_from_file(m_drThisPage, m_strOpenFile.c_str()))
		{
			MessageBoxW(_T("���ļ��ж�ȡ����ʧ��,�����ļ��ĺϷ���"), 0, MB_OK | MB_ICONERROR);
			return;
		}
		RefreshList();
	}
}

// �������Ϊ��ť
void CSettingDlg::OnBnClickedBtnSaveas()
{
	// ����һ�����Ϊ�Ի���
	CFileDialog saveFile(FALSE, 0, 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("�����ļ� (*.json)|*.json||"), NULL);
	saveFile.DoModal();
	CString cstrFilePath{ saveFile.GetPathName() };
	if (cstrFilePath != _T(""))
	{
		USES_CONVERSION;
		if (!write_rule_to_file(m_drThisPage, std::string(W2A(cstrFilePath)).c_str()))
		{
			MessageBoxW(_T("д���ļ�ʧ��"), 0, MB_OK | MB_ICONERROR);
			return;
		}
		MessageBoxW(_T("����ɹ�д���ļ�"), 0, MB_OK | MB_ICONINFORMATION);
	}
}

// ����Ĭ�Ϲ���ť
void CSettingDlg::OnBnClickedBtnSetdefault()
{
	if(!get_rule_from_json(m_drThisPage, g_strDefaultRule))
	{
		MessageBoxW(_T("����Ĭ�Ϲ���ʧ��"), 0, MB_OK | MB_ICONERROR);
		return;
	}
	MessageBoxW(_T("����Ĭ�Ϲ���ɹ�"), 0, MB_OK | MB_ICONINFORMATION);
}

// Ӧ�ð�ť
void CSettingDlg::OnBnClickedBtnApply()
{
	g_drAllRules = m_drThisPage;
	MessageBoxW(_T("Ӧ�ù���ɹ�"), 0, MB_OK | MB_ICONINFORMATION);
}
