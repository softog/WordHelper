// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include "Utils.h"

#endif //PCH_H

// 任务栏重新调整位置
#define MY_TIMER_TASKBAR_REPOSITION 250
#define MY_TIMER_TASKBAR_REPOSITION_ID (WM_USER+1)

// 更新显示的单词
#define MY_TIMER_TASKBAR_UPDATE_WORD 1000
#define MY_TIMER_TASKBAR_UPDATE_WORD_ID (WM_USER+2)