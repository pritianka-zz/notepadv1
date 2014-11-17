// This file contains the core of WakaTime's plugin for Notepad++.

#ifndef __WAKATIME_NPP_PLUGIN_HEADER
#define __WAKATIME_NPP_PLUGIN_HEADER

// The absolute must routines a plugin should support is defined here:
#include "PluginInterface.h"

// The common utility. Should get included almost everwhere.
#include "CommonUtility.h"

extern "C" class WakaTimeNPPPlugin
{
public:
	// Initialization of your plugin data
	// It will be called while plugin loading
	static void pluginInit(HANDLE hModule);

	//
	// Cleaning of your plugin
	// It will be called while plugin unloading
	//
	static void pluginCleanUp();

	//
	//Initialization of your plugin commands
	//
	static void commandMenuInit();

	//
	//Clean up your plugin commands allocation (if any)
	//
	static void commandMenuCleanUp();

	//
	// Function which sets your command 
	//
	static bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);


	//
	// Your plugin command functions
	//
	static void showWakaTimeAPIDlg();

};

#endif