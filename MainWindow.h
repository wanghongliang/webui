#pragma once

#include <atlsplit.h>
#include "ScriptEditCtrl.h"
#include "BrowserContainer.h"
#include "ClientHandler.h"
#include <include\cef_app.h>

#define TIMER_LOADING_INDICATOR 1

#define UM_LUAERROR (WM_APP + 1)
#define UM_NOTIFY_OPENER (WM_APP + 2)
#define UM_LOADING_INDICATOR (WM_APP + 3)

class CMainWindow : public CWindowImpl<CMainWindow, CWindow, CFrameWinTraits>
{
public:
    static ATL::CWndClassInfo& GetWndClassInfo();

    static CMainWindow* NewInstance(BOOL createBrowser);

    CBrowserContainer& GetBrowserContainer();
    void SetHandler(CClientHandler *pHandler) {m_handler = pHandler;}

    void AppendLog(LPCTSTR lpText);
    void AppendError(LPCTSTR lpText);
    void DoLuaString(const char *code);
    bool IsDebugPanelVisible();
    void SetDebugPanelVisible(bool bVisible);
    void AnimateLoadingIndicator(bool isLoading);

    virtual void OnFinalMessage(HWND hWnd);

    BEGIN_MSG_MAP(CMainWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(UM_LUAERROR, OnLuaError)
        MESSAGE_HANDLER(UM_NOTIFY_OPENER, OnNotifyOpener)
        MESSAGE_HANDLER(UM_LOADING_INDICATOR, OnLoadingIndicator)
        NOTIFY_CODE_HANDLER(TBVN_PAGEACTIVATED, OnTabPageActived)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnLuaError(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnNotifyOpener(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnLoadingIndicator(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnTabPageActived(int idCtrl, LPNMHDR pnmh, BOOL bHandled);
private:
    CMainWindow();
    ~CMainWindow();

    void MarkTabTitleIfNeeded(CRichEditCtrl &page);

    class CSplitterWnd : public CHorSplitterWindow
    {
        BEGIN_MSG_MAP(CSplitterWnd)
            MESSAGE_HANDLER(WM_TIMER, OnTimer)
            NOTIFY_CODE_HANDLER(TBVN_PAGEACTIVATED, OnTabPageActived)
            CHAIN_MSG_MAP(CHorSplitterWindow)
        END_MSG_MAP()

        LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
        {
            HWND hParent = GetParent();
            ATLASSERT(::IsWindow(hParent));
            ::SendMessage(hParent, UM_LOADING_INDICATOR, 0, 0);
            return 0;
        }

        LRESULT OnTabPageActived(int idCtrl, LPNMHDR pnmh, BOOL bHandled)
        {
            ::SendMessage(GetParent(), WM_NOTIFY, GetDlgCtrlID(), (LPARAM)pnmh);
            return 0;
        }
    };

    CSplitterWnd m_wndSplitter;
    CBrowserContainer m_wndBrowserContainer;
    CTabView m_wndTab;
    CRichEditCtrl m_wndLog;
    CRichEditCtrl m_wndErr;
    CScriptEditCtrl m_wndScript;

    CefRefPtr<CClientHandler> m_handler;

    static UINT s_nInstCount;
};
