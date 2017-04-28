// StartDebate.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "StartDebate.h"
#include "afxdialogex.h"
#include "Core.h"


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

// ���þ�̬�ı���������С,����Ϊ6��Լ���������һ��static��
void CStartDebate::SetStaticCtlFontSize(CStatic & __s, double __nps)
{
	CRect stcRect;
	__s.GetClientRect(stcRect);
	m_font.CreatePointFont(__nps*stcRect.Height(), _T("Microsoft Sans Serif"));
	__s.SetFont(&m_font);
}

// ��ӡ��Ŀ����
void CStartDebate::PrintTitle()
{
	m_stcTitle.SetWindowTextW(CString{ g_drAllRules[m_nItemNum].m_strChapter.c_str() });
}

// ��ӡ����������
void CStartDebate::PrintTimerName()
{
	const SRule & rule{ g_drAllRules[m_nItemNum] };
	CString output;
	CString tmp;
	for (int i = 0; i < rule.m_nTimerNum; i++)
	{
		tmp.Format(_T("%s:\r\n"), CString{rule.m_vecTimerName[i].c_str()}.GetString());
		output += tmp;
	}
	m_stcTimerName.SetWindowTextW(output);
	SetStaticCtlFontSize(m_stcTimerName, 1.5);
}

// ����ʱ��
void CStartDebate::ResetTimer()
{
	m_aTimer[0] = g_drAllRules[m_nItemNum].m_nTime;
	m_aTimer[1] = g_drAllRules[m_nItemNum].m_nTimerNum == 2 ? 
		g_drAllRules[m_nItemNum].m_nTime : -1;
}

// �ھ�̬���д�ӡʱ����Ϣ
void CStartDebate::PrintTimer()
{
	const SRule & rule{ g_drAllRules[m_nItemNum] };
	const unsigned nLineNum{ rule.m_nTimerNum / 2 + 1 };	// ��Ҫ��ӡ������
	CString output;
	CString tmp;
	for (int i = 0; i < rule.m_nTimerNum; i++)
	{
		tmp.Format(_T("%2d:%2d\r\n"), m_aTimer[i] / 60, m_aTimer[i] - 60 * int(m_aTimer[i] / 60));
		output += tmp;
	}
	m_stcShowTime.SetWindowTextW(output);
	SetStaticCtlFontSize(m_stcShowTime, 5.5 / nLineNum);
}

