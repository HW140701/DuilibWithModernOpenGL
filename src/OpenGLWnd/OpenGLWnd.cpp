#include "OpenGLWnd.h"

template<> OpenGLWnd::ptr Singleton<OpenGLWnd>::_instance = nullptr;

OpenGLWnd::OpenGLWnd()
{
}

OpenGLWnd::~OpenGLWnd()
{
}

OpenGLWnd::ptr OpenGLWnd::GetSingleton()
{
	if (_instance == nullptr)
		return _instance = std::make_shared<OpenGLWnd>();

	return _instance;
}
