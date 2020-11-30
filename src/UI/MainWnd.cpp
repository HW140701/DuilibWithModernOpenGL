#include "MainWnd.h"

// 按钮
const TCHAR* const Btn_Min = _T("Btn_Min");
const TCHAR* const Btn_Max = _T("Btn_Max");
const TCHAR* const Btn_Close = _T("Btn_Close");


// OpenGL窗口
const TCHAR* const Wnd_OpenGLWnd = _T("Wnd_OpenGLWnd");

// 自定义Wnd
const TCHAR* const WndUI = _T("Wnd");

MainWnd::MainWnd()
{
	m_pOpenGLWnd = nullptr;
}

MainWnd::~MainWnd()
{
}

LPCTSTR MainWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}

DuiLib::CDuiString MainWnd::GetSkinFile()
{
	return _T("MainWnd.xml");
}

CDuiString MainWnd::GetSkinFolder()
{
	return _T("../../../resource/skin");
}

void MainWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClickProcess(msg);
	}
	if (_tcsicmp(msg.sType, _T("itemselect")) == 0)
	{

	}

	WindowImplBase::Notify(msg);
}

CControlUI* MainWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, WndUI) == 0)
	{
		if (m_pOpenGLWnd == nullptr)
		{
			m_pOpenGLWnd = new CWndUI();
			m_OpenGLHWND = CreateWindow(_T("OpenGLWnd"), _T("win32"), WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS, 0, 0, 0, 0, m_PaintManager.GetPaintWindow(), NULL, NULL, NULL);
			m_pOpenGLWnd->Attach(m_OpenGLHWND);
			m_pOpenGLWnd->OnSize += MakeDelegate(this, &MainWnd::OnTargetSizeChanged);
		}

		return m_pOpenGLWnd;
	}

	return nullptr;
}

LRESULT MainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;

	default:
		bHandled = FALSE;

		break;
	}
	if (bHandled) return lRes;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

void MainWnd::InitWindow()
{
}

LRESULT MainWnd::OnClose(UINT, WPARAM, LPARAM, BOOL& bHandled)
{

	bHandled = FALSE;
	return 0;
}

bool MainWnd::OnTargetSizeChanged(void* param)
{
	CHorizontalLayoutUI* pHorizontalLayoutUI = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("HorizontalLayout_OpenGL")));
	if (!pHorizontalLayoutUI)
		return true;

	const RECT& rc_pos = pHorizontalLayoutUI->GetPos();

	CWndUI* pUI = static_cast<CWndUI*>(m_PaintManager.FindControl(_T("Wnd_OpenGLWnd")));
	if (!pUI)
		return false;

	// 得到OpenGL窗口的宽高
	int openGLWndWidth = rc_pos.right - rc_pos.left;
	int openGLWndHeight = rc_pos.bottom - rc_pos.top;

	if (openGLWndWidth >= 0 && openGLWndHeight >= 0)
	{
		::MoveWindow(pUI->GetHWND(), rc_pos.left, rc_pos.top, openGLWndWidth, openGLWndHeight, TRUE);
	}

	return true;
}

void MainWnd::OnClickProcess(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), Btn_Close) == 0)
	{
		// 然后发送关闭窗口和退出程序消息
		::SendMessage(this->GetHWND(), WM_CLOSE, NULL, NULL);
		PostQuitMessage(0);
	}
	// 最小化窗口
	else if (_tcsicmp(msg.pSender->GetName(), Btn_Min) == 0)
	{
#if defined(UNDER_CE)
		::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
	}
	// 最大化窗口
	else if (_tcsicmp(msg.pSender->GetName(), Btn_Max) == 0)
	{
#if defined(UNDER_CE)
		::ShowWindow(m_hWnd, SW_MAXIMIZE);
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
		if (pControl) pControl->SetVisible(false);
		pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
		if (pControl) pControl->SetVisible(true);
#else
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
#endif
	}
}
