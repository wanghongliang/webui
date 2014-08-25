#pragma once

class CBrowserContainer : public CWindowImpl<CBrowserContainer>
{
public:
    CBrowserContainer();

    void SetBrowserHandle(HWND hWnd);

    BEGIN_MSG_MAP(CBrowserContainer)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    END_MSG_MAP()

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
private:
    HWND m_hWndBrowser;
};