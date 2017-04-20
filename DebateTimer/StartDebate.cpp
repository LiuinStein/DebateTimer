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
}


BEGIN_MESSAGE_MAP(CStartDebate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &CStartDebate::OnBnClickedButton5)
END_MESSAGE_MAP()


// CStartDebate message handlers

// ÍË³ö
void CStartDebate::OnBnClickedButton5()
{
	this->OnCancel();
}


BOOL CStartDebate::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
