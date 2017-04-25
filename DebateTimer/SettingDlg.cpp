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
	DDX_Control(pDX, IDC_EDIT_LIST, m_editListEdit);
	DDX_Control(pDX, IDC_EDIT_LIST_NUM, m_editListEditNum);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSettingDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CSettingDlg::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_SAVEAS, &CSettingDlg::OnBnClickedBtnSaveas)
	ON_BN_CLICKED(IDC_BTN_SETDEFAULT, &CSettingDlg::OnBnClickedBtnSetdefault)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CSettingDlg::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSettingDlg::OnBnClickedBtnCancel)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CSettingDlg::OnRclickList)
	ON_COMMAND(ID_32773, &CSettingDlg::OnChangeList)
	ON_COMMAND(ID_32774, &CSettingDlg::OnInsertUp)
	ON_COMMAND(ID__32775, &CSettingDlg::OnInsertDown)
	ON_COMMAND(ID__32776, &CSettingDlg::OnDeleteLine)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSettingDlg::OnDblclkList)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST, &CSettingDlg::OnKillfocusEditList)
	ON_COMMAND(ID__32777, &CSettingDlg::OnMoveUp)
	ON_COMMAND(ID__32778, &CSettingDlg::OnMoveDown)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST_NUM, &CSettingDlg::OnKillfocusEditListNum)
END_MESSAGE_MAP()


// CSettingDlg message handlers


BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnApplyList();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_strOpenFile = g_strRuleFile;	// ����Ĭ�ϲ����ļ�
	m_drThisPage = g_drAllRules;		// ��������
	m_bIsOper = false;					// Ĭ��û���в���
	m_nClickListLine = -1;				// Ĭ��û��ѡ����
	m_nClickListCol = -1;				// Ĭ��û��ѡ����
	m_editopt = nullptr;				// ��ʼ������ָ��
	m_editListEdit.ShowWindow(SW_HIDE);	// ���ø����ı��򲻿ɼ�
	m_editListEditNum.ShowWindow(SW_HIDE);
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

// ���浽�ļ�
void CSettingDlg::SaveToFile()
{
	RefreshRules();
	if (!write_rule_to_file(m_drThisPage, m_strOpenFile.c_str()))
		MessageBoxW(_T("���浽�ļ�ʧ��"), 0, MB_OK | MB_ICONERROR);
	else
		MessageBoxW(CString{ ("�ɹ��������ļ�" + m_strOpenFile).c_str() }, 0, MB_OK | MB_ICONINFORMATION);
}

// �޸��б�
void CSettingDlg::ChangeList()
{
	if(m_nClickListCol > 0)
	{
		m_editopt = m_nClickListCol == 2 || m_nClickListCol == 3 ? &m_editListEditNum : &m_editListEdit;
		// ���ѡ���������
		CRect rc;
		// ��ȡ�����RECT
		m_listRule.GetSubItemRect(m_nClickListLine, m_nClickListCol, LVIR_LABEL, rc);
		// ת�����굽�б���е�����
		m_editopt->SetParent(&m_listRule);
		// ���ı����ƶ���RECT��ʾ��Χ
		m_editopt->MoveWindow(rc);
		// �������е�ֵ����Edit�ؼ���
		m_editopt->SetWindowTextW(m_listRule.GetItemText(m_nClickListLine, m_nClickListCol));
		// ��ʾ�ı���
		m_editopt->ShowWindow(SW_SHOW);
		// ���ý���
		m_editopt->SetFocus();
		// ���ù��
		m_editopt->ShowCaret();
		// ����Ƶ����
		m_editopt->SetSel(-1);
	}
}

// ���ı���ʧȥ������»س�ʱ
void CSettingDlg::OnApplyList()
{
	if (!m_editopt)
		return;
	CString tmp;
	m_editopt->GetWindowTextW(tmp);
	m_listRule.SetItemText(m_nClickListLine, m_nClickListCol, tmp);
	m_editopt->ShowWindow(SW_HIDE);
}

// �����б�ˢ�¹���
void CSettingDlg::RefreshRules()
{
	m_drThisPage.clear();
	USES_CONVERSION;
	for (int i = 0, j = 0; i < m_listRule.GetItemCount(); i++)
	{
		if (m_listRule.GetItemText(j, 2).IsEmpty() || m_listRule.GetItemText(j, 3).IsEmpty())
			continue;
		SRule tmp;
		tmp.m_nID = _ttoi(m_listRule.GetItemText(j, 0));
		tmp.m_strChapter = W2A(m_listRule.GetItemText(j, 1));
		tmp.m_nTime = _ttoi(m_listRule.GetItemText(j, 2));
		tmp.m_nTimerNum = _ttoi(m_listRule.GetItemText(j, 3));
		for (int p = 4; p < 8; p++)
		{
			if (0 != m_listRule.GetItemText(j, p).GetLength())
			{
				tmp.m_vecTimerName.push_back(W2A(m_listRule.GetItemText(j, p)));
			}
		}
		j++;
		m_drThisPage.push_back(tmp);
	}
}

// ˢ���б���
void CSettingDlg::RefreshLineNum()
{
	CString tmp;
	for (int i = 0; i < m_listRule.GetItemCount(); i++)
	{
		tmp.Format(_T("%d"), i + 1);
		m_listRule.SetItemText(i, 0, tmp);
	}
}

