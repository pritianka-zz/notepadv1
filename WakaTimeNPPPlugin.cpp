// WakaTimeNPPPlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "WakaTimeNPPPlugin.h"

FuncItem funcItem[nbFunc];
NppData nppData;

extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
	switch (notifyCode->nmhdr.code)
	{
	case NPPN_SHUTDOWN:
	{
		WakaTimeNPPPlugin::commandMenuCleanUp();
	}
		break;

	default:
		return;
	}
}

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	WakaTimeNPPPlugin::commandMenuInit();
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return funcItem;
}

// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
}

// Here you can do the clean up, save the parameters (if any) for the next session
void pluginCleanUp()
{
}

// Initialization of your plugin commands
// You should fill your plugins commands here
void WakaTimeNPPPlugin::commandMenuInit()
{
	WakaTimeNPPPlugin::setCommand(0, TEXT("WakaTime API Key"), WakaTimeNPPPlugin::showWakaTimeAPIDlg, NULL, false);
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
