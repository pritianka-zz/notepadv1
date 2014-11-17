
#ifndef __WAKATIME_NPP_PLUGIN_VIEW
#define __WAKATIME_NPP_PLUGIN_VIEW
#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "resource.h"

#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hEdit = GetDlgItem(hDlg, IDC_WAKATIME_KEY);
		SetFocus(hEdit);
		return FALSE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			// Handle cancel by sending the close windows message.
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return TRUE;
		case IDOK:
			// Write user provided Key to the config file with full trust.
			return TRUE;
		case IDC_WAKATIME_KEY:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				HWND hOk = GetDlgItem(hDlg, IDOK);
				EnableWindow(hOk, true);
				return TRUE;
			}

			return FALSE;
		}
		break;

	case WM_CLOSE:
	{
		// Close will close the dialog to enter WakaTime API key.
		DestroyWindow(hDlg);
		return TRUE;
	}
		
	case WM_DESTROY:
	{
		// Handle any processing that needs to be done before quitting.
		return TRUE;
	}
	}

	return FALSE;
}

int ShowWakaTimeAPIKeyDialog()
{
	try
	{
		HWND hSelf = ::CreateDialogParam(currentInstance,
			MAKEINTRESOURCE(IDD_WAKATIME_API_DLG), nppData._nppHandle, 
			(DLGPROC)DialogProc, (LPARAM)NULL);
		if (hSelf == NULL)
		{
			::MessageBox(NULL, TEXT("WakaTime API Key dialog could not be created!"), 
				TEXT("WakaTime Notepad++ Plugin"), MB_ICONEXCLAMATION);
			return -1;
		}

		RECT rc;
		::GetClientRect(nppData._nppHandle, &rc);
		POINT center;
		int w = rc.right - rc.left;
		int h = rc.bottom - rc.top;
		center.x = rc.left + w / 2;
		center.y = rc.top + h / 2;
		::ClientToScreen(nppData._nppHandle, &center);



		RECT dlgRect;
		::GetClientRect(hSelf, &dlgRect);
		int x = center.x - (dlgRect.right - dlgRect.left) / 2;
		int y = center.y - (dlgRect.bottom - dlgRect.top) / 2;
		::SetWindowPos(hSelf, HWND_TOP, x, y, (dlgRect.right - dlgRect.left), 
			(dlgRect.bottom - dlgRect.top), SWP_SHOWWINDOW);
		::ShowWindow(hSelf, SW_SHOW);
		return 0;
	}
	catch (...)
	{
		// Don't let the NPP runtime issue a cryptic dialog bar that our plugin 
		// has failed. Rather fail gracefully.
		::MessageBox(NULL, TEXT("WakaTime API Key dialog could not be created!"), 
			TEXT("WakaTime Notepad++ Plugin"), MB_ICONEXCLAMATION);
		return -1;
	}
}

#endif