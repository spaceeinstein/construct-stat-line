#include <Windows.h>
#include "CustomStats.h"

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH) {
		CustomStats::Register();
	}
	return TRUE;
}
