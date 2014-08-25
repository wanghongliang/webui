#include "StdAfx.h"
#include "BrowserContainer.h"

CBrowserContainer::CBrowserContainer():
m_hWndBrowser(NULL)
{
}

void CBrowserContainer::SetBrowserHandle(HWND hWnd)
{
    m_hWndBrowser = hWnd;
}

LRESULT CBrowserContainer::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    if (m_hWndBrowser) {
        ATLASSERT(::IsWindow(m_hWndBrowser));
        if (::IsWindow(m_hWndBrowser)) {
            ::MoveWindow(m_hWndBrowser, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
        }
    }

    return 0;
}

LRESULT CBrowserContainer::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    return 1;
}