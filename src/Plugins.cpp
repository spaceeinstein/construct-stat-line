#include "Plugins.h"
#include <Windows.h>

Plugin *Plugins::plugins;

Plugin::Plugin(char *path)
{
	this->module = LoadLibrary(path);
	this->prev = nullptr;
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
	Plugins::plugins = nullptr;
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				char filename[MAX_PATH];
				strcpy_s(filename, "stats\\");
				strcat_s(filename, FindFileData.cFileName);
				Plugin *plugin = new Plugin(filename);
				if (plugin) {
					if (!plugin->module) {
						delete plugin;
					} else {
						plugin->prev = Plugins::plugins;
						Plugins::plugins = plugin;
					}
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}

void Plugins::UnloadPlugins()
{
	Plugin *plugin = Plugins::plugins;
	while (plugin) {
		Plugin *prev = plugin->prev;
		delete plugin;
		plugin = prev;
	}
	Plugins::plugins = nullptr;
}
