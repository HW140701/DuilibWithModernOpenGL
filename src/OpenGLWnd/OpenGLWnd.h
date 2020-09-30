#ifndef OPENGL_WND_H
#define OPENGL_WND_H

#include "Utils/Singleton.h"
#include <memory>

class OpenGLWnd : public Singleton<OpenGLWnd>
{
public:
	typedef std::shared_ptr<OpenGLWnd> ptr;
	OpenGLWnd();
	virtual~OpenGLWnd();

	static OpenGLWnd::ptr GetSingleton();
	
private:

};

#endif // !OPENGL_WND_H