// ���б���еĵ�ǰ�����ϻ������ƶ�__m����λ����,__mΪ�������ƶ�,Ϊ�������ƶ�
void CSettingDlg::OnMoveLine(int __m)
{
	if (__m != 0 && m_nClickListLine + __m < m_listRule.GetItemCount() && m_nClickListLine + __m >= 0)
	{
		// �����ƶ������е�����
		CString tmp;
		int n1{ m_nClickListLine }, n2{ m_nClickListLine + __m };
		for (int i = 1; i < 8; i++)
		{
			tmp = m_listRule.GetItemText(n1, i);
			m_listRule.SetItemText(n1, i, m_listRule.GetItemText(n2, i));
			m_listRule.SetItemText(n2, i, tmp);
		}
	}
}

// ���б��ǰ��Ϊ��׼,���ϻ����²�����,__mΪ�����²���,Ϊ�����ϲ���
void CSettingDlg::OnInsertLine(int __m)
{
	// ���ϲ�������²��붼���б����ƵĹ���
	m_listRule.InsertItem(m_nClickListLine + __m,_T(""));
	RefreshLineNum();
}

// ���水ť,����Ǵӱ���ļ������,��ô���䱣�浽����ļ�,�����Ĭ�����þͽ��䱣����rule.json�ļ�
void CSettingDlg::OnBnClickedBtnSave()
{
	SaveToFile();
}

// ���ļ��������ť
void CSettingDlg::OnBnClickedBtnImport()
{
	// ����һ���򿪶Ի���
	CFileDialog openFile(TRUE, 0, NULL, OFN_HIDEREADONLY | OFN_READONLY, _T("�����ļ� (*.json)|*.json|�����ļ� (*.*)|*.*||"), NULL);
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
	CFileDialog saveFile(FALSE, 0, 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("�����ļ� (*.json)|*.json|�����ļ� (*.*)|*.*||"), NULL);
	saveFile.DoModal();
	RefreshRules();
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
	if (IDNO == MessageBoxW(_T("����Ĭ�����ú�ǰ�ĸ��Ľ��ᱻ����,�Ƿ�ȷ��"), 0, MB_YESNO | MB_ICONINFORMATION))
		return;
	if(!get_rule_from_json(m_drThisPage, g_strDefaultRule))
	{
		MessageBoxW(_T("����Ĭ�Ϲ���ʧ��"), 0, MB_OK | MB_ICONERROR);
		return;
	}
	RefreshList();
	MessageBoxW(_T("����Ĭ�Ϲ���ɹ�"), 0, MB_OK | MB_ICONINFORMATION);
}

// Ӧ�ð�ť
void CSettingDlg::OnBnClickedBtnApply()
{
	RefreshRules();
	g_drAllRules = m_drThisPage;
	MessageBoxW(_T("Ӧ�ù���ɹ�"), 0, MB_OK | MB_ICONINFORMATION);
}

// ȡ����ť
void CSettingDlg::OnBnClickedBtnCancel()
{
	if(m_bIsOper && IDYES == MessageBoxW(_T("�Ƿ񽫸��ı��浽�����ļ�"),0,MB_YESNO|MB_ICONINFORMATION))
		SaveToFile();
	this->OnCancel();
}


// �Ҽ��б�ĳһ������¼���Ӧ
void CSettingDlg::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW * pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	m_nClickListLine = pNMListView->iItem;	// ��ȡѡ������Ϣ
	m_nClickListCol = pNMListView->iSubItem;	// ��ȡѡ�е�����Ϣ
	POSITION pos = m_listRule.GetFirstSelectedItemPosition();
	if (m_listRule.GetNextSelectedItem(pos) == -1)
		return;		//���û��ѡ�е���Ŀ������
	//��ʾ�����˵�
	CPoint point;
	GetCursorPos(&point);
	CMenu menu;
	menu.LoadMenu(IDR_MENU_SETTING);//��ȡ�˵�����Դ
	CMenu* popup = menu.GetSubMenu(0);//ֻ��ȡ��һ���в˵���ָ��
	//�����˵���ʾ
	popup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);
	*pResult = 0;
}

// �Ҽ��˵��б༭��ť
void CSettingDlg::OnChangeList()
{
	ChangeList();
}

// �Ҽ��˵����ϲ���
void CSettingDlg::OnInsertUp()
{
	OnInsertLine(0);
}

// �Ҽ��˵����²���
void CSettingDlg::OnInsertDown()
{
	OnInsertLine(1);
}

// �Ҽ��˵�ɾ������
void CSettingDlg::OnDeleteLine()
{
	m_listRule.DeleteItem(m_nClickListLine);
	RefreshLineNum();
}

// ˫��List���¼���Ӧ
void CSettingDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW * pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	m_nClickListLine = pNMListView->iItem;	// ��ȡѡ������Ϣ
	m_nClickListCol = pNMListView->iSubItem;	// ��ȡѡ�е�����Ϣ
	POSITION pos = m_listRule.GetFirstSelectedItemPosition();
	if (m_listRule.GetNextSelectedItem(pos) == -1)
		return;		//���û��ѡ�е���Ŀ������
	ChangeList();
	*pResult = 0;
}

// �б��ı���ʧȥ����
void CSettingDlg::OnKillfocusEditList()
{
	OnApplyList();
}

// �����ƶ���ť
void CSettingDlg::OnMoveUp()
{
	OnMoveLine(-1);
}

// �����ƶ���ť
void CSettingDlg::OnMoveDown()
{
	OnMoveLine(1);
}

// �б��ı���ʧȥ����
void CSettingDlg::OnKillfocusEditListNum()
{
	OnApplyList();
}
