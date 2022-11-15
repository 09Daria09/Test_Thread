#pragma once
#include "header.h"

class Test
{
public:
	Test(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Test* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hprogress, hRadioSponge, hRadioUnicorn, hCheckFear, hCheckDisgust, hEditTime;
	HANDLE Time;
};
