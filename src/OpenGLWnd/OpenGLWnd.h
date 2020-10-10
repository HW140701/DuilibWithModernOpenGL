#ifndef OPENGL_WND_H
#define OPENGL_WND_H

#include "stdafx.h"
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

private:
	bool CreateOpenGLWindow();
};

#endif // !OPENGL_WND_H
