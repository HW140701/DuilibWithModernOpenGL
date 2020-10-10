#include "OpenGLWnd.h"
#include "glad/glad.h"

OpenGLWnd::OpenGLWnd()
{
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
	CreateOpenGLWindow();
}

void OpenGLWnd::OnDestory(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void OpenGLWnd::OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC = ::GetDC(hWnd);

	RECT rc = { 0 };

	GetClientRect(hWnd, &rc);

	//HBRUSH hbr = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF)); // °×É«»­Ë¢

	//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0x00, 0x00)); // ºÚÉ«»­Ë¢

	//HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // ºìÉ«»­Ë¢

	//HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH); //Í¸Ã÷»­Ë¢

	HBRUSH hbr = ::CreateSolidBrush(RGB(0x00, 0xFF, 0x00)); // ÂÌÉ«»­Ë¢

	::FillRect(hDC, &rc, hbr);

	::DeleteObject(hbr);

	::ReleaseDC(hWnd, hDC);
}

bool OpenGLWnd::CreateOpenGLWindow()
{


	return true;
}
