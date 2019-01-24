#include "header.h"
#include <tlhelp32.h>
#include <map>

typedef std::map<DWORD, char*> TMAP;

int GetTaskList(TMAP &tmap)
{
	HANDLE snapshot;
	PROCESSENTRY32 pe;

	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(snapshot == INVALID_HANDLE_VALUE) return(1);
	pe.dwSize = sizeof(pe);
	if(!Process32First(snapshot, &pe)) {
		CloseHandle(snapshot);
		return(1);
	}
	do {
		char *name = _strdup(pe.szExeFile);
		// drop ".exe" to be compatible with previous versions
		int len = lstrlen(name);
		if(len > 4 && !lstrcmpi(name+len-4, ".exe")) name[len-4] = '\0';
		tmap[pe.th32ProcessID] = name;
	} while (Process32Next(snapshot, &pe));
	CloseHandle(snapshot);
	return(0);
}

char *GetImageName(DWORD pid)
{
	static int init;
	static TMAP tmap;
	static char Unknown[] = "Unknown";

	if(!init++) {
		if(GetTaskList(tmap)) return NULL;
		// build list of tasks
	}

	TMAP::const_iterator t = tmap.find(pid);
	if(t != tmap.end()) return t->second;
	return Unknown;
}
