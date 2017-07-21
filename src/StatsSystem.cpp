#include "StatsSystem.h"
#include <Windows.h>
#include "DefaultStats.h"
#include "Plugins.h"

Stat *StatsSystem::line;
Stat *StatsSystem::begin;
bool StatsSystem::isPressingKey;

HMODULE StatsSystem::dllModule;
int StatsSystem::reloadKey;
int StatsSystem::useDefaultStats;
int StatsSystem::useCustomStats;

Stat::Stat(bool(*condition)(), void(*function)())
{
	this->condition = condition;
	this->function = function;
	this->next = nullptr;
}

void StatsSystem::Init()
{
	char moduleIniPath[MAX_PATH];

	GetModuleFileName(StatsSystem::dllModule, moduleIniPath, MAX_PATH);
	size_t nLen = strlen(moduleIniPath);
	moduleIniPath[nLen - 1] = L'i';
	moduleIniPath[nLen - 2] = L'n';
	moduleIniPath[nLen - 3] = L'i';

	StatsSystem::reloadKey = GetPrivateProfileInt("Main", "ReloadKey", 0x52, moduleIniPath); // R key
	StatsSystem::useDefaultStats = GetPrivateProfileInt("Main", "UseDefaultStats", 1, moduleIniPath);
	StatsSystem::useCustomStats = GetPrivateProfileInt("Main", "UseCustomStats", 1, moduleIniPath);

	DefaultStats::metricOnly = GetPrivateProfileInt("DefaultStats", "MetricOnly", 0, moduleIniPath);
	DefaultStats::totalStoresKnockedOff = GetPrivateProfileInt("DefaultStats", "TotalStoresKnockedOff", 15, moduleIniPath);
	DefaultStats::totalMovieStunts = GetPrivateProfileInt("DefaultStats", "TotalMovieStunts", 0, moduleIniPath);
	DefaultStats::totalAssassinations = GetPrivateProfileInt("DefaultStats", "TotalAssassinations", 5, moduleIniPath);

	StatsSystem::line = StatsSystem::begin = nullptr;
	StatsSystem::isPressingKey = false;

	Plugins::LoadPlugins();
}

void StatsSystem::Reinit()
{
	Stat *current = StatsSystem::begin;
	while (current) {
		Stat *next = current->next;
		delete current;
		current = next;
	}
	Plugins::UnloadPlugins();
	StatsSystem::Init();
}

int StatsSystem::ConstructStatLineHack(int line)
{
	int offset = 0;
	if (GetKeyState(StatsSystem::reloadKey) & 0x8000) {
		if (!StatsSystem::isPressingKey) {
			StatsSystem::Reinit();
			StatsSystem::isPressingKey = true;
		}
	} else {
		StatsSystem::isPressingKey = false;
	}
	if (StatsSystem::useDefaultStats) {
		offset = DefaultStats::UseDefaultStatLine(line);
	}
	if (Plugins::plugins && StatsSystem::useCustomStats && (StatsSystem::useDefaultStats && offset > 0 || !StatsSystem::useDefaultStats)) {
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
	}
	return offset;
}
