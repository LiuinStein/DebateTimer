#include "stdafx.h"
#include "DoubleBuffStatic.h"


CDoubleBuffStatic::CDoubleBuffStatic() :
	m_cstrShowText(_T("")), m_colorText(RGB(255,255,255)),
	m_colorBkgnd(RGB(0,0,0)), m_fontText(nullptr),
	m_fmtText(DT_LEFT)
{
}

CDoubleBuffStatic::CDoubleBuffStatic(CDoubleBuffStatic& __c) :
	m_cstrShowText(__c.m_cstrShowText), m_colorText(__c.m_colorText),
	m_colorBkgnd(__c.m_colorBkgnd), m_fontText(__c.m_fontText),
	m_fmtText(__c.m_fmtText)
{
}


CDoubleBuffStatic::~CDoubleBuffStatic()
{
}

void CDoubleBuffStatic::SetWindowText(LPCTSTR __str)
{
	m_cstrShowText = __str;
	Invalidate();
}

void CDoubleBuffStatic::GetWindowText(CString& __str) const
{
	__str = m_cstrShowText;
}

void CDoubleBuffStatic::SetTextFormat(UINT __agn)
{
	m_fmtText = __agn;
	Invalidate();
}

void CDoubleBuffStatic::SetTextColor(COLORREF __color)
{
	m_colorText = __color;
	Invalidate();
}

void CDoubleBuffStatic::SetBkgndColor(COLORREF __color)
{
	m_colorBkgnd = __color;
	Invalidate();
}

void CDoubleBuffStatic::SetFont(CFont* __font)
{
	m_fontText = __font;
	Invalidate();
}

CFont* CDoubleBuffStatic::GetFont() const
{
	return m_fontText;
}

BEGIN_MESSAGE_MAP(CDoubleBuffStatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL CDoubleBuffStatic::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CDoubleBuffStatic::OnPaint()
{
	// Ë«»º³å»æÍ¼
	CPaintDC dc(this); 
	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	if (!memDC.m_hDC)
	{
		CBitmap memMap;
		memDC.CreateCompatibleDC(&dc);
		memMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&memMap);
		memMap.DeleteObject();
		memDC.SetBkMode(TRANSPARENT);
	}
	PaintOnMemDC(rect, &memDC);
	dc.SetBkMode(TRANSPARENT);
	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.DeleteDC();
}

void CDoubleBuffStatic::PaintOnMemDC(CRect __rect, CDC* __mdc)
{
	__mdc->FillSolidRect(__rect, m_colorBkgnd);
	__mdc->SetTextColor(m_colorText);
	if(m_fontText)
		__mdc->SelectObject(m_fontText);
	__mdc->DrawText(m_cstrShowText, __rect, m_fmtText);
}
