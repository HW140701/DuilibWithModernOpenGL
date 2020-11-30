#ifndef C_WND_UI_H
#define C_WND_UI_H

// �������HWND�Ŀؼ���ʾ��CControlUI����
class CWndUI : public CControlUI
{
public:
	CWndUI() : m_hWnd(NULL) {}

	/* �����¿ؼ�������Ӧ����д������������GetClass��GetInterface��
	���Ǻ��������ֿؼ������͵��麯�������ڶ�̬ʶ��ؼ����ͺ����ؼ�������ת���� */
	virtual LPCTSTR GetClass() const
	{
		return _T("WndUI");
	}

	virtual LPVOID GetInterface(LPCTSTR pstrName)
	{
		if (_tcsicmp(pstrName, _T("Wnd")) == 0)
		{
			return static_cast<CWndUI*>(this);
		}
		return CControlUI::GetInterface(pstrName);
	}


	virtual void SetVisible(bool bVisible = true)
	{
		__super::SetVisible(bVisible);
		::ShowWindow(m_hWnd, bVisible);
	}

	virtual void SetInternVisible(bool bVisible = true)
	{
		__super::SetInternVisible(bVisible);
		::ShowWindow(m_hWnd, bVisible);
	}

	virtual void SetPos(RECT rc)
	{
		__super::SetPos(rc);
		::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	BOOL Attach(HWND hWndNew)
	{
		if (!::IsWindow(hWndNew))
		{
			return FALSE;
		}

		m_hWnd = hWndNew;
		return TRUE;
	}

	HWND Detach()
	{
		HWND hWnd = m_hWnd;
		m_hWnd = NULL;
		return hWnd;
	}

	HWND GetHWND()
	{
		return m_hWnd;
	}

protected:
	HWND m_hWnd;
};

#endif // !C_WND_UI_H
