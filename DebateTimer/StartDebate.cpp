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
	// ��ʼ��ʱ��, ֵΪ-1������ʱ��δ����
	for (int i = 0; i < 4; i++)
		m_alTimer[i] = -1;
	// ��ʼ����ʱ��
	SetTimer(1, 1000, NULL);
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
	// TODO: Add your control notification handler code here
}

// ��ͣ��ʱ��ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
}

// ���ñ��ڰ�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnResetThis()
{
	// TODO: Add your control notification handler code here
}

// ���ñ�����ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnResetAll()
{
	// TODO: Add your control notification handler code here
}

// ��һ���ڰ�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnLeft()
{
	// TODO: Add your control notification handler code here
}

// ��һ���ڰ�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnRight()
{
	// TODO: Add your control notification handler code here
}

// �����б�ť�¼���Ӧ
void CStartDebate::OnBnClickedBtnShowlist()
{
	// TODO: Add your control notification handler code here
}

// ��ʱ���ص�����
void CStartDebate::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		// �����ĸ�ʱ�������
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
	m_stcShowTime.MoveWindow(CRect{ 0,int(0.08*cy) ,cx,int(0.75*cy) });
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
	if (nCtlColor == CTLCOLOR_STATIC && (pWnd->GetDlgCtrlID() == IDC_STC_TITLE || pWnd->GetDlgCtrlID() == IDC_STC_SHOWTIME))
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 0, 255));
		return m_brushBlue;
	}
	return hbr;
}
