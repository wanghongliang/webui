#include "StdAfx.h"
#include "MainWindow.h"
#include "Resource.h"
#include "ClientHandler.h"
#include "Common.h"
#include <include\cef_browser.h>

UINT CMainWindow::s_nInstCount = 0;

ATL::CWndClassInfo& CMainWindow::GetWndClassInfo()
{
    static ATL::CWndClassInfo wc = {
        {sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, StartWindowProc,
            0, 0, NULL, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TASKEXECUTOR)),
            NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, CLSNAME_MAINWINDOW, NULL
        },
        NULL, NULL, IDC_ARROW, TRUE, 0, _T("")
    };
    return wc;
}

CMainWindow* CMainWindow::NewInstance(BOOL createBrowser)
{
    CMainWindow *pMainWindow = new CMainWindow();
    pMainWindow->Create(NULL);

    if (createBrowser) {
        RECT rc;
        CefWindowInfo wndInfo;
        pMainWindow->GetBrowserContainer().GetClientRect(&rc);
        wndInfo.SetAsChild(pMainWindow->GetBrowserContainer().m_hWnd, rc);

        CefBrowserSettings settings;

        CClientHandler *pHandler = new CClientHandler();
        pHandler->SetMainWindow(pMainWindow);
        pMainWindow->m_handler = pHandler;

        std::string startupUrl;
        CefRefPtr<CefCommandLine> cmdline = CefCommandLine::CreateCommandLine();
        cmdline->InitFromString(GetCommandLine());

        if (cmdline->HasSwitch(SWITCH_ARGS)) {
            pHandler->SetLuaArgs(cmdline->GetSwitchValue(SWITCH_ARGS).ToString().c_str());
        }

        if (cmdline->HasSwitch(SWITCH_SCRIPT)) {
            std::string script = cmdline->GetSwitchValue(SWITCH_SCRIPT).ToString();
            pHandler->SetLuaScript(script.c_str());
            pHandler->DoLuaFile(script.c_str());
        }

        if (cmdline->HasSwitch(SWITCH_URL)) {
            startupUrl = cmdline->GetSwitchValue(SWITCH_URL);
        }
        if (startupUrl.empty()) {
            startupUrl = "about:blank";
        }

        CefBrowserHost::CreateBrowserSync(wndInfo, pHandler, startupUrl, settings, NULL);
    }

    return pMainWindow;
}

CBrowserContainer& CMainWindow::GetBrowserContainer()
{
    return m_wndBrowserContainer;
}

void CMainWindow::AppendLog(LPCTSTR lpText)
{
    m_wndLog.SetSel(-1, -1);
    m_wndLog.ReplaceSel(lpText);
    if (lpText[lstrlen(lpText) - 1] != _T('\n')) {
        m_wndLog.SetSel(-1, -1);
        m_wndLog.ReplaceSel(_T("\r\n"));
    }
    m_wndLog.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);

    MarkTabTitleIfNeeded(m_wndLog);
}

void CMainWindow::AppendError(LPCTSTR lpText)
{
    m_wndErr.SetSel(-1, -1);
    m_wndErr.ReplaceSel(lpText);
    if (lpText[lstrlen(lpText) - 1] != _T('\n')) {
        m_wndErr.SetSel(-1, -1);
        m_wndErr.ReplaceSel(_T("\r\n"));
    }
    m_wndErr.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);

    MarkTabTitleIfNeeded(m_wndErr);
}

void CMainWindow::DoLuaString(const char *code)
{
    ATLASSERT(m_handler.get());

    m_handler->DoLuaString(code);
}

bool CMainWindow::IsDebugPanelVisible()
{
    return m_wndSplitter.GetSinglePaneMode() == SPLIT_PANE_NONE ||
        m_wndSplitter.GetSinglePaneMode() == SPLIT_PANE_BOTTOM;
}

void CMainWindow::SetDebugPanelVisible(bool bVisible)
{
    m_wndSplitter.SetSinglePaneMode(bVisible ? SPLIT_PANE_NONE : SPLIT_PANE_TOP);
}

void CMainWindow::AnimateLoadingIndicator(bool isLoading)
{
    if (isLoading) {
        // the wParam indicates starting animation by first frame
        SendMessage(UM_LOADING_INDICATOR, 1);
        // because main window's timer is used by the setTimeout callback, so use another window's
        // timer instead
        m_wndSplitter.SetTimer(TIMER_LOADING_INDICATOR, 42, NULL);
    } else {
        m_wndSplitter.KillTimer(TIMER_LOADING_INDICATOR);

        static HICON s_hDefaultIcon = NULL;
        if (s_hDefaultIcon == NULL) {
            s_hDefaultIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TASKEXECUTOR), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
        }

        SendMessage(WM_SETICON, ICON_SMALL, (LPARAM)s_hDefaultIcon);
    }
}

void CMainWindow::OnFinalMessage(HWND hWnd)
{
    delete this;
}

