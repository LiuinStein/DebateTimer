#pragma once
#include "afxwin.h"

/*
 * 双缓冲静态框
 * 使用双缓冲绘图更新机制解决快速刷新时的闪烁问题，用于文本的更新
 */
class CDoubleBuffStatic :
	public CStatic
{
	CString m_cstrShowText;	// 显示文本
	COLORREF m_colorText;		// 文本颜色
	COLORREF m_colorBkgnd;		// 控件背景色
	CFont * m_fontText;		// 控件字体

	// 在内存DC中绘图,编译器开了/O2八成会把这个函数给优化掉,MSVC141就是这样的
	void PaintOnMemDC(CRect __rect, CDC* __mdc);
public:
	CDoubleBuffStatic();
	CDoubleBuffStatic(CDoubleBuffStatic & __c);
	~CDoubleBuffStatic();
	// 定义新的API覆盖基类中原有的函数，这些函数顾名思义吧
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