// ���ñ���
void CStartDebate::ResetItem()
{
	KillTimer(1);
	m_bActiveFirst = true;
	m_bStartFirst = true;
	m_bIsStop = false;
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
	ResetTimer();
	PrintTitle();
	PrintTimerName();
	PrintTimer();
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
	// �����ʼ��ʱ��������һ���Ϸ��Ĺ���,����򲻺Ϸ�,��ҳ�˳�
	if(g_drAllRules.empty())
	{
		MessageBoxW(_T("�����趨ʧ��,�����µ������"), 0, MB_OK | MB_ICONERROR);
		this->OnCancel();
	}
	// ��ʼ����ɫ��ˢ
	m_brushBlue.CreateSolidBrush(RGB(0, 0, 255));
	// ���ô���ȫ����ʾ
	CRect winRect, enableClient;
	GetWindowRect(&winRect); //����������Ļ�Ĵ���ľ������� 
	RepositionBars(0, AFX_IDW_PANE_FIRST, AFX_IDW_PANE_LAST, reposQuery, &enableClient);  //reposQuery���������Ӧ�����CRect�����ȡ�ͻ�����
	RECT newPos;   //��λ��
	ClientToScreen(&enableClient); //ת����Ļ����
	newPos.left = winRect.left - enableClient.left;//��������߽�-�ڲ��ͻ�����  �պðѱ߽�ȥ�� 
	newPos.right = winRect.right - enableClient.right + GetSystemMetrics(SM_CXSCREEN);
	newPos.top = winRect.top - enableClient.top; //����Ҳ���ÿͻ�����-����  ������պ��Ǳ�ݵĳ��� 
	newPos.bottom = winRect.bottom - enableClient.bottom + GetSystemMetrics(SM_CYSCREEN); //�±߿�ĸ߶�+��Ļ����
	WINDOWPLACEMENT  wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = 0;   //���� 0 
	wp.rcNormalPosition = newPos; //��λ��
	wp.showCmd = SW_SHOWNORMAL;//������ʾ
	::SetWindowPlacement(this->m_hWnd, &wp); //���ô���λ��
	// �����ı��������С
	SetStaticCtlFontSize(m_stcTitle, 6);
	// ��ʼ����Ŀ
	m_nItemNum = 0;
	ResetItem();
	// ��ʼ���б��
	m_listRule.SetExtendedStyle(m_listRule.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRule.InsertColumn(0, _T("���"), LVCFMT_CENTER, 60, 50);
	m_listRule.InsertColumn(1, _T("��Ŀ����"), LVCFMT_CENTER, 150, 50);
	m_listRule.InsertColumn(2, _T("ʱ��ʱ��"), LVCFMT_CENTER, 150, 50);
	m_listRule.InsertColumn(3, _T("ʱ��1˵��"), LVCFMT_CENTER, 120, 50);
	m_listRule.InsertColumn(4, _T("ʱ��2˵��"), LVCFMT_CENTER, 120, 50);
	// �˴����б�Ϊֻ��,�����޸���������,���ڴ˴�һ���ʼ��
	CString tmp;
	for (int i = 0; i < g_drAllRules.size(); i++)
	{
		// ���
		tmp.Format(_T("%d"), i + 1);
		m_listRule.InsertItem(i, tmp);
		// ��Ŀ����
		tmp = g_drAllRules[i].m_strChapter.c_str();
		m_listRule.SetItemText(i, 1, tmp);
		// ʱ��ʱ��
		tmp.Format(_T("%d��%d��"), g_drAllRules[i].m_nTime / 60,
			g_drAllRules[i].m_nTime - int(g_drAllRules[i].m_nTime / 60) * 60);
		m_listRule.SetItemText(i, 2, tmp);
		// ʱ��˵��
		for (int j = 0; j < g_drAllRules[i].m_nTimerNum && j < g_drAllRules[i].m_vecTimerName.size(); j++)
		{
			tmp = g_drAllRules[i].m_vecTimerName[j].c_str();
			m_listRule.SetItemText(i, 3 + j, tmp);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// �˳���ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnExit()
{
	this->OnCancel();
}

// ��ʼ��ʱ��ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnStart()
{
	SetTimer(1, 1000, NULL);
	BOOL bEnable = FALSE;
	if (g_drAllRules[m_nItemNum].m_nTimerNum > 1)
	{
		// ���������ʱ�ӵĻ�
		m_btnStart.SetWindowTextW(_T("�л�ʱ��"));
		if(!m_bIsStop && !m_bStartFirst)
			m_bActiveFirst = !m_bActiveFirst;
		bEnable = TRUE;
	}
	m_bIsStop = false;
	m_bStartFirst = false;
	m_btnStart.EnableWindow(bEnable);
	m_btnStop.EnableWindow(TRUE);
	m_listRule.ShowWindow(SW_HIDE);
	m_btnShowList.SetWindowTextW(_T("��ʾ�б�"));
}

// ��ͣ��ʱ��ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnStop()
{
	KillTimer(1);
	if(g_drAllRules[m_nItemNum].m_nTimerNum > 1)
		m_btnStart.SetWindowTextW(_T("��ʼ��ʱ"));
	m_bIsStop = true;
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
}

// ���ñ��ڰ�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnResetThis()
{
	if (IDYES == MessageBoxW(_T("ȷ��Ҫ���ñ���?"), 0, MB_YESNO | MB_ICONINFORMATION))
	{
		KillTimer(1);
		ResetItem();
	}
}

// ���ñ�����ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnResetAll()
{
	if (IDYES == MessageBoxW(_T("ȷ��Ҫ���ñ���?"), 0, MB_YESNO | MB_ICONINFORMATION))
	{
		m_nItemNum = 0;
		KillTimer(1);
		ResetItem();
	}
}

// ��һ���ڰ�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnLeft()
{
	if (m_nItemNum - 1 >= 0)
	{
		m_nItemNum--;
		ResetItem();
	}
	else
	{
		MessageBoxW(_T("��ͷ��!"), 0, MB_OK | MB_ICONSTOP);
	}
}

// ��һ���ڰ�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnRight()
{
	if (m_nItemNum + 1 < g_drAllRules.size())
	{
		m_nItemNum++;
		ResetItem();
	}
	else
	{
		MessageBoxW(_T("��ͷ��!"), 0, MB_OK | MB_ICONSTOP);
	}
}

// �����б�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnShowlist()
{
	OnBnClickedBtnStop();		// ��ʾ�б��ʱ����ͣ��ʱ
	m_listRule.ShowWindow(m_listRule.IsWindowVisible() ? SW_HIDE : SW_SHOW);
	m_btnShowList.SetWindowTextW(m_listRule.IsWindowVisible() ? _T("�����б�") : _T("��ʾ�б�"));
}

// ��ʱ���ص�����
void CStartDebate::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		int * ptrChange{ m_bActiveFirst ? &m_aTimer[0] : &m_aTimer[1] };
		if (*ptrChange > 0)
			*ptrChange -= 1;
		else
			KillTimer(1);
		PrintTimer();
	}
	CDialogEx::OnTimer(nIDEvent);
}

// �����С�����ı�
void CStartDebate::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// �ƶ���ť��ָ��λ��
	CRect rectBtn;
	m_btnStart.GetWindowRect(rectBtn);
	const int btnWidth{ rectBtn.Width() };
	const int btnHeight{ rectBtn.Height() };
	// ���Ͻǰ�ť�����Ͻ�����
	const int x0{ int((cx - btnWidth*5.2) / 2) };						// ������ʾ,�м���0.4����ť����
	const int y0{ int(cy - int(0.06*double(cy)) - 2.3*btnHeight) };	// �ײ�����5%�Ŀռ���
	m_btnStart.MoveWindow(CRect{ x0,y0,x0 + btnWidth,y0 + btnHeight });
	m_btnStop.MoveWindow(CRect{ x0 + int(1.4*btnWidth),y0,int(x0 + 2.4*btnWidth),y0 + btnHeight });
	m_btnResetThis.MoveWindow(CRect{ x0 + int(2.8*btnWidth),y0,int(x0 + 3.8*btnWidth),y0 + btnHeight });
	m_btnResetAll.MoveWindow(CRect{ x0 + int(4.2*btnWidth),y0,int(x0 + 5.2*btnWidth),y0 + btnHeight });
	m_btnLeft.MoveWindow(CRect{ x0,y0 + int(1.4*btnHeight),x0 + btnWidth ,y0 + int(2.4*btnHeight) });
	m_btnRight.MoveWindow(CRect{ x0 + int(1.4*btnWidth),y0 + int(1.4*btnHeight),int(x0 + 2.4*btnWidth) ,y0 + int(2.4*btnHeight) });
	m_btnShowList.MoveWindow(CRect{ x0 + int(2.8*btnWidth),y0 + int(1.4*btnHeight),int(x0 + 3.8*btnWidth) ,y0 + int(2.4*btnHeight) });
	m_btnExit.MoveWindow(CRect{ x0 + int(4.2*btnWidth),y0 + int(1.4*btnHeight),int(x0 + 5.2*btnWidth) ,y0 + int(2.4*btnHeight) });
	// �ƶ��ı���ָ��λ��
	m_stcTitle.MoveWindow(CRect{ 0,0,cx,int(0.08*cy) });
	m_stcShowTime.MoveWindow(CRect{ int(0.15*cx),int(0.08*cy) ,cx,int(0.75*cy) });
	m_stcTimerName.MoveWindow(CRect{ 0,int(0.35*cy) ,int(0.15*cx) ,int(0.75*cy) });
	// �ƶ��б�ָ��λ��
	m_listRule.MoveWindow(CRect{ int(0.3*cx),int(0.08*cy) ,int(0.65*cx),int(0.75*cy) });
}


void CStartDebate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// ���ô��屳��ɫ
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0, 0, 255));
}


HBRUSH CStartDebate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// �����ı��򱳾���������ɫ
	if (nCtlColor == CTLCOLOR_STATIC && 
		(pWnd->GetDlgCtrlID() == IDC_STC_TITLE || 
			pWnd->GetDlgCtrlID() == IDC_STC_SHOWTIME ||
			pWnd->GetDlgCtrlID() == IDC_STC_TIMERNAME))
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 0, 255));
		return m_brushBlue;
	}
	return hbr;
}