LRESULT CMainWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    m_wndSplitter.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE);
    m_wndSplitter.m_cxySplitBar = 4;
    m_wndSplitter.m_bFullDrag = FALSE;
    m_wndSplitter.SetSplitterExtendedStyle(SPLIT_BOTTOMALIGNED);

    m_wndBrowserContainer.Create(m_wndSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE);
    m_wndTab.Create(m_wndSplitter, rcDefault, NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
    m_wndLog.Create(m_wndTab, rcDefault, NULL,
        ES_MULTILINE | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_CHILD);
    m_wndLog.SetFont(m_wndTab.GetFont());
    m_wndLog.SetReadOnly(TRUE);
    m_wndTab.AddPage(m_wndLog, _T("Log"));
    m_wndErr.Create(m_wndTab, rcDefault, NULL,
        ES_MULTILINE | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_CHILD);
    m_wndErr.SetFont(m_wndTab.GetFont());
    m_wndErr.SetReadOnly(TRUE);
    m_wndTab.AddPage(m_wndErr, _T("Error"));
    m_wndScript.Create(m_wndTab, rcDefault, NULL,
        ES_MULTILINE | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_CHILD);
    m_wndScript.SetFont(m_wndTab.GetFont());
    m_wndTab.AddPage(m_wndScript, _T("Script"));
    m_wndTab.SetActivePage(0);

    RECT rcClient;
    GetClientRect(&rcClient);
    m_wndSplitter.SetWindowPos(NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER | SWP_NOACTIVATE);
    m_wndSplitter.SetSplitterPanes(m_wndBrowserContainer, m_wndTab);
    m_wndSplitter.SetSplitterPos(rcClient.bottom - 150);

    CefRefPtr<CefCommandLine> cmdline = CefCommandLine::CreateCommandLine();
    cmdline->InitFromString(GetCommandLine());
    if (cmdline->HasSwitch(SWITCH_NODBGPANEL)) {
        SetDebugPanelVisible(false);
    }

    return 0;
}

LRESULT CMainWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    if (m_handler.get() && !m_handler->IsClosing()) {
        m_handler->CloseBrowser(true);
    } else {
        bHandled = FALSE;
    }
    return 0;
}

LRESULT CMainWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    if (m_wndSplitter.IsWindow()) {
        m_wndSplitter.MoveWindow(0, 0, LOWORD(lParam), HIWORD(lParam));
    }
    return 0;
}

LRESULT CMainWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    ATLASSERT(m_handler.get());
    KillTimer((UINT_PTR)wParam);
    m_handler->OnMainWindowTimer((UINT)wParam);
    return 0;
}

LRESULT CMainWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    // do nothing to prevent quit message from being sending
    return 0;
}

LRESULT CMainWindow::OnLuaError(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    const char *err = (const char*)wParam;
    AppendError(CA2T(err));
    free((void*)err);

    return 0;
}

LRESULT CMainWindow::OnNotifyOpener(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    ATLASSERT(m_handler.get());
    m_handler->OnMainWindowNotify((int)wParam);
    return 0;
}

LRESULT CMainWindow::OnLoadingIndicator(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    static int s_index = 0;
    static HICON s_hIcons[24] = {NULL};

    if (wParam) {
        s_index = 0;
    }

    if (s_hIcons[0] == NULL) {
        int cx = GetSystemMetrics(SM_CXICON);
        int cy = GetSystemMetrics(SM_CYICON);
        for (int i = 0; i < _countof(s_hIcons); ++i) {
            s_hIcons[i] = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_INDICATOR1 + i), IMAGE_ICON, cx, cy, 0);
        }
    }

    SendMessage(WM_SETICON, ICON_SMALL, (LPARAM)s_hIcons[s_index++ % _countof(s_hIcons)]);
    return 0;
}

LRESULT CMainWindow::OnTabPageActived(int idCtrl, LPNMHDR pnmh, BOOL bHandled)
{
    if (m_wndTab.IsValidPageIndex(pnmh->idFrom)) {
        LPCTSTR lpszTitle = m_wndTab.GetPageTitle(pnmh->idFrom);
        if (lpszTitle) {
            size_t len = _tcslen(lpszTitle);
            if (lpszTitle[len - 1] == _T('*')) {
                TCHAR szTitle[50] = {0};
                _tcsncpy(szTitle, lpszTitle, min(len - 1, sizeof(szTitle)/sizeof(szTitle[0]) - 1));
                m_wndTab.SetPageTitle(pnmh->idFrom, szTitle);
            }
        }
    }
    return 0;
}

CMainWindow::CMainWindow():
m_wndScript(this)
{
    ++s_nInstCount;
}

CMainWindow::~CMainWindow()
{
    if (--s_nInstCount == 0) {
        CefQuitMessageLoop();
    }
}

void CMainWindow::MarkTabTitleIfNeeded(CRichEditCtrl &page)
{
    int nActivePage = m_wndTab.GetActivePage();
    if (m_wndTab.GetPageHWND(nActivePage) != page.m_hWnd) {
        int nPage = m_wndTab.PageIndexFromHwnd(page.m_hWnd);
        LPCTSTR lpszTitle = m_wndTab.GetPageTitle(nPage);
        if (lpszTitle) {
            size_t len = _tcslen(lpszTitle);
            if (lpszTitle[len - 1] != _T('*')) {
                TCHAR szTitle[50] = {0};
                _tcsncpy(szTitle, lpszTitle, sizeof(szTitle)/sizeof(szTitle[0]) - 2);
                len = _tcslen(szTitle);
                szTitle[len] = _T('*');
                szTitle[len + 1] = _T('\0');
                m_wndTab.SetPageTitle(nPage, szTitle);
            }
        }
    }
}