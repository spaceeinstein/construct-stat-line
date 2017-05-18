#include "Plugins.h"
#include <Windows.h>

int Plugins::total;

Plugin::Plugin(char *path)
{
	this->module = LoadLibrary(path);
}

Plugin::~Plugin()
{
	FreeLibrary(this->module);
}

void Plugins::LoadPlugins()
{
	WIN32_FIND_DATA FindFileData;
	memset(&FindFileData, 0, sizeof(WIN32_FIND_DATA));
	HANDLE hFind = FindFirstFile("stats\\*.stats", &FindFileData);
	Plugins::total = 0;
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				char filename[MAX_PATH];
				strcpy_s(filename, "stats\\");
				strcat_s(filename, FindFileData.cFileName);
				Plugin *plugin = new Plugin(filename);
				if (plugin) {
					if (!plugin->module) {
						delete plugin; // failed to load
					} else {
						Plugins::total++; // loaded
					}
				} else {
					// failed to load
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}
