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


	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	RECT rc;
    GetClientRect(&rc);

    DWORD style = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
    //m_editor.Create(m_hWnd, rc, nullptr, style);


	pView = new CBrowserView;	
	pView->Create( m_hWnd, rc , _T("http://www.hao123.com"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL);
	 
 

    bHandled = TRUE;
    return 0;
}

LRESULT CMainWindow::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
    
    //bHandled = TRUE;


	// unregister object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

    ::PostQuitMessage(0);
    return 1;
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

void CMainWindow::OnSize(WPARAM wParam, LPARAM lParam){
	if (pView) { 
		if (::IsWindow(pView->m_hWnd)) {
			//::MoveWindow(pView->m_hWnd, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
			::SetWindowPos( pView->m_hWnd,NULL, 0, 0,  LOWORD(lParam),  HIWORD(lParam), SWP_NOZORDER);
		}
	}


}