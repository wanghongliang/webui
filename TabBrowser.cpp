// TabBrowser.cpp : main source file for TabBrowser.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlctrlw.h>
#include <atldlgs.h>
#include <atlmisc.h>

#include "resource.h"

#include "BrowserView.h"
#include "CustomTabView.h"
#include "AddressCombo.h"
#include "OpenDlg.h"
#include "WindowsDlg.h"
#include "AboutDlg.h"
#include "MainFrm.h"
#include "MainWindow.h"
#include "WndShadow.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);



	CMainFrame wndMain; 
	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	} 
	wndMain.ShowWindow(nCmdShow);



	//CMainWindow mainWindow;
	//if(mainWindow.Create(NULL) == NULL)
	//{
	//	ATLTRACE(_T(" CMainWindow creation failed!\n"));
	//	return 0;
	//}
	//mainWindow.ShowWindow(nCmdShow);



		//CBrowserView* pView = new CBrowserView;
		//RECT rcDefault = {100,100,100,100};

		//pView->Create(wndMain.m_hWnd,rcDefault , _T("http://www.baidu.com"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL);
		//if(pView->IsWindow()){
		//	pView->ShowWindow(nCmdShow);
		//}



	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES);

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	//CWndShadow::Initialize(hInstance );   

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
