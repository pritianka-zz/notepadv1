// To keep things simple let us have a header file to keep common
// utility stuff. Many of the routines in this file are adapted from
// other notepad++ plugins.

#ifndef __WAKATIME_NPP_PLUGIN_UTILITIES
#define __WAKATIME_NPP_PLUGIN_UTILITIES
#include "stdafx.h"
#include "PluginInterface.h"

// The global plugin name. This is also the name in which the menu item
// under PlugIns will be created by Notepad++.
const TCHAR NPP_PLUGIN_NAME[] = TEXT("WakaTime");

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

#endif