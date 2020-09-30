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

		//HBRUSH hbr = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF)); // ��ɫ��ˢ

		//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0x00, 0x00)); // ��ɫ��ˢ

		//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // ��ɫ��ˢ

		//HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH); //͸����ˢ

		HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // ��ɫ��ˢ

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

/* �����쳣��������ص����� */
LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	FatalAppExit(0, _T("OK, You get an Unhandled Exception !"));
	return EXCEPTION_EXECUTE_HANDLER;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// �����������
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	// ע��OpenGL������Ϣ������
	//MyRegisterWnd(_T("OpenGLWnd"), OpenGLWndDisplayProc);
	MyRegisterWnd((TCHAR*)("OpenGLWnd"), OpenGLWndDisplayProc);


	// ��һ���� ʵ���������Ⱦ�����
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CWndShadow::Initialize(hInstance);//������Ӱ��ʼ��

	// �ڶ�������ʼ��COM��, Ϊ����COM���ṩ֧��
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return 0;
	}

	// ������������������
	MainWnd mainWnd;

	mainWnd.Create(NULL, _T("DuilibWithModernOpenGL"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	mainWnd.CenterWindow();
	::ShowWindow(mainWnd, SW_SHOW);

	// ��������������Ϣѭ��
	CPaintManagerUI::MessageLoop();

	// ���߲����˳������ͷ�COM��
	::CoUninitialize();

	return 0;
}