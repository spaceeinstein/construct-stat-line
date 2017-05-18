#include "StatsSystem.h"
#include "DefaultStats.h"
#include "Plugins.h"

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

int StatsSystem::ConstructStatLineHack(int line)
{
	if (Plugins::total) {
		int offset = 0;
		Stat *current = StatsSystem::begin;
		while (current) {
			if (current->condition()) {
				if (line == offset++) {
					current->function();
					return 0;
				}
			}
			current = current->next;
		}
		return offset;
	} else {
		return DefaultStats::UseDefaultStatLine(line);
	}
}
