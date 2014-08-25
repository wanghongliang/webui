#include "StdAfx.h"
#include "MainWindow.h"
 

LRESULT CMainWindow::OnCreate(
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam,
    BOOL& bHandled)
{
    //LONG_PTR icon = reinterpret_cast<LONG_PTR>(
    //    m_icon.LoadIcon(MAKEINTRESOURCE(IDI_MAIN)));

    //SetClassLongPtr(m_hWnd, GCLP_HICON, icon);
    //SetClassLongPtr(m_hWnd, GCLP_HICONSM, icon);

	RECT rc;
    GetClientRect(&rc);

    DWORD style = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
    //m_editor.Create(m_hWnd, rc, nullptr, style);


 	CBrowserView* pView = new CBrowserView;	
	pView->Create( m_hWnd, rc , _T("http://www.baidu.com"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL);
	 
 

    bHandled = TRUE;
    return 0;
}

LRESULT CMainWindow::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
    ::PostQuitMessage(0);
    bHandled = TRUE;
    return 0;
}


LRESULT CMainWindow::OnFileNew(WORD, WORD, HWND, BOOL& bHandled)
{
    bHandled = TRUE;
    return 0;
}

LRESULT CMainWindow::OnFileOpen(WORD, WORD, HWND, BOOL& bHandled)
{
    bHandled = TRUE;
    return 0;
}