#pragma once

#include "Stats.h"

class CustomStats : public Stats
{
private:
	static void PercentageCompleted();
public:
	static void Register();
};
