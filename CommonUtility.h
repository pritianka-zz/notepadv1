// To keep things simple let us have a header file to keep common
// utility stuff. Many of the routines in this file are adapted from
// other notepad++ plugins.

#ifndef __WAKATIME_NPP_PLUGIN_UTILITIES
#define __WAKATIME_NPP_PLUGIN_UTILITIES
#include "stdafx.h"
#include "PluginInterface.h"
#include <string>

// The global plugin name. This is also the name in which the menu item
// under PlugIns will be created by Notepad++.
const TCHAR NPP_PLUGIN_NAME[] = TEXT("WakaTime");

// The WakaTime config file name. 
const TCHAR WAKATIME_CONFIG_NAME[] = TEXT(".wakatime.cfg");

// The number of functions that this plugin will support. The code is taken
// from "How to build a Notepad++ plugin in 10 mins" resource.
const int nbFunc = 1;

// The instance of Notepad++ for which the dll is loaded. This is declared
// extern here so that whoever includes this file gets this variable. But 
// the variable itself is declared in dllmain.cpp.
extern HINSTANCE currentInstance;

// Notepad++ relavent data. Both these datastructures are declared in the file
// WakaTimeNPPPlugin.cpp.
extern FuncItem funcItem[nbFunc];
extern NppData nppData;

class EditRecordTimer
{
private:
	~EditRecordTimer(){}
	static FILETIME lastUpdatedTimeStamp; 
	static const long long SPAN = 2 * 60 * 1000; // 2 Minute interval
public:
	static bool HasEnoughTimeElapsedToRecordEdit()
	{
		FILETIME thisInstant;
		GetSystemTimeAsFileTime(&thisInstant);
		// Somewhere in SO there was this comment that FILETIME is laid out in 
		// memory as a long long and reinterpreting it as long long.
		long long delta = *(reinterpret_cast<long long*>(&thisInstant)) - 
							*(reinterpret_cast<long long*>(&lastUpdatedTimeStamp));
		return (delta > SPAN);
	}

	static void UpdateTimeStampToBringToCurrent()
	{
		GetSystemTimeAsFileTime(&lastUpdatedTimeStamp);
	}
};

class ManageWakaTimeConfigFile
{
private:
	const std::wstring SECTION = L"settings";
	const std::wstring API_KEY = L"api_key";
	std::wstring m_FileName;
public:
	bool ReadWakaTimeConfigFile();
	std::wstring GetAPIKeyFromConfigFile();
	bool UpdateWakaTimeAPIKey(std::wstring key);
	void CreateWakaTimeConfigFile(std::wstring key);
};

class CommonUtility
{
private:
	static std::wstring sWakaTimeCmdPath;
	static const std::wstring pythoncmd;
public:
	static std::wstring GetCurrentNPPDocument();
	static void OnCurrentNPPDocumentSaved();
	static void OnNewNPPDocumentCreated();
	static void OnNPPDocumentModified();
};

// One instance of config file manager. 
extern ManageWakaTimeConfigFile gConfigFileManager;

#endif