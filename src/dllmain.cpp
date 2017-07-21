#include <cstdint>
#include <Windows.h>
#include "StatsSystem.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH) {
		uint32_t jumpAddress = 0x004CB085;
		if (*reinterpret_cast<uint32_t *>(jumpAddress) == 0x05D9EED9) {
			StatsSystem::dllModule = hModule;
			DWORD flOldProtect;
			VirtualProtect(reinterpret_cast<void *>(jumpAddress), 5, PAGE_EXECUTE_READWRITE, &flOldProtect);
			*reinterpret_cast<uint8_t *>(jumpAddress) = 0xE9;
			*reinterpret_cast<uint32_t *>(jumpAddress + 1) = reinterpret_cast<uint32_t>(&StatsSystem::ConstructStatLineHack) - jumpAddress - 5;
			VirtualProtect(reinterpret_cast<void *>(jumpAddress), 5, flOldProtect, &flOldProtect);
			StatsSystem::Init();
		}
	}
	return TRUE;
}
