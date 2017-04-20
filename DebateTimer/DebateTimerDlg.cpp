
// DebateTimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DebateTimer.h"
#include "DebateTimerDlg.h"
#include "afxdialogex.h"
#include "AboutDlg.h"
#include "SettingDlg.h"
#include "StartDebate.h"
#include "Core.h"
#include "ParseJson.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDebateTimerDlg dialog



CDebateTimerDlg::CDebateTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DEBATETIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDebateTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDebateTimerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CDebateTimerDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_SETRULE, &CDebateTimerDlg::OnBnClickedBtnSetrule)
	ON_BN_CLICKED(IDC_BUTTON2, &CDebateTimerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDebateTimerDlg message handlers

BOOL CDebateTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// ��Ĭ���ļ��ж������
	if(!get_rule_from_file(g_drAllRules))
	{
		// �ļ�������,д���ļ�
		write_to_file(g_strDefaultRule, g_strRuleFile);
		// ��ȡĬ������
		get_rule_from_json(g_drAllRules, g_strDefaultRule);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDebateTimerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDebateTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ڰ�ť
void CDebateTimerDlg::OnBnClickedBtnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

// ���ù���ť
void CDebateTimerDlg::OnBnClickedBtnSetrule()
{
	CSettingDlg dlg;
	dlg.DoModal();
}

// ��ʼ���۰�ť
void CDebateTimerDlg::OnBnClickedButton2()
{
	CStartDebate dlg;
	dlg.DoModal();
}


BOOL CDebateTimerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
