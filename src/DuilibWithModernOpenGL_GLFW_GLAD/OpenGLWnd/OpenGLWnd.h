#ifndef OPENGL_WND_H
#define OPENGL_WND_H

#include "GlobalHeader.h"
#include "Utils/Singleton.h"
#include <memory>

class OpenGLWnd
{
public:
	typedef std::shared_ptr<OpenGLWnd> ptr;
	OpenGLWnd();
	virtual~OpenGLWnd();

	static OpenGLWnd::ptr GetInstance();
	
public:
	void OnCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnDestory(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	bool CreateOpenGLWindow(HWND hWnd);

	void LoopRender();
private:
	bool m_IsDebug;
	GLFWwindow* m_pRenderWrapWindowHandler;
	std::shared_ptr<std::thread> m_RenderThreadPtr;
};

#endif // !OPENGL_WND_H
