#include "CustomStats.h"

void CustomStats::PercentageCompleted()
{
	bool &nastyGame = *reinterpret_cast<bool *>(0x0068DD68);
	float fRatio = 0.0f;
	float adjustedTotal = nastyGame ? TotalProgressInGame : TotalProgressInGame - 1.0f;
	if (adjustedTotal > 0.0f) {
		fRatio = ProgressMade * 100.0f / adjustedTotal;
		if (fRatio > 100.0f) {
			fRatio = 100.0f;
		}
	}
	int nRatio = static_cast<int>(fRatio);
	BuildStatLine("PER_COM", &nRatio, 2, 0, 0); // Percentage completed
}

void CustomStats::Register()
{
	Stats::Register(AlwaysTrue, PercentageCompleted);
}
