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
	m_strOpenFile = g_strRuleFile;	// 设置默认操作文件
	m_drThisPage = g_drAllRules;		// 拷贝配置
	m_bIsOper = false;					// 默认没进行操作
	m_nClickListLine = -1;				// 默认没有选中行
	m_nClickListCol = -1;				// 默认没有选中列
	m_editopt = nullptr;				// 初始化操作指针
	m_editListEdit.ShowWindow(SW_HIDE);	// 设置浮动文本框不可见
	m_editListEditNum.ShowWindow(SW_HIDE);
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

// 保存到文件
void CSettingDlg::SaveToFile()
{
	RefreshRules();
	if (!write_rule_to_file(m_drThisPage, m_strOpenFile.c_str()))
		MessageBoxW(_T("保存到文件失败"), 0, MB_OK | MB_ICONERROR);
	else
		MessageBoxW(CString{ ("成功保存至文件" + m_strOpenFile).c_str() }, 0, MB_OK | MB_ICONINFORMATION);
}

// 修改列表
void CSettingDlg::ChangeList()
{
	if(m_nClickListCol > 0)
	{
		m_editopt = m_nClickListCol == 2 || m_nClickListCol == 3 ? &m_editListEditNum : &m_editListEdit;
		// 如果选择的是子项
		CRect rc;
		// 获取子项的RECT
		m_listRule.GetSubItemRect(m_nClickListLine, m_nClickListCol, LVIR_LABEL, rc);
		// 转换坐标到列表框中的坐标
		m_editopt->SetParent(&m_listRule);
		// 将文本框移动到RECT所示范围
		m_editopt->MoveWindow(rc);
		// 将子项中的值放在Edit控件中
		m_editopt->SetWindowTextW(m_listRule.GetItemText(m_nClickListLine, m_nClickListCol));
		// 显示文本框
		m_editopt->ShowWindow(SW_SHOW);
		// 设置焦点
		m_editopt->SetFocus();
		// 设置光标
		m_editopt->ShowCaret();
		// 光标移到最后
		m_editopt->SetSel(-1);
	}
}

// 当文本框失去焦点或按下回车时
void CSettingDlg::OnApplyList()
{
	if (!m_editopt)
		return;
	CString tmp;
	m_editopt->GetWindowTextW(tmp);
	m_listRule.SetItemText(m_nClickListLine, m_nClickListCol, tmp);
	m_editopt->ShowWindow(SW_HIDE);
}

// 依据列表刷新规则
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

// 刷新列表编号
void CSettingDlg::RefreshLineNum()
{
	CString tmp;
	for (int i = 0; i < m_listRule.GetItemCount(); i++)
	{
		tmp.Format(_T("%d"), i + 1);
		m_listRule.SetItemText(i, 0, tmp);
	}
}

// 将列表框中的当前行向上或向下移动__m个单位长度,__m为正往下移动,为负向上移动
void CSettingDlg::OnMoveLine(int __m)
{
	if (__m != 0 && m_nClickListLine + __m < m_listRule.GetItemCount() && m_nClickListLine + __m >= 0)
	{
		// 交换移动的两列的内容
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

// 以列表框当前行为基准,向上或向下插入行,__m为正向下插入,为负向上插入
void CSettingDlg::OnInsertLine(int __m)
{
	// 向上插入和向下插入都是列表下移的过程
	m_listRule.InsertItem(m_nClickListLine + __m,_T(""));
	RefreshLineNum();
}

// 保存按钮,如果是从别的文件导入的,那么将其保存到这个文件,如果是默认设置就将其保存至rule.json文件
void CSettingDlg::OnBnClickedBtnSave()
{
	SaveToFile();
}

// 从文件导入规则按钮
void CSettingDlg::OnBnClickedBtnImport()
{
	// 弹出一个打开对话框
	CFileDialog openFile(TRUE, 0, NULL, OFN_HIDEREADONLY | OFN_READONLY, _T("配置文件 (*.json)|*.json|所有文件 (*.*)|*.*||"), NULL);
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
	CFileDialog saveFile(FALSE, 0, 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("配置文件 (*.json)|*.json|所有文件 (*.*)|*.*||"), NULL);
	saveFile.DoModal();
	RefreshRules();
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
	if (IDNO == MessageBoxW(_T("载入默认设置后当前的更改将会被丢弃,是否确认"), 0, MB_YESNO | MB_ICONINFORMATION))
		return;
	if(!get_rule_from_json(m_drThisPage, g_strDefaultRule))
	{
		MessageBoxW(_T("载入默认规则失败"), 0, MB_OK | MB_ICONERROR);
		return;
	}
	RefreshList();
	MessageBoxW(_T("载入默认规则成功"), 0, MB_OK | MB_ICONINFORMATION);
}

// 应用按钮
void CSettingDlg::OnBnClickedBtnApply()
{
	RefreshRules();
	g_drAllRules = m_drThisPage;
	MessageBoxW(_T("应用规则成功"), 0, MB_OK | MB_ICONINFORMATION);
}

// 取消按钮
void CSettingDlg::OnBnClickedBtnCancel()
{
	if(m_bIsOper && IDYES == MessageBoxW(_T("是否将更改保存到配置文件"),0,MB_YESNO|MB_ICONINFORMATION))
		SaveToFile();
	this->OnCancel();
}


// 右键列表某一规则的事件响应
void CSettingDlg::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW * pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	m_nClickListLine = pNMListView->iItem;	// 获取选中行信息
	m_nClickListCol = pNMListView->iSubItem;	// 获取选中的列信息
	POSITION pos = m_listRule.GetFirstSelectedItemPosition();
	if (m_listRule.GetNextSelectedItem(pos) == -1)
		return;		//如果没有选中的项目，返回
	//显示弹出菜单
	CPoint point;
	GetCursorPos(&point);
	CMenu menu;
	menu.LoadMenu(IDR_MENU_SETTING);//获取菜单的资源
	CMenu* popup = menu.GetSubMenu(0);//只获取第一个列菜单的指针
	//弹出菜单显示
	popup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);
	*pResult = 0;
}

// 右键菜单中编辑按钮
void CSettingDlg::OnChangeList()
{
	ChangeList();
}

// 右键菜单向上插入
void CSettingDlg::OnInsertUp()
{
	OnInsertLine(0);
}

// 右键菜单向下插入
void CSettingDlg::OnInsertDown()
{
	OnInsertLine(1);
}

// 右键菜单删除此行
void CSettingDlg::OnDeleteLine()
{
	m_listRule.DeleteItem(m_nClickListLine);
	RefreshLineNum();
}

// 双击List的事件响应
void CSettingDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW * pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	m_nClickListLine = pNMListView->iItem;	// 获取选中行信息
	m_nClickListCol = pNMListView->iSubItem;	// 获取选中的列信息
	POSITION pos = m_listRule.GetFirstSelectedItemPosition();
	if (m_listRule.GetNextSelectedItem(pos) == -1)
		return;		//如果没有选中的项目，返回
	ChangeList();
	*pResult = 0;
}

// 列表文本框失去焦点
void CSettingDlg::OnKillfocusEditList()
{
	OnApplyList();
}

// 向上移动按钮
void CSettingDlg::OnMoveUp()
{
	OnMoveLine(-1);
}

// 向下移动按钮
void CSettingDlg::OnMoveDown()
{
	OnMoveLine(1);
}

// 列表文本框失去焦点
void CSettingDlg::OnKillfocusEditListNum()
{
	OnApplyList();
}
