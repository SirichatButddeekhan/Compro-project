#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <windows.h>
// ประกาศฟังก์ชันสำหรับสร้างหน้าต่างล็อกอิน
HWND CreateLoginWindow(HINSTANCE hInstance, int nCmdShow);
// ประกาศฟังก์ชันสำหรับจัดการข้อความของหน้าต่างล็อกอิน
LRESULT CALLBACK LoginProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif