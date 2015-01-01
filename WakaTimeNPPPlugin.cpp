// WakaTimeNPPPlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "WakaTimeNPPPlugin.h"
#define _CRT_SECURE_NO_WARNINGS

FuncItem funcItem[nbFunc];
NppData nppData;


extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
	if (nppData._nppHandle != notifyCode->nmhdr.hwndFrom)
	{
		// These are the editor modificaitons. Check to see if we need to
		// tell WakaTime backend about this event.
		switch (notifyCode->nmhdr.code)
		{
		case SCN_MODIFIED:
		case SCN_CHARADDED:
		case SCN_UPDATEUI:
		{
			if (EditRecordTimer::HasEnoughTimeElapsedToRecordEdit())
			{
				CommonUtility::OnNPPDocumentModified();
				EditRecordTimer::UpdateTimeStampToBringToCurrent();
			}
		}
		default:
			return;
		}
		return;
	}
	switch (notifyCode->nmhdr.code)
	{
	case NPPN_SHUTDOWN:
	{
		CommonUtility::OnCurrentNPPDocumentSaved();
		WakaTimeNPPPlugin::commandMenuCleanUp();
		break;
	}
	case NPPN_FILEBEFORECLOSE:
	case NPPN_FILEBEFORESAVE:
	{
		CommonUtility::OnCurrentNPPDocumentSaved();
		break;
	}
	case NPPN_BUFFERACTIVATED:
	{
		CommonUtility::OnNewNPPDocumentCreated();
		break;
	}
	case NPPN_DOCORDERCHANGED:
	case NPPN_READONLYCHANGED:
	{
		CommonUtility::OnNPPDocumentModified();
		break;
	}
	default:
	{
		return;
	}
	}
}

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	WakaTimeNPPPlugin::commandMenuInit();
	WakaTimeNPPPlugin::pluginInit(nppData._nppHandle);
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return funcItem;
}

size_t WriteDownloadedZip(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
	return fwrite(ptr, size, nmemb, stream);
}

#include <curl/curl.h>
// Initialize your plugin data here
// It will be called while plugin loading   
void WakaTimeNPPPlugin::pluginInit(HANDLE hModule)
{
	/*
	MessageBox(NULL, CommonUtility::IsPythonAvailableInPath() ? L"Python found" : L"Python not found",
		L"Message", MB_OK);
	*/
	if (!CommonUtility::IsWakaTimeModuleAvailable())
	{
		CURL *curl = curl_easy_init();
		if (NULL == curl)
			return;

		std::wstring configPath = CommonUtility::GetNPPConfigDirectory() + L"\\wakatime";
		// May fail if the directory already exists. Just what we want.
		CreateDirectory(configPath.c_str(), NULL);
		std::wstring wakatimeZipFile = configPath + L"\\master.zip";

		FILE* fp = _wfopen(wakatimeZipFile.c_str(), L"wb");

		if (NULL == fp)
			return;

		curl_easy_setopt(curl, CURLOPT_URL, "https://github.com/wakatime//wakatime//archive//master.zip");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDownloadedZip);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		CURLcode res = curl_easy_perform(curl);
		if (CURLE_OK == res)
		{
			// Unzip the file for use.
		}

		fclose(fp);
		curl_easy_cleanup(curl);
	}
}

// Here you can do the clean up, save the parameters (if any) for the next session
void WakaTimeNPPPlugin::pluginCleanUp()
{
}

// Initialization of your plugin commands
// You should fill your plugins commands here
void WakaTimeNPPPlugin::commandMenuInit()
{
	WakaTimeNPPPlugin::setCommand(0, TEXT("WakaTime API Key"), WakaTimeNPPPlugin::showWakaTimeAPIDlg, NULL, false);
	WakaTimeNPPPlugin::setCommand(1, TEXT("About"), WakaTimeNPPPlugin::showWakaTimeAbtDlg, NULL, false);
}

// Here you can do the clean up (especially for the shortcut)
void WakaTimeNPPPlugin::commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


// This function help you to initialize your plugin commands
bool WakaTimeNPPPlugin::setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit)
{
	if (index >= nbFunc)
		return false;

	if (!pFunc)
		return false;

	lstrcpy(funcItem[index]._itemName, cmdName);
	funcItem[index]._pFunc = pFunc;
	funcItem[index]._init2Check = check0nInit;
	funcItem[index]._pShKey = sk;

	return true;
}

#include "View.h"
void WakaTimeNPPPlugin::showWakaTimeAPIDlg()
{
	ShowWakaTimeAPIKeyDialog();
}

void WakaTimeNPPPlugin::showWakaTimeAbtDlg()
{
	ShowWakaTimeAbtDialog();
}