#include "GlobalHeader.h"
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
		OpenGLWnd::GetInstance()->OnCreate(hWnd, message, wParam, lParam);
	}
	break;

	case WM_SIZE:
	{
		OpenGLWnd::GetInstance()->OnSize(hWnd, message, wParam, lParam);
	}
	break;

	case WM_PAINT:
	{
		OpenGLWnd::GetInstance()->OnPaint(hWnd, message, wParam, lParam);
	}
	break;

	case WM_DESTROY:
	{
		OpenGLWnd::GetInstance()->OnDestory(hWnd, message, wParam, lParam);
	}
	break;

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


bool MyRegisterOpenGLWnd(TCHAR* szClass, WNDPROC proc)
{
	WNDCLASS wndclass;

	if (GetClassInfo(GetModuleHandle(NULL), szClass, &wndclass))
	{
		return 1;// name already registered - ok if it was us  
	}
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = proc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClass;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szClass, MB_ICONERROR);
		return false;
	}

	return true;

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
	//MyRegisterWnd((TCHAR*)("OpenGLWnd"), OpenGLWndDisplayProc);
	MyRegisterOpenGLWnd((TCHAR*)("OpenGLWnd"), OpenGLWndDisplayProc);

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