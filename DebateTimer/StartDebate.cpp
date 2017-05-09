// StartDebate.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "StartDebate.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "Core.h"
#include "Vfw.h"


// CStartDebate dialog

IMPLEMENT_DYNAMIC(CStartDebate, CDialogEx)

CStartDebate::CStartDebate(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CStartDebate::~CStartDebate()
{
}

void CStartDebate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_RESET_THIS, m_btnResetThis);
	DDX_Control(pDX, IDC_BTN_RESET_ALL, m_btnResetAll);
	DDX_Control(pDX, IDC_BTN_LEFT, m_btnLeft);
	DDX_Control(pDX, IDC_BTN_RIGHT, m_btnRight);
	DDX_Control(pDX, IDC_BTN_SHOWLIST, m_btnShowList);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_STC_TITLE, m_stcTitle);
	DDX_Control(pDX, IDC_STC_SHOWTIME, m_stcShowTime);
	DDX_Control(pDX, IDC_STC_TIMERNAME, m_stcTimerName);
	DDX_Control(pDX, IDC_LIST_SHOWRULELIST, m_listRule);
	DDX_Control(pDX, IDC_STC_SHOWTIME2, m_stcShowTime2);
}


BEGIN_MESSAGE_MAP(CStartDebate, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CStartDebate::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_START, &CStartDebate::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CStartDebate::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_RESET_THIS, &CStartDebate::OnBnClickedBtnResetThis)
	ON_BN_CLICKED(IDC_BTN_RESET_ALL, &CStartDebate::OnBnClickedBtnResetAll)
	ON_BN_CLICKED(IDC_BTN_LEFT, &CStartDebate::OnBnClickedBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, &CStartDebate::OnBnClickedBtnRight)
	ON_BN_CLICKED(IDC_BTN_SHOWLIST, &CStartDebate::OnBnClickedBtnShowlist)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SHOWRULELIST, &CStartDebate::OnDblclkListShowrulelist)
END_MESSAGE_MAP()


// CStartDebate message handlers

// 设置控件的字体及大小
void CStartDebate::SetControlFont(CWnd& __wnd, double __nps, const char* __font)
{
	CRect rect;
	__wnd.GetClientRect(rect);
	m_font.CreatePointFont(__nps*min(rect.Height(), rect.Width()), CString{ __font });
	__wnd.SetFont(&m_font);
}

// 设置时钟静态框显示模式
void CStartDebate::SetTimerShowMode()
{
	// 显示屏大小
	int cx{ GetSystemMetrics(SM_CXSCREEN) };
	int cy{ GetSystemMetrics(SM_CYSCREEN) };
	auto tn{ g_drAllRules[m_nItemNum].m_nTimerNum };
	double ky{ 0.75 - 0.335*(tn - 1) };
	m_stcShowTime.MoveWindow(CRect{ int(0.15*cx),int(0.08*cy) ,cx,int(ky*cy) });
	m_stcShowTime2.MoveWindow(CRect{ int(0.15*cx),int(ky*cy) + 20 ,cx,int(0.75*cy) });
	m_stcShowTime2.ShowWindow(tn == 1 ? SW_HIDE : SW_SHOW);
}

// 打印项目标题
void CStartDebate::PrintTitle()
{
	m_stcTitle.SetWindowTextW(CString{ g_drAllRules[m_nItemNum].m_strChapter.c_str() });
}

// 打印计数器名称
void CStartDebate::PrintTimerName()
{
	const SRule & rule{ g_drAllRules[m_nItemNum] };
	CString output{ rule.m_vecTimerName[0].c_str() };
	if (rule.m_nTimerNum > 1)
		output += ("\r\n" + rule.m_vecTimerName[1]).c_str();
	m_stcTimerName.SetWindowTextW(output);
	SetControlFont(m_stcTimerName, 1.5);
}

// 重置时钟
void CStartDebate::ResetTimer()
{
	m_aTimer[0] = g_drAllRules[m_nItemNum].m_nTime;
	m_aTimer[1] = g_drAllRules[m_nItemNum].m_nTimerNum == 2 ? m_aTimer[0] : -1;
}

