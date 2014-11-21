#include "stdafx.h"
#include "CommonUtility.h"
#include "INIReader.h"
#include <Knownfolders.h>
#include <Shlobj.h>
#include <Pathcch.h>

// Mandatory initialization of static class variable outside the header file.
static FILETIME local;
FILETIME EditRecordTimer::lastUpdatedTimeStamp = (GetSystemTimeAsFileTime(&local), local);
ManageWakaTimeConfigFile gConfigFileManager;

bool ManageWakaTimeConfigFile::ReadWakaTimeConfigFile()
{
	// Read the wakatime.cfg file under users home directory if it exists.
	WCHAR* path;
	bool status = false;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Profile, SHGFP_TYPE_CURRENT, 0, &path)))
	{
		WCHAR fullPath[MAX_PATH];
		if (SUCCEEDED(PathCchCombine(fullPath, MAX_PATH, path, WAKATIME_CONFIG_NAME)))
		{
			m_FileName = fullPath;
			status = true;
		}

		CoTaskMemFree(path);
	}

	return status;
}

std::wstring ManageWakaTimeConfigFile::GetAPIKeyFromConfigFile()
{
	if (m_FileName.empty())
		return L"";
	INIReader reader(m_FileName);
	return reader.GetKeyValuePairsUnderASection(SECTION)[API_KEY];
}

bool ManageWakaTimeConfigFile::UpdateWakaTimeAPIKey(std::wstring key)
{
	if (m_FileName.empty())
		return false;
	INIReader reader(m_FileName);
	reader.ChangeValue(SECTION, API_KEY, key);
	reader.WriteIniFile(m_FileName);
	return true;
}

void ManageWakaTimeConfigFile::CreateWakaTimeConfigFile(std::wstring key)
{
	if (m_FileName.empty())
		return;
	INIReader reader(m_FileName);
	reader.CreateSectionAndAddKeyValue(SECTION, API_KEY, key);
	reader.WriteIniFile(m_FileName);
}