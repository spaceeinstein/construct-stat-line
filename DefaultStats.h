#pragma once

#include "Stats.h"

class DefaultStats : public Stats
{
public:
	static int metricOnly;
	static int totalStoresKnockedOff;
	static int totalMovieStunts;
	static int totalAssassinations;

	static int UseDefaultStatLine(int line);
};
