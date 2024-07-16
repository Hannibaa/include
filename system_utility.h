#pragma once

// #ifdef	RUNNING_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//#include <Shlwapi.h>   // there problem of linker add lib 
//#include <PathCch.h>   // same thing
#include <string>
#include <vector>
#include <sstream>

/*
          SYSTEM FUNCTION  
		  GET MACHINE ATTRIBUTE AND CARACTERISTICS
		  GET CPU AND GPU DATA 
		  GET OPERATING SYSTEM VERSION
		  GET CONNECTION 
		  GET SERVER CLIENT AND ADMIN.

*/


inline std::wstring  GetWorkingDirectory() {
	HMODULE hModule = GetModuleHandle(nullptr);

	if (!hModule) { return L""; }

	wchar_t path[256]{};
	GetModuleFileName(hModule, path, sizeof(path));
	std::wstring::size_type pos = std::wstring(path).find_last_of(L"\\/");
	//PathRemoveFileSpec(path);
	//PathCchRemoveFileSpec(path, sizeof(path));
	//std::strcat(path, "");
	return std::wstring(path).substr(0,pos);
}

std::vector<std::wstring> GetDirectoryNamesFromPath(const std::wstring& path) {

	std::vector<std::wstring> vDirNames;
	std::wstring::size_type posEnd = path.size()-1, posBeg{};

	while (true) {
		posBeg = path.find_last_of(L"\\/", posEnd);
		if (posBeg == std::wstring::npos) break;
		vDirNames.push_back(path.substr(posBeg+1, posEnd - posBeg ));
		posEnd = posBeg - 1;
	}
	   
	return vDirNames;
}

inline std::vector<std::wstring> GetFileList(
	const std::wstring& l_directory,
	const std::wstring& l_search = L"*.*")
{
	std::vector<std::wstring> files;

	if (l_search.empty()) { return files; }

	std::wstring path = l_directory + l_search;
	WIN32_FIND_DATA data;
	HANDLE found = FindFirstFile(path.c_str(), &data);

	if (found == INVALID_HANDLE_VALUE) { return files; }
	do {
		if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			files.emplace_back(data.cFileName);
		}
	} while (FindNextFile(found, &data));

	FindClose(found);
	return files;
}

inline void ReadQuotedString(std::stringstream& l_stream, std::string& l_string)
{
	l_stream >> l_string;
	if (l_string.at(0) == '"') {
		while (l_string.at(l_string.length() - 1) != '"' || !l_stream.eof())
		{
			std::string str;
			l_stream >> str;
			l_string.append(" " + str);
		}
	}
	l_string.erase(std::remove(l_string.begin(), l_string.end(), '"'), l_string.end());
}

template<typename T>
inline T Interpolate(float tBegin, float tEnd, const T& begin_val, const T& end_val, float tX)
{
	return static_cast<T>((
		((end_val - begin_val) / (tEnd - tBegin)) * (tX - tBegin)) + begin_val);
}

