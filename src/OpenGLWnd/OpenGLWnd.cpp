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
	CreateOpenGLWindow(hWnd);
}

void OpenGLWnd::OnDestory(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	glfwSetWindowShouldClose(m_pRenderWrapWindowHandler, true);
	if (m_RenderThreadPtr != nullptr)
	{
		m_RenderThreadPtr->join();
	}
}

void OpenGLWnd::OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HDC hDC = ::GetDC(hWnd);

	//RECT rc = { 0 };

	//GetClientRect(hWnd, &rc);

	////HBRUSH hbr = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF)); // ��ɫ��ˢ

	////HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0x00, 0x00)); // ��ɫ��ˢ

	////HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // ��ɫ��ˢ

	////HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH); //͸����ˢ

	//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // ��ɫ��ˢ

	//::FillRect(hDC, &rc, hbr);

	//::DeleteObject(hbr);

	//::ReleaseDC(hWnd, hDC);
}

void OpenGLWnd::OnSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wndHeight = HIWORD(lParam);
	int wndWidth = LOWORD(lParam);

	glfwSetWindowSize(m_pRenderWrapWindowHandler, wndWidth, wndHeight);

	glViewport(0, 0, wndWidth, wndHeight);
}

bool OpenGLWnd::CreateOpenGLWindow(HWND hWnd)
{
	// �õ�Duilib��Windows�Ӵ��ڵĴ�С
	CRect rect;
	GetClientRect(hWnd, rect);
	int childWndwidth = rect.Width();
	int childWndHeight = rect.Height();

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);// ���ÿɵ������ڴ�С
	// debug context.
	if (m_IsDebug)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	else
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);

	// glfw window creation
	// --------------------
	m_pRenderWrapWindowHandler = glfwCreateWindow(100, 100, "glfwOpenGLWnd", nullptr, nullptr);
	if (m_pRenderWrapWindowHandler == nullptr)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_pRenderWrapWindowHandler);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	//ȡ��glfw���ھ��������Ƕ��Windows������
	HWND hwndGLFW = glfwGetWin32Window(m_pRenderWrapWindowHandler);
	SetWindowLong(hwndGLFW, GWL_STYLE, WS_VISIBLE);
	MoveWindow(hwndGLFW, 0, 0, 0, 0, TRUE);
	SetParent(hwndGLFW, hWnd);

	//����Ⱦ�ƽ��߳�ǰ��Ҫ����ǰ��������Ϊnull
	glfwMakeContextCurrent(NULL);

	// ������Ⱦ���߳�
	m_RenderThreadPtr.reset();
	m_RenderThreadPtr = nullptr;
	m_RenderThreadPtr = std::make_shared<std::thread>(std::bind(&OpenGLWnd::LoopRender, this));

	return true;
}

void OpenGLWnd::LoopRender()
{
	if (m_pRenderWrapWindowHandler != nullptr)
	{
		glfwMakeContextCurrent(m_pRenderWrapWindowHandler);

		while (!glfwWindowShouldClose(m_pRenderWrapWindowHandler))
		{
			//ˢ����ɫ��������
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);




			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(m_pRenderWrapWindowHandler);
			glfwPollEvents();
		}
		glfwTerminate();
	}
}
