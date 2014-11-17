// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "CommonUtility.h"

HINSTANCE currentInstance;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		currentInstance = (HINSTANCE)hModule;
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}


extern "C" __declspec(dllexport) BOOL isUnicode()
{
#ifdef UNICODE
	return TRUE;
#else
	return FALSE;
#endif
}
