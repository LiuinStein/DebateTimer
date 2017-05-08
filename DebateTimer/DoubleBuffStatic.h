#pragma once
#include "afxwin.h"

/*
 * ˫���徲̬��
 * ʹ��˫�����ͼ���»��ƽ������ˢ��ʱ����˸���⣬�����ı��ĸ���
 */
class CDoubleBuffStatic :
	public CStatic
{
	CString m_cstrShowText;	// ��ʾ�ı�
	COLORREF m_colorText;		// �ı���ɫ
	COLORREF m_colorBkgnd;		// �ؼ�����ɫ
	CFont * m_fontText;		// �ؼ�����

	// ���ڴ�DC�л�ͼ,����������/O2�˳ɻ������������Ż���,MSVC141����������
	void PaintOnMemDC(CRect __rect, CDC* __mdc);
public:
	CDoubleBuffStatic();
	CDoubleBuffStatic(CDoubleBuffStatic & __c);
	~CDoubleBuffStatic();
	// �����µ�API���ǻ�����ԭ�еĺ�������Щ��������˼���
	void SetWindowText(LPCTSTR __str);
	void GetWindowText(CString& __str) const;
	void SetTextColor(COLORREF __color);
	void SetBkgndColor(COLORREF __color);
	void SetFont(CFont * __font);
	CFont* GetFont() const;

	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};

