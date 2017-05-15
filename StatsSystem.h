#pragma once

class Stat
{
public:
	bool(*condition)();
	void(*function)();
	Stat *next;

	Stat(bool(*)(), void(*)());
};

class StatsSystem {
public:
	static Stat *line;
	static Stat *begin;

	static int total;

	static void Init();
	static unsigned int ConstructStatLineHack(int line);
	static void ConstructStatLineHackProxy();
};
