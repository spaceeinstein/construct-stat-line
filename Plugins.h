#pragma once

#include <Windows.h>

class Plugin
{
public:
	HMODULE module;
	Plugin(char *path);
	~Plugin();
};

class Plugins
{
public:
	static void LoadPlugins();
};
