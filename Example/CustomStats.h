#pragma once

#include "Stats.h"

class CustomStats : public Stats
{
private:
	static void PercentageCompleted();
	static bool InsaneStuntCondition();
	static void InsaneStunt();
public:
	static void Register();
};
