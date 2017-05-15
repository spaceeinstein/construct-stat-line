#include "StatsSystem.h"

int StatsSystem::total;
Stat *StatsSystem::line;
Stat *StatsSystem::begin;

Stat::Stat(bool(*condition)(), void(*function)())
{
	this->condition = condition;
	this->function = function;
	this->next = nullptr;
	StatsSystem::total++;
}

void StatsSystem::Init()
{
	StatsSystem::line = StatsSystem::begin = nullptr;
	StatsSystem::total = 0;
}

unsigned int StatsSystem::ConstructStatLineHack(int line)
{
	int offset = 0;
	StatsSystem::line = StatsSystem::begin;
	while (StatsSystem::line) {
		if (StatsSystem::line->condition()) {
			if (line == offset++) {
				StatsSystem::line->function();
				return 0;
			}
		}
		StatsSystem::line = StatsSystem::line->next;
	}
	return offset;
}

void __declspec(naked) StatsSystem::ConstructStatLineHackProxy()
{
	__asm
	{
		jmp ConstructStatLineHack
	}
}
