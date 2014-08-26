#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <atlbase.h>
#include <atlapp.h>
#include <atlwinx.h> 
#include "BrowserView.h"
#include "PaintBkgnd.h"

//定义新的变量 
#define CPaintBkgndBase CPaintBkgnd<CMainWindow, RGB(255,255,255)>  //RGB(218,230,243)  RGB(219,231,243)
class CMainWindow;

class CMainWindow : public CWindowImpl<CMainWindow, CWindow, CFrameWinTraits>,
		public CMessageFilter, public CIdleHandler , public CPaintBkgndBase
{
public:

    DECLARE_WND_CLASS(TEXT("Main Window"));

	bool inited;
	CBrowserView* pView;
	// CMessageFilter
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
 

		return FALSE;
	}

	// CIdleHandler
	virtual BOOL OnIdle()
	{
		
		return FALSE;
	}
private:

    BEGIN_MSG_MAP(CMainWindow)

        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy) 

		CHAIN_MSG_MAP(CPaintBkgndBase)
    END_MSG_MAP()

    LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&);

    LRESULT OnFileNew(WORD, WORD, HWND, BOOL&);
    LRESULT OnFileOpen(WORD, WORD, HWND, BOOL&);

	void OnSize(WPARAM wParam, LPARAM lParam);
	void OnMove(WPARAM wParam, LPARAM lParam);
    CIcon m_icon;
    CMenu m_menu; 
};

#endif // CMAINWINDOW_H