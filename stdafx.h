// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0100

//#define _WTL_USE_CSTRING
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _ATL_USE_CSTRING_FLOAT
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES



#ifdef _VC80X
  // Support for VS2005 Express & SDK ATL
  #define _CRT_SECURE_NO_DEPRECATE
  #pragma conform(forScope, off)
  #pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")
  #pragma warning(disable: 4565) // redefinition; the symbol was previously declared with __declspec(noalias)
  #pragma warning(disable: 4068) // unknown pragma
#endif // _VC80X


#include <atlbase.h> 
#include <atlstr.h>
#include <atltypes.h>
#include <atlapp.h>

 

 
//获取应用程序数据目录时需要的头文件 CSIDL_LOCAL_APPDATA
#include <shlobj.h> 
#include <atlmisc.h>
#include <string>
#include <vector>
#include <map>
using namespace std;



#ifndef TRACE
#define TRACE ATLTRACE
#endif








#ifdef _VC80X
  // Support for VS2005 Express & SDK ATL
  namespace ATL
  {
	inline void * __stdcall __AllocStdCallThunk()
	{
		return ::HeapAlloc(::GetProcessHeap(), 0, sizeof(_stdcallthunk));
	}

	inline void __stdcall __FreeStdCallThunk(void *p)
	{
		::HeapFree(::GetProcessHeap(), 0, p);
	}
  };
#endif // _VC80X

#include <atlapp.h>

extern CAppModule _Module;

 
#include <atlcom.h>

//#if (_ATL_VER < 0x0700)
  //#pragma warning(default: 4100)
  //#pragma warning(default: 4189)

//禁止输出警告信息， 如：未引用的变量等信息
#pragma warning(disable: 4100)
#pragma warning(disable: 4189)
#pragma warning(disable: 4290)


//#endif

#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

#ifdef _EMBEDDED_MANIFEST
  #if defined _M_IX86
    #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #elif defined _M_IA64
    #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #elif defined _M_X64
    #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #else
    #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #endif
#endif // _EMBEDDED_MANIFEST
