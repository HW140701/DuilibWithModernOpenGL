#pragma once

#include <SDKDDKVer.h>
#include <afxwin.h>

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#include <iostream>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// duilib
#include "UIlib.h"
using namespace DuiLib;

// glad
#include <glad/glad.h>


// glfw
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>






