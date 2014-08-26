// MainDlg.h : interface of the CBasicDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
 
#ifndef _BROWSERWND_H_
#define _BROWSERWND_H_

 





/////////////////////////////////////// 新加 broswer window 消息处理类 ////////////////////////////////

class BrowserWnd : public CWindowImpl<BrowserWnd> //<BrowserWnd, CAxWindow>
{
public:
	HWND tWnd;
	 

	//DECLARE_WND_SUPERCLASS(_T("BrowserWindow"), CAxWindow::GetWndClassName())
	BrowserWnd(){ }

	BEGIN_MSG_MAP(BrowserWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus) 
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown) 
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)  
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)


		//MESSAGE_HANDLER( WM_NCPAINT, OnNcPaint )
		MESSAGE_HANDLER( WM_ERASEBKGND, OnEraseBkgnd ) 
		//MESSAGE_HANDLER( WM_PAINT, OnPaint )  

	END_MSG_MAP()


	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
	 
		return lRet;
	}
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{ 
		bHandled=FALSE;
		return 1;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam); 
		return lRet;
	}
 

	LRESULT	OnNcLButtonDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		//bHandled=FALSE;
 		UINT nHitTest = (INT) wParam;    // hit-test value
		CPoint point(lParam); 
		if(nHitTest == HTTOP)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTBOTTOM)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTLEFT)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTRIGHT)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTTOPLEFT)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTTOPRIGHT)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTBOTTOMLEFT)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		else if(nHitTest == HTBOTTOMRIGHT)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTSYSMENU)
			SendMessage(tWnd,WM_SYSCOMMAND, SC_MOUSEMENU,MAKELPARAM(point.x, point.y));
		else{
			//::SetForegroundWindow( tWnd );   
			SendMessage(tWnd,WM_SYSCOMMAND, SC_MOVE | HTCLIENT, MAKELPARAM(point.x, point.y));
			//bHandled = FALSE;
		}
		return 1;
	}

	LRESULT	OnSetCursor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{ 
		bHandled=FALSE;

		/**
		UINT nHitTest = HIWORD(wParam);//(INT) wParam;    // hit-test value 
		switch (nHitTest)
		{
		case HTTOPLEFT:
		case HTBOTTOMRIGHT:
			{
				SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
			}
			break;
		case HTTOPRIGHT:
		case HTBOTTOMLEFT:
			{
				SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
			}
			break;
		case HTLEFT:
		case HTRIGHT:
			{
			   SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			}
			break;
		case HTTOP:
		case HTBOTTOM:
			{
				SetCursor(::LoadCursor(NULL, IDC_SIZENS));
			}
			break;
		default:
			{
				//SetCursor(::LoadCursor(NULL, IDC_ARROW));
			}
			break;
		}

		**/
		return 0;
	}

	LRESULT	OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled=FALSE;

		if (::IsZoomed(m_hWnd))
		{
			return 0;
		}

		UINT nHitTest = (INT) wParam;    // hit-test value

		CRect rect;
		::GetClientRect(m_hWnd,&rect);  
		CPoint pt(lParam);  
		::ScreenToClient(m_hWnd,&pt); 
		static int nFrame=3; // 窗口边框的宽度

		rect.DeflateRect(nFrame,nFrame);

		bHandled =TRUE;
		if (!rect.PtInRect(pt))
		{
			if (pt.x<=nFrame && pt.y>=rect.bottom-nFrame)
			{

				return HTBOTTOMLEFT;
			}
			else if (pt.x<=nFrame && pt.y<=nFrame)
			{
				return HTTOPLEFT;
			}
			else if (pt.x>=rect.right-nFrame && pt.y<=nFrame)
			{
				return HTTOPRIGHT;
			}
			else if (pt.x>=rect.right-nFrame && pt.y>=rect.bottom-nFrame)
			{
				return HTBOTTOMRIGHT;
			}
			else if (pt.x<=nFrame)
			{
				return HTLEFT;
			}
			else if (pt.y<=nFrame)
			{
				return HTTOP;
			}
			else if (pt.y>=rect.bottom-nFrame)
			{
				return HTBOTTOM;
			}
			else if (pt.x>=rect.right-nFrame)
			{
				return HTRIGHT;
			}else{
				return HTCLIENT;
			}
		}
		else
		{ 
			//OutputDebugString(_T("OnNcHitTest \n"));
			//return HTCAPTION;
		} 
		bHandled = FALSE; 
		return 0;
	}


	//清除背景响应
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		//在OnEraseBkgnd写一段，确定WEBBROWSER所在的区域，然后将这个区域InvalidateRgn掉，就OK了，我这是这么干的。
		//CPaintDC dc(this);
		//CRect rect;
		//GetClientRect(&rect);
		//CRgn rgnWeb,rgnUpdate;
		//if ( !rect.EqualRect(&rcPreSize) )//rcPreSize,CRect类型的窗口成员，用于记录窗口大小。如果窗口没改变大小将不挖坑
		//{    
		////PS：计算无效区域
		//CRect rectAll;
		//GetWindowRect(&rectAll);
		//rgnUpdate.CreateRectRgn(/*写上窗口区域相关的数据*/);
		//rgnWeb.CreateRectRgn(/*WEBBROWSER区域的数据*/);
		//rgnUpdate.CombineRgn(&rgnUpdate,&rgnWeb,RGN_DIFF);
		//InvalidateRgn(&rgnUpdate,FALSE);
		//}
		//rgnWeb.DeleteObject();
		//rgnUpdate.DeleteObject();
		//GetClientRect(&rcPreSize);
		//     
		return TRUE;

	}
    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
     {

 
 
		 return TRUE;
     } 
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
     {
 
 
		 return TRUE;
        //return ::DefWindowProc(static_cast<T*>(this)->m_hWnd, uMsg, wParam, lParam);
     } 
 
};


#endif  