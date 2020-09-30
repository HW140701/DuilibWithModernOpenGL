#include "stdafx.h"
#include "UI/MainWnd.h"
#include "OpenGLWnd/OpenGLWnd.h"


LRESULT CALLBACK OpenGLWndDisplayProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
	{

	}

	break;

	case WM_DESTROY:
	{
	}

	break;

	case WM_TIMER:
	{

	}
	break;

	case WM_PAINT:
	{
		HDC hDC = ::GetDC(hWnd);

		RECT rc = { 0 };

		GetClientRect(hWnd, &rc);

		//HBRUSH hbr = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF)); // 白色画刷

		//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0x00, 0x00)); // 黑色画刷

		//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // 红色画刷

		//HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH); //透明画刷

		HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // 绿色画刷

		::FillRect(hDC, &rc, hbr);

		::DeleteObject(hbr);

		::ReleaseDC(hWnd, hDC);
	}


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



ATOM MyRegisterWnd(TCHAR* szClass, WNDPROC proc)
{
	WNDCLASS wcls;
	// check to see if class already registered  
	if (GetClassInfo(GetModuleHandle(NULL), szClass, &wcls))
	{
		return 1;// name already registered - ok if it was us  
	}
	// Use standard "button" control as a template.  
	GetClassInfo(NULL, _T("button"), &wcls);
	// set new values  
	wcls.style |= CS_DBLCLKS; // Make it to receive double clicks  
	wcls.lpfnWndProc = proc;
	wcls.hInstance = GetModuleHandle(NULL);
	wcls.lpszClassName = szClass;

	return RegisterClass(&wcls);
}

/* 程序异常崩溃处理回调函数 */
LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	FatalAppExit(0, _T("OK, You get an Unhandled Exception !"));
	return EXCEPTION_EXECUTE_HANDLER;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// 程序崩溃捕获
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	// 注册OpenGL窗口消息处理函数
	//MyRegisterWnd(_T("OpenGLWnd"), OpenGLWndDisplayProc);
	MyRegisterWnd((TCHAR*)("OpenGLWnd"), OpenGLWndDisplayProc);


	// 第一步： 实例句柄与渲染类关联
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CWndShadow::Initialize(hInstance);//窗体阴影初始化

	// 第二步：初始化COM库, 为加载COM库提供支持
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return 0;
	}

	// 第三步：创建窗口类
	MainWnd mainWnd;

	mainWnd.Create(NULL, _T("DuilibWithModernOpenGL"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	mainWnd.CenterWindow();
	::ShowWindow(mainWnd, SW_SHOW);

	// 第六步：处理消息循环
	CPaintManagerUI::MessageLoop();

	// 第七步：退出程序并释放COM库
	::CoUninitialize();

	return 0;
}