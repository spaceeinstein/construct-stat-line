#pragma once

#include <Windows.h>

class Plugin
{
public:
	HMODULE module;
	Plugin *prev;
	Plugin(char *path);
	~Plugin();
};

class Plugins
{
public:
	static Plugin *plugins;

	static void LoadPlugins();
	static void UnloadPlugins();
};
