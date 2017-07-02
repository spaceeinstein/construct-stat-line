#pragma once

#include <Windows.h>

class Stat
{
public:
	bool(*condition)();
	void(*function)();
	Stat *next;

	Stat(bool(*)(), void(*)());
};

class StatsSystem
{
public:
	static Stat *line;
	static Stat *begin;
	static bool isPressingKey;

	static HMODULE dllModule;
	static int reloadKey;
	static int useDefaultStats;
	static int useCustomStats;

	static void Init();
	static void Reinit();
	static int ConstructStatLineHack(int line);
};
