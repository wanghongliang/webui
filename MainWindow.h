#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <atlbase.h>
#include <atlapp.h>
#include <atlwinx.h> 
#include "BrowserView.h"

class CMainWindow : public CWindowImpl<CMainWindow, CWindow, CFrameWinTraits>
{
public:

    DECLARE_WND_CLASS(TEXT("Main Window"));

private:

    BEGIN_MSG_MAP(CMainWindow)

        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy) 

    END_MSG_MAP()

    LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&);

    LRESULT OnFileNew(WORD, WORD, HWND, BOOL&);
    LRESULT OnFileOpen(WORD, WORD, HWND, BOOL&);

    CIcon m_icon;
    CMenu m_menu; 
};

#endif // CMAINWINDOW_H