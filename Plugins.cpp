#include "Plugins.h"
#include <Windows.h>

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
						// loaded
					}
				} else {
					// failed to load
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}
