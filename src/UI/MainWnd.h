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
	virtual LPCTSTR    GetWindowClassName() const;													    // 设置程序类名称
	virtual DuiLib::CDuiString GetSkinFile();														    // 设置皮肤文件
	virtual CDuiString GetSkinFolder();																    // 设置皮肤文件路
	virtual void Notify(TNotifyUI& msg);															    // 响应duilib的各种消息
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);											    // 根据xml创建相关控件
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	                            // 处理系统消息
	virtual void InitWindow();                                                                          // 窗口初始化函数
	virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);	    // 窗口关闭函数

private:
	bool OnTargetSizeChanged(void* param);															    // 视频窗口大小改变和绘制事件触发函数
	void OnClickProcess(TNotifyUI& msg);															    // 点击事件处理函数
private:
	CWndUI* m_pOpenGLWnd;
	HWND m_OpenGLHWND;
};

#endif // !MAINWND_h
