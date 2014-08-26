// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once 
#include <time.h>  
#include <Windows.h>


template <class T, COLORREF t_crBrushColor>
class CPaintBkgnd : public CMessageMap
{
	
protected:
    HBRUSH m_hbrBkgnd;
 

	bool m_isInitShow;		//是否初始化显示 
	bool m_isInitIE;		//是否初始化过 
	bool m_isLayeredWnd;	//是否设置layered窗口 
	time_t m_activeTime;	//激活时间

public:

	enum Flags
	{
		// Window want's to syncronize the activation state with owner.
		Move         = 0x00000001,
		Size         = 0x00000002
	};

	 //初始化方法
     CPaintBkgnd() { 
		m_isInitShow	=	false;
		m_isInitIE		=	false;
		m_isLayeredWnd	=	false; 
		m_activeTime	=	0; 
		m_hbrBkgnd = CreateSolidBrush(t_crBrushColor);		//笔刷
 
	 }

	 //析构方法 
     ~CPaintBkgnd() {  
		 //删除笔刷对象
		 DeleteObject(m_hbrBkgnd); 
	 }

     BEGIN_MSG_MAP(CPaintBkgnd) 

		MESSAGE_HANDLER( WM_SHOWWINDOW, OnShowWindow )

		MESSAGE_HANDLER( WM_LBUTTONDOWN,  OnLButtonDown ) 
		MESSAGE_HANDLER( WM_NCACTIVATE, OnNcActivate)
		MESSAGE_HANDLER( WM_ACTIVATEAPP, OnActivateApp )  
		MESSAGE_HANDLER( WM_MOVE, OnMove )		//移动消息处理
		MESSAGE_HANDLER( WM_SIZE, OnSize )
		//MESSAGE_HANDLER( WM_SYSCOMMAND, OnSysCommand)
		
		//MESSAGE_HANDLER( WM_WINDOWPOSCHANGED, OnWindowPosChanged)

		//MESSAGE_HANDLER( WM_NCPAINT, OnNcPaint )
		MESSAGE_HANDLER( WM_ERASEBKGND, OnEraseBkgnd ) 
		//MESSAGE_HANDLER( WM_PAINT, OnPaint )  

		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
     END_MSG_MAP()
public: 
	//清除背景响应
	LRESULT OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		bHandled = false;
		WINDOWPOS* lpwndpos = (WINDOWPOS*)lParam;

		int flags  = lpwndpos->flags;
		 
		return ::DefWindowProc(static_cast<T*>(this)->m_hWnd, uMsg, wParam, lParam);
		
	}
    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
     {
		 
		 return TRUE;
     } 
	
	//清除背景响应
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{ 
		 

		return TRUE;

	}
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
     {
		 return TRUE;
        //return ::DefWindowProc(static_cast<T*>(this)->m_hWnd, uMsg, wParam, lParam);
     } 
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{ 
		CPoint pt(lParam);  
		static_cast<T*>(this)->PostMessage ( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x,pt.y));  
		return 0;
	} 
 	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//TRACE(_T("OnSysCommand \n" ));
		int Type = (int)wParam;
		switch( Type ){
		case SC_RESTORE:
			 
			break;
		}
		return ::DefWindowProc(static_cast<T*>(this)->m_hWnd, uMsg, wParam, lParam);
	}
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//int tag = (int)wParam;
		//TRACE(_T( "OnGetMinMaxInfo %d \n" ), tag); 

	
		//PMINMAXINFO info = (PMINMAXINFO)lParam;
		//MONITORINFO monitor = {0};
		//monitor.cbSize = sizeof(monitor);
		//HMONITOR hMonitor = ::MonitorFromWindow(static_cast<T*>(this)->m_hWnd, MONITOR_DEFAULTTOPRIMARY);
		//::GetMonitorInfo(hMonitor, &monitor);

 
		//info->ptMaxPosition.x = 0;//monitor.rcWork.left;
		//info->ptMaxPosition.y = 0;//monitor.rcWork.top;
		//info->ptMaxSize.x = monitor.rcWork.right - monitor.rcWork.left - 0;
		//info->ptMaxSize.y = monitor.rcWork.bottom - monitor.rcWork.top - 0;
		//info->ptMinTrackSize.x = monitor.rcWork.right - monitor.rcWork.left;
		//info->ptMinTrackSize.y = monitor.rcWork.bottom - monitor.rcWork.top;


		//bHandled = FALSE;
		//return 0;

		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(static_cast<T*>(this)->m_hWnd, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
		CRect rcWork = oMonitor.rcWork;
		//rcWork.Offset(-rcWork.left, -rcWork.top);

		LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
		//lpMMI->ptMaxPosition.x	= rcWork.left;
		//lpMMI->ptMaxPosition.y	= rcWork.top;
		//lpMMI->ptMaxSize.x		= rcWork.right;
		lpMMI->ptMaxSize.y		= rcWork.bottom;
		//lpMMI->ptMinTrackSize.x = rcWork.right - rcWork.left;
		//lpMMI->ptMinTrackSize.y = rcWork.bottom - rcWork.top;
		bHandled = FALSE;
		 
		lpMMI->ptMinTrackSize.x = 300;
		lpMMI->ptMinTrackSize.y = 100;
		return 0;


	}


	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{ 
		 
		return 0;
	}
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		this->OnSize( wParam, lParam); 
		return 0;
	}
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{	
		//TRACE(_T("OnNcActivate \n"));
		if( (BOOL)wParam ){
			//SyncBgWnd();
		}else{
			
		}
		return ::DefWindowProc(static_cast<T*>(this)->m_hWnd, uMsg, wParam, lParam);
	}
	LRESULT OnActivateApp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//bHandled = FALSE; // 拦截此消息  
		 
		return 0;
	}	

	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//bHandled = FALSE; // 拦截此消息 
		 
		return 0;
	}

 

	//右下角显示 
	//@param marginLeft 右边距设置
	void BottomWindow(int marginLeft=0){	

		HWND m_hWnd = static_cast<T*>(this)->m_hWnd;
		RECT rcDlg = {0};
		::GetWindowRect(m_hWnd, &rcDlg);
		RECT rcArea = { 0 };
		RECT rcCenter = { 0 };
		HWND hWndParent = ::GetParent(m_hWnd);
		HWND hWndCenter = ::GetWindow(m_hWnd,GW_OWNER);//::GetWindowOwner(m_hWnd);
		::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
		if( hWndCenter == NULL ) rcCenter = rcArea; else ::GetWindowRect(hWndCenter, &rcCenter);

		int DlgWidth = rcDlg.right - rcDlg.left;
		int DlgHeight = rcDlg.bottom - rcDlg.top; 
		// Find dialog's upper left based on rcCenter
		int xLeft = rcCenter.right  - DlgWidth -12;

		if( marginLeft>0 ){
			xLeft = xLeft + marginLeft;
		}
		int yTop = rcCenter.bottom  - DlgHeight - 8 ; 
		::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

		//SyncSize(Move);
	}
	void CloseDialog(int nVal){  
	}  

	void HideDialog(){ 
		
	}


	void Init(){ 
	};
	virtual void OnSize(WPARAM wParam, LPARAM lParam){};
	virtual void InitIE(){};
	
};
