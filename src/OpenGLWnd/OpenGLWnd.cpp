#include "OpenGLWnd.h"

OpenGLWnd::OpenGLWnd()
{
}

OpenGLWnd::~OpenGLWnd()
{
}

OpenGLWnd::ptr OpenGLWnd::GetSingleton()
{
	return Singleton<OpenGLWnd>::GetInstance();
}
