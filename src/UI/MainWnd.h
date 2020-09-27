#ifndef MAINWND_H
#define MAINWND_H

#include "stdafx.h"
#include "DuilibExternal/CWndUI.h"

class MainWnd : public WindowImplBase
{
public:
	MainWnd();
	virtual~MainWnd();

public:
	virtual LPCTSTR    GetWindowClassName() const;													    // ���ó���������
	virtual DuiLib::CDuiString GetSkinFile();														    // ����Ƥ���ļ�
	virtual CDuiString GetSkinFolder();																    // ����Ƥ���ļ�·
	virtual void Notify(TNotifyUI& msg);															    // ��Ӧduilib�ĸ�����Ϣ
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);											    // ����xml������ؿؼ�
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	                            // ����ϵͳ��Ϣ
	virtual void InitWindow();                                                                          // ���ڳ�ʼ������
	virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);	    // ���ڹرպ���

private:
	bool OnTargetSizeChanged(void* param);															    // ��Ƶ���ڴ�С�ı�ͻ����¼���������
	void OnClickProcess(TNotifyUI& msg);															    // ����¼�������
private:
	CWndUI* m_pOpenGLWnd;
	HWND m_OpenGLHWND;
};

#endif // !MAINWND_h