// 依据编号打印时钟信息
void CStartDebate::PrintTimer(unsigned __n)
{
	CString output;
	output.Format(_T("%2d:%02d\r\n"), m_aTimer[__n] / 60, m_aTimer[__n] - 60 * int(m_aTimer[__n] / 60));
	auto pOperStatic{ __n ? &m_stcShowTime2 : &m_stcShowTime };
	if (m_aTimer[__n] <= 30)
		pOperStatic->SetTextColor(RGB(255, 0, 0));
	pOperStatic->SetWindowText(output);
}

// 在静态框中打印时钟信息
void CStartDebate::PrintTimer()
{
	PrintTimer(0);
	if (g_drAllRules[m_nItemNum].m_nTimerNum > 1)
		PrintTimer(1);
}

// 重置本节
void CStartDebate::ResetItem()
{
	KillTimer(1);
	m_bActiveFirst = true;
	m_bStartFirst = true;
	m_bIsStop = false;
	m_btnStart.SetWindowTextW(_T("开始计时"));
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
	m_listRule.ShowWindow(SW_HIDE);
	m_btnShowList.SetWindowTextW(_T("显示列表"));
	m_stcShowTime.SetTextColor(RGB(255, 255, 255));
	m_stcShowTime2.SetTextColor(RGB(255, 255, 255));
	SetTimerShowMode();
	ResetTimer();
	PrintTitle();
	PrintTimerName();
	PrintTimer();
	// 刷新计时器框的字体
	CRect rect;
	m_stcShowTime.GetClientRect(rect);
	m_font.CreatePointFont(6 * rect.Height(), _T("Microsoft Sans Serif"));
	m_stcShowTime.SetFont(&m_font);
	m_stcShowTime2.SetFont(&m_font);
}

// 播放文件中音频
void CStartDebate::PlaySoundFromFile(const char* __file)
{
	MCIWndPlay(MCIWndCreate(GetSafeHwnd(), AfxGetInstanceHandle(),
		WS_CHILD | MCIWNDF_NOMENU | MCIWNDF_NOTIFYMODE, CString{ __file }));
}

BOOL CStartDebate::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CStartDebate::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 窗体初始化时必需载入一个合法的规则,如规则不合法,本页退出
	if(g_drAllRules.empty())
	{
		MessageBoxW(_T("规则设定失败,请重新导入规则"), 0, MB_OK | MB_ICONERROR);
		this->OnCancel();
	}
	// 初始化蓝色画刷
	m_brushBlue.CreateSolidBrush(RGB(0, 0, 255));
	// 设置窗体全屏显示
	CRect winRect, enableClient;
	GetWindowRect(&winRect); //获得相对于屏幕的窗体的矩形区域 
	RepositionBars(0, AFX_IDW_PANE_FIRST, AFX_IDW_PANE_LAST, reposQuery, &enableClient);  //reposQuery这个参数对应后面的CRect对象获取客户区域
	RECT newPos;   //新位置
	ClientToScreen(&enableClient); //转换屏幕坐标
	newPos.left = winRect.left - enableClient.left;//窗体包括边界-内部客户区域  刚好把边界去掉 
	newPos.right = winRect.right - enableClient.right + GetSystemMetrics(SM_CXSCREEN);
	newPos.top = winRect.top - enableClient.top; //顶部也是用客户区域-窗体  负坐标刚好是便捷的长度 
	newPos.bottom = winRect.bottom - enableClient.bottom + GetSystemMetrics(SM_CYSCREEN); //下边框的高度+屏幕坐标
	WINDOWPLACEMENT  wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = 0;   //参数 0 
	wp.rcNormalPosition = newPos; //新位置
	wp.showCmd = SW_SHOWNORMAL;//正常显示
	::SetWindowPlacement(this->m_hWnd, &wp); //设置窗体位置
	// 设置文本框字体大小
	SetControlFont(m_stcTitle, 6);
	// 初始化项目
	m_nItemNum = 0;
	ResetItem();
	// 初始化列表框
	m_listRule.SetExtendedStyle(m_listRule.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRule.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 60, 50);
	m_listRule.InsertColumn(1, _T("项目名称"), LVCFMT_CENTER, 250, 50);
	m_listRule.InsertColumn(2, _T("时钟时间"), LVCFMT_CENTER, 100, 50);
	m_listRule.InsertColumn(3, _T("时钟1说明"), LVCFMT_CENTER, 100, 50);
	m_listRule.InsertColumn(4, _T("时钟2说明"), LVCFMT_CENTER, 100, 50);
	// 此处的列表为只读,不可修改其中内容,故在此处一遍初始化
	CString tmp;
	for (int i = 0; i < g_drAllRules.size(); i++)
	{
		// 编号
		tmp.Format(_T("%d"), i + 1);
		m_listRule.InsertItem(i, tmp);
		// 项目名称
		tmp = g_drAllRules[i].m_strChapter.c_str();
		m_listRule.SetItemText(i, 1, tmp);
		// 时钟时间
		tmp.Format(_T("%d分%02d秒"), g_drAllRules[i].m_nTime / 60,
			g_drAllRules[i].m_nTime - int(g_drAllRules[i].m_nTime / 60) * 60);
		m_listRule.SetItemText(i, 2, tmp);
		// 时钟说明
		for (int j = 0; j < g_drAllRules[i].m_nTimerNum && j < g_drAllRules[i].m_vecTimerName.size(); j++)
		{
			tmp = g_drAllRules[i].m_vecTimerName[j].c_str();
			m_listRule.SetItemText(i, 3 + j, tmp);
		}
	}
	// 初始化控件
	m_stcShowTime.SetBkgndColor(RGB(0, 0, 255));
	m_stcShowTime2.SetBkgndColor(RGB(0, 0, 255));
	m_stcShowTime.SetTextFormat(DT_CENTER | DT_VCENTER);
	m_stcShowTime2.SetTextFormat(DT_CENTER | DT_VCENTER);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// 退出按钮事件响应
void CStartDebate::OnBnClickedBtnExit()
{
	this->OnCancel();
}

// 开始计时按钮事件响应
void CStartDebate::OnBnClickedBtnStart()
{
	SetTimer(1, 1000, NULL);
	BOOL bEnable = FALSE;
	if (g_drAllRules[m_nItemNum].m_nTimerNum > 1)
	{
		// 如果有两个时钟的话
		m_btnStart.SetWindowTextW(_T("切换时钟"));
		if(!m_bIsStop && !m_bStartFirst)
			m_bActiveFirst = !m_bActiveFirst;
		bEnable = TRUE;
	}
	m_bIsStop = false;
	m_bStartFirst = false;
	m_btnStart.EnableWindow(bEnable);
	m_btnStop.EnableWindow(TRUE);
	m_listRule.ShowWindow(SW_HIDE);
	m_btnShowList.SetWindowTextW(_T("显示列表"));
}

// 暂停计时按钮事件响应
void CStartDebate::OnBnClickedBtnStop()
{
	KillTimer(1);
	if(g_drAllRules[m_nItemNum].m_nTimerNum > 1)
		m_btnStart.SetWindowTextW(_T("开始计时"));
	m_bIsStop = true;
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
}

// 重置本节按钮事件响应
void CStartDebate::OnBnClickedBtnResetThis()
{
	if (IDYES == MessageBoxW(_T("确定要重置本节?"), 0, MB_YESNO | MB_ICONINFORMATION))
	{
		KillTimer(1);
		ResetItem();
	}
}

// 重置比赛按钮事件响应
void CStartDebate::OnBnClickedBtnResetAll()
{
	if (IDYES == MessageBoxW(_T("确定要重置比赛?"), 0, MB_YESNO | MB_ICONINFORMATION))
	{
		m_nItemNum = 0;
		KillTimer(1);
		ResetItem();
	}
}

// 上一环节按钮事件响应
void CStartDebate::OnBnClickedBtnLeft()
{
	if (m_nItemNum - 1 >= 0)
	{
		m_nItemNum--;
		ResetItem();
	}
	else
	{
		MessageBoxW(_T("到头了!"), 0, MB_OK | MB_ICONSTOP);
	}
}

// 下一环节按钮事件响应
void CStartDebate::OnBnClickedBtnRight()
{
	if (m_nItemNum + 1 < g_drAllRules.size())
	{
		m_nItemNum++;
		ResetItem();
	}
	else
	{
		MessageBoxW(_T("到头了!"), 0, MB_OK | MB_ICONSTOP);
	}
}

// 环节列表按钮事件响应
void CStartDebate::OnBnClickedBtnShowlist()
{
	OnBnClickedBtnStop();		// 显示列表的时候暂停计时
	m_listRule.ShowWindow(m_listRule.IsWindowVisible() ? SW_HIDE : SW_SHOW);
	m_listRule.SetFocus();
	m_btnShowList.SetWindowTextW(m_listRule.IsWindowVisible() ? _T("隐藏列表") : _T("显示列表"));
}

// 计时器回调函数
void CStartDebate::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		int * ptrChange{ m_bActiveFirst ? &m_aTimer[0] : &m_aTimer[1] };
		*ptrChange > 0 ? *ptrChange -= 1 : KillTimer(1);
		if (*ptrChange == 30)
			PlaySoundFromFile("l30s.mp3");
		else if (*ptrChange == 0)
			PlaySoundFromFile("l1s.mp3");
		PrintTimer();
	}
	CDialogEx::OnTimer(nIDEvent);
}

// 窗体大小发生改变
void CStartDebate::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// 移动按钮到指定位置
	CRect rectBtn;
	m_btnStart.GetWindowRect(rectBtn);
	const int btnWidth{ int(0.1*cx) };
	const int btnHeight{ rectBtn.Height() };
	// 左上角按钮的左上角坐标
	const int x0{ int((cx - btnWidth*8) / 2) };	// 居中显示,中间间隔0.4倍按钮长度
	const int y0{ int(0.95*cy - btnHeight) };		// 底部留出5%的空间来
	m_btnStart.MoveWindow(CRect{ x0,y0,x0 + btnWidth,y0 + btnHeight });
	m_btnStop.MoveWindow(CRect{ x0 + int(1.4*btnWidth),y0,int(x0 + 2.4*btnWidth),y0 + btnHeight });
	m_btnResetThis.MoveWindow(CRect{ x0 + int(2.8*btnWidth),y0,int(x0 + 3.8*btnWidth),y0 + btnHeight });
	m_btnRight.MoveWindow(CRect{ x0 + int(4.2*btnWidth),y0,int(x0 + 5.2*btnWidth) ,y0 + btnHeight });
	m_btnShowList.MoveWindow(CRect{ x0 + int(5.6*btnWidth),y0,int(x0 + 6.6*btnWidth) ,y0 + btnHeight });
	m_btnExit.MoveWindow(CRect{ x0 + int(7*btnWidth),y0,int(x0 + 8*btnWidth) ,y0 + btnHeight });
	// 移动文本框到指定位置
	m_stcTitle.MoveWindow(CRect{ 0,0,cx,int(0.08*cy) });
	m_stcTimerName.MoveWindow(CRect{ 0,int(0.35*cy) ,int(0.15*cx) ,int(0.75*cy) });
	// 移动列表到指定位置
	m_listRule.MoveWindow(CRect{ int(0.3*cx),int(0.08*cy) ,int(0.65*cx),int(0.75*cy) });
}


void CStartDebate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 设置窗体背景色
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0, 0, 255));
}


HBRUSH CStartDebate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// 设置文本框背景及文字颜色
	pDC->SetBkColor(RGB(0, 0, 255));
	if (pWnd->GetDlgCtrlID() == IDC_STC_TITLE || 
		pWnd->GetDlgCtrlID() == IDC_STC_TIMERNAME)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		return m_brushBlue;
	}
	return hbr;
}

// 双击列表框事件响应
void CStartDebate::OnDblclkListShowrulelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW * pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	int nLine{ pNMListView->iItem };	// 获取选中行信息
	POSITION pos = m_listRule.GetFirstSelectedItemPosition();
	if (m_listRule.GetNextSelectedItem(pos) == -1)
		return;		//如果没有选中的项目，返回
	// 获取此行的项目id,然后载入
	m_nItemNum = _ttoi(CString{ m_listRule.GetItemText(nLine,0) }) - 1;
	ResetItem();
	*pResult = 0;
}
