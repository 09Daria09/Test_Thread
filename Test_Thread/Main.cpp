#include "Main.h"

Test* Test::ptr = NULL;

Test::Test(void)
{
	ptr = this;
}

void Test::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Thread(LPVOID lp)
{
	HWND hProgress = (HWND)lp;
	TCHAR str[100];
	int min = 3;
	int sec = 0;
	TCHAR Time_[255];
	TCHAR Min[255];
	TCHAR Sec[255];
	while (TRUE)
	{
		sec--;
		if (sec == -1){
			min--;
			sec = 59;
		}

		if (min < 11)_stprintf_s(Time_, TEXT("0%d"), min);
		else _stprintf_s(Time_, TEXT("%d"), min);

		if (sec < 11)wcscat_s(Time_, TEXT(":0"));
		else wcscat_s(Time_, TEXT(":"));

		_stprintf_s(Sec, TEXT("%d"), sec);
		wcscat_s(Time_, 255, Sec);

		SetWindowText(hProgress, Time_);
		Sleep(980);
	}
	return 0;
}

BOOL Test::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	srand(time(0));
	
	hprogress = GetDlgItem(hwnd, IDC_PROGRESS1);
	SendMessage(hprogress, PBM_SETRANGE, 0, MAKELPARAM(0, 3));
	SendMessage(hprogress, PBM_SETSTEP, 1, 0);
	SendMessage(hprogress, PBM_SETPOS, 0, 0);
	SendMessage(hprogress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 255, 0)));


	hRadioSponge = GetDlgItem(hwnd, IDC_RADIO3);
	hRadioUnicorn = GetDlgItem(hwnd, IDC_RADIO6);

	hCheckFear = GetDlgItem(hwnd, IDC_CHECK1);
	hCheckDisgust = GetDlgItem(hwnd, IDC_CHECK2);

	hEditTime = GetDlgItem(hwnd, IDC_EDIT1);

	Time = CreateThread(NULL, 0, Thread, hEditTime, 0, NULL);

	return TRUE;
}

void Test::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR str[100];
	double Result = 0;
	double res;
	if (LOWORD(id) == IDOK)
	{
		LRESULT res = SendDlgItemMessage(hwnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED){
			Result+=33.33333;
			SendMessage(hprogress, PBM_STEPIT, 0, 0);
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO6, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED){
			Result+=33.33333;
			SendMessage(hprogress, PBM_STEPIT, 0, 0);
		}
		LRESULT lResult = SendMessage(hCheckFear, BM_GETCHECK, 0, 0);
		LRESULT PResult = SendMessage(hCheckDisgust, BM_GETCHECK, 0, 0);
		if (lResult == BST_CHECKED && PResult == BST_CHECKED) {
			Result+=33.33333;
			SendMessage(hprogress, PBM_STEPIT, 0, 0);
		}
	TerminateThread(Time, 0);
	_stprintf_s(str, TEXT("Вы набрали: %.2f/100"), Result);
	MessageBox(hwnd, str, TEXT("Результат тестирования"), MB_OK | MB_ICONINFORMATION);
	
	}
	if (LOWORD(id) == IDCANCEL) {
		EndDialog(hwnd, 0);
		TerminateThread(Time, 0);
	}

	
}

BOOL CALLBACK Test::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}