#include "OpenGLWnd.h"
#include <functional>

OpenGLWnd::OpenGLWnd()
{
#ifdef DEBUG
	m_IsDebug = false;
#elif
	m_IsDebug = true;
#endif // DEBUG

	m_RenderThreadPtr = nullptr;

}

OpenGLWnd::~OpenGLWnd()
{
}

OpenGLWnd::ptr OpenGLWnd::GetInstance()
{
	return Singleton<OpenGLWnd>::GetInstance();
}

void OpenGLWnd::OnCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//CreateOpenGLWindow(hWnd);

	CreateOpenGLRenderContext_GLEW(hWnd);
}


void OpenGLWnd::OnDestory(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//glfwSetWindowShouldClose(m_pRenderWrapWindowHandler, true);
	//if (m_RenderThreadPtr != nullptr)
	//{
	//	m_RenderThreadPtr->join();
	//}

	if (m_HGLRC) 
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_HGLRC);
	}
}

void OpenGLWnd::OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HDC hDC = ::GetDC(hWnd);

	//RECT rc = { 0 };

	//GetClientRect(hWnd, &rc);

	////HBRUSH hbr = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF)); // 白色画刷

	////HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0x00, 0x00)); // 黑色画刷

	////HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // 红色画刷

	////HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH); //透明画刷

	//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // 绿色画刷

	//::FillRect(hDC, &rc, hbr);

	//::DeleteObject(hbr);

	//::ReleaseDC(hWnd, hDC);

	OpenGLRender_GLEW(hWnd);
}

void OpenGLWnd::OnSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wndHeight = HIWORD(lParam);
	int wndWidth = LOWORD(lParam);

	//glfwSetWindowSize(m_pRenderWrapWindowHandler, wndWidth, wndHeight);

	glViewport(0, 0, wndWidth, wndHeight);
}

bool OpenGLWnd::CreateOpenGLWindow(HWND hWnd)
{
	//// 得到Duilib下Windows子窗口的大小
	//CRect rect;
	//GetClientRect(hWnd, rect);
	//int childWndwidth = rect.Width();
	//int childWndHeight = rect.Height();

	// glfw: initialize and configure
	// ------------------------------
	//glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 16);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);// 设置可调整窗口大小
	//// debug context.
	//if (m_IsDebug)
	//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//else
	//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);

	//// glfw window creation
	//// --------------------
	//m_pRenderWrapWindowHandler = glfwCreateWindow(100, 100, "glfwOpenGLWnd", nullptr, nullptr);
	//if (m_pRenderWrapWindowHandler == nullptr)
	//{
	//	std::cout << "Failed to create GLFW window." << std::endl;
	//	glfwTerminate();
	//	return false;
	//}
	//glfwMakeContextCurrent(m_pRenderWrapWindowHandler);

	//// glad: load all OpenGL function pointers
	//// ---------------------------------------
	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//{
	//	std::cout << "Failed to initialize GLAD" << std::endl;
	//	return false;
	//}

	////取得glfw窗口句柄并将其嵌入Windows父窗口
	//HWND hwndGLFW = glfwGetWin32Window(m_pRenderWrapWindowHandler);
	//SetWindowLong(hwndGLFW, GWL_STYLE, WS_VISIBLE);
	//MoveWindow(hwndGLFW, 0, 0, 0, 0, TRUE);
	//SetParent(hwndGLFW, hWnd);

	////将渲染移交线程前需要将当前上下文设为null
	//glfwMakeContextCurrent(NULL);

	//// 开启渲染子线程
	//m_RenderThreadPtr.reset();
	//m_RenderThreadPtr = nullptr;
	//m_RenderThreadPtr = std::make_shared<std::thread>(std::bind(&OpenGLWnd::LoopRender, this));

	return true;
}

void OpenGLWnd::LoopRender()
{
	//if (m_pRenderWrapWindowHandler != nullptr)
	//{
	//	glfwMakeContextCurrent(m_pRenderWrapWindowHandler);

	//	while (!glfwWindowShouldClose(m_pRenderWrapWindowHandler))
	//	{
	//		//刷新颜色缓冲和深度
	//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


	//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	//		// -------------------------------------------------------------------------------
	//		glfwSwapBuffers(m_pRenderWrapWindowHandler);
	//		glfwPollEvents();
	//	}
	//	glfwTerminate();
	//}
}


bool OpenGLWnd::CreateOpenGLRenderContext_GLEW(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);

	// 1. SetupPixelFormat
	//PIXELFORMATDESCRIPTOR pfd = {
	//sizeof(PIXELFORMATDESCRIPTOR),  /* size */
	//1,                              /* version */
	//PFD_SUPPORT_OPENGL |
	//PFD_DRAW_TO_WINDOW |
	//PFD_DOUBLEBUFFER,               /* support double-buffering */
	//PFD_TYPE_RGBA,                  /* color type */
	//24,                             /* prefered color depth */
	//0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
	//0,                              /* no alpha buffer */
	//0,                              /* alpha bits (ignored) */
	//0,                              /* no accumulation buffer */
	//0, 0, 0, 0,                     /* accum bits (ignored) */
	//24,                             /* depth buffer */
	//8,                              /* no stencil buffer */
	//0,                              /* no auxiliary buffers */
	//PFD_MAIN_PLANE,                 /* main layer */
	//0,                              /* reserved */
	//0, 0, 0,                        /* no layer, visible, damage masks */
	//};

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat;

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (pixelFormat == 0)
	{
		MessageBox(WindowFromDC(hDC), "ChoosePixelFormat failed.", "Error",
			MB_ICONERROR | MB_OK);
		return false;
	}

	if (SetPixelFormat(hDC, pixelFormat, &pfd) != TRUE)
	{
		MessageBox(WindowFromDC(hDC), "SetPixelFormat failed.", "Error",
			MB_ICONERROR | MB_OK);
		return false;
	}
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		MessageBox(WindowFromDC(hDC), "Palette pixel format not supported..", "Error",
			MB_ICONERROR | MB_OK);
		exit(1);
	}


	m_HGLRC = wglCreateContext(hDC);
	if (m_HGLRC == NULL)
	{
		MessageBox(WindowFromDC(hDC), "wglCreateContext failed!", "Error",
			MB_ICONERROR | MB_OK);
		return false;
	}

	if (wglMakeCurrent(hDC, m_HGLRC) == false)
	{

		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		AfxMessageBox(_T("GLEW is not initialized!"));

		return false;
	}

	if (WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0);
	}

	SwapBuffers(hDC);

	return true;
}

void OpenGLWnd::OpenGLRender_GLEW(HWND hWnd)
{
	static DWORD LastFPSTime = GetTickCount(), LastFrameTime = LastFPSTime, FPS = 0;

	PAINTSTRUCT ps;

	DWORD Time = GetTickCount();

	float FrameTime = (Time - LastFrameTime) * 0.001f;

	LastFrameTime = Time;

	if (Time - LastFPSTime > 1000)
	{
	}
	else
	{
		FPS++;
	}

	HDC hDC = BeginPaint(hWnd, &ps);

	if (m_HGLRC)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


		SwapBuffers(hDC);
	}

	EndPaint(hWnd, &ps);

	InvalidateRect(hWnd, NULL, FALSE);
}
