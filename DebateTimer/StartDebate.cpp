// StartDebate.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "StartDebate.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CStartDebate message handlers

BOOL CStartDebate::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CStartDebate::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 初始化时钟, 值为-1表名计时器未激活
	for (int i = 0; i < 4; i++)
		m_alTimer[i] = -1;
	// 初始化计时器
	SetTimer(1, 1000, NULL);
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
	// TODO: Add your control notification handler code here
}

// 暂停计时按钮事件响应
void CStartDebate::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
}

// 重置本节按钮事件响应
void CStartDebate::OnBnClickedBtnResetThis()
{
	// TODO: Add your control notification handler code here
}

// 重置比赛按钮事件响应
void CStartDebate::OnBnClickedBtnResetAll()
{
	// TODO: Add your control notification handler code here
}

// 上一环节按钮事件响应
void CStartDebate::OnBnClickedBtnLeft()
{
	// TODO: Add your control notification handler code here
}

// 下一环节按钮事件响应
void CStartDebate::OnBnClickedBtnRight()
{
	// TODO: Add your control notification handler code here
}

// 环节列表按钮事件响应
void CStartDebate::OnBnClickedBtnShowlist()
{
	// TODO: Add your control notification handler code here
}

// 计时器回调函数
void CStartDebate::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		// 遍历四个时间计数器
		for (int i = 0; i < 4; i++)
		{
			if (m_alTimer[i] > 0)
			{
				m_alTimer[i] -= 1;
			}
		}
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
	const int btnWidth{ rectBtn.Width() };
	const int btnHeight{ rectBtn.Height() };
	// 左上角按钮的左上角坐标
	const int x0{ int((cx - btnWidth*5.2) / 2) };						// 居中显示,中间间隔0.4倍按钮长度
	const int y0{ int(cy - int(0.06*double(cy)) - 2.3*btnHeight) };	// 底部留出5%的空间来
	m_btnStart.MoveWindow(CRect{ x0,y0,x0 + btnWidth,y0 + btnHeight });
	m_btnStop.MoveWindow(CRect{ x0 + int(1.4*btnWidth),y0,int(x0 + 2.4*btnWidth),y0 + btnHeight });
	m_btnResetThis.MoveWindow(CRect{ x0 + int(2.8*btnWidth),y0,int(x0 + 3.8*btnWidth),y0 + btnHeight });
	m_btnResetAll.MoveWindow(CRect{ x0 + int(4.2*btnWidth),y0,int(x0 + 5.2*btnWidth),y0 + btnHeight });
	m_btnLeft.MoveWindow(CRect{ x0,y0 + int(1.4*btnHeight),x0 + btnWidth ,y0 + int(2.4*btnHeight) });
	m_btnRight.MoveWindow(CRect{ x0 + int(1.4*btnWidth),y0 + int(1.4*btnHeight),int(x0 + 2.4*btnWidth) ,y0 + int(2.4*btnHeight) });
	m_btnShowList.MoveWindow(CRect{ x0 + int(2.8*btnWidth),y0 + int(1.4*btnHeight),int(x0 + 3.8*btnWidth) ,y0 + int(2.4*btnHeight) });
	m_btnExit.MoveWindow(CRect{ x0 + int(4.2*btnWidth),y0 + int(1.4*btnHeight),int(x0 + 5.2*btnWidth) ,y0 + int(2.4*btnHeight) });
	// 移动文本框到指定位置
	m_stcTitle.MoveWindow(CRect{ 0,0,cx,int(0.08*cy) });
	m_stcShowTime.MoveWindow(CRect{ 0,int(0.08*cy) ,cx,int(0.75*cy) });
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
	if (nCtlColor == CTLCOLOR_STATIC && (pWnd->GetDlgCtrlID() == IDC_STC_TITLE || pWnd->GetDlgCtrlID() == IDC_STC_SHOWTIME))
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 0, 255));
		return m_brushBlue;
	}
	return hbr;
}
