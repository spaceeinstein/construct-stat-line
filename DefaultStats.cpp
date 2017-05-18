#include "DefaultStats.h"

#define METRES_TO_MILES 0.0006213712f
#define METRES_TO_FEET 3.28084f

bool &nastyGame = *reinterpret_cast<bool *>(0x0068DD68);
bool &isDaysPassedInitialised = *reinterpret_cast<bool *>(0x0070499C);
int &storedDaysPassed = *reinterpret_cast<int *>(0x00704998);
bool &isSpendingInitialised = *reinterpret_cast<bool *>(0x007049A4);
float &storedSpending = *reinterpret_cast<float *>(0x007049A0);
unsigned char &PrefsLanguage = *reinterpret_cast<unsigned char *>(0x00869680);
int &totalPackages = *reinterpret_cast<int *>(0x0094ADD4);
int &foundPackages = *reinterpret_cast<int *>(0x0094ADD0);
unsigned int &nTimeInMilliseconds = *reinterpret_cast<unsigned int *>(0x00974B2C);

enum eStatType
{
	STAT_TYPE_INT,
	STAT_TYPE_FLOAT,
	STAT_TYPE_PERCENT,
	STAT_TYPE_CASH,
	STAT_TYPE_DEGREE
};

int DefaultStats::UseDefaultStatLine(int line)
{
	int offset = 0;
	// fixes game's odd possibility of division by 0
	if (line == offset++) {
		float fRatio = 0.0f;
		float adjustedTotal = nastyGame ? TotalProgressInGame : TotalProgressInGame - 1.0f;
		if (adjustedTotal > 0.0f) {
			fRatio = ProgressMade * 100.0f / adjustedTotal;
			if (fRatio > 100.0f) {
				fRatio = 100.0f;
			}
		}
		int nRatio = static_cast<int>(fRatio);
		BuildStatLine("PER_COM", &nRatio, STAT_TYPE_PERCENT, 0, 0); // Percentage completed
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("NMISON", &MissionsGiven, STAT_TYPE_INT, 0, 0); // Mission attempts
		return 0;
	}
	if (line == offset++) {
		unsigned int hours = static_cast<unsigned int>(nTimeInMilliseconds / 3.6e6f);
		unsigned int minutes = (nTimeInMilliseconds / 60000) % 60;
		BuildStatLine("ST_TIME", &hours, STAT_TYPE_INT, &minutes, 1); // Playing Time
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("DAYSPS", &DaysPassed, STAT_TYPE_INT, 0, 0); // Days passed in game
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("NUMSHV", &SafeHouseVisits, STAT_TYPE_INT, 0, 0); // Safehouse visits
		return 0;
	}
	if (nastyGame && line == offset++) {
		BuildStatLine("FEST_RP", &NumberKillFrenziesPassed, STAT_TYPE_INT, &TotalNumberKillFrenzies, 0); // Rampages passed
		return 0;
	}
	if (line == offset++) {
		int ratio = 0;
		if (totalPackages) {
			ratio = static_cast<int>(foundPackages * 100.0f / totalPackages);
		}
		BuildStatLine("PERPIC", &ratio, STAT_TYPE_INT, &totalPackages, 0); // Hidden Packages found
		return 0;
	}
	if (nastyGame) {
		if (line == offset++) {
			BuildStatLine("PE_WAST", &PeopleKilledByPlayer, STAT_TYPE_INT, 0, 0); // People you've wasted
			return 0;
		}
		if (line == offset++) {
			BuildStatLine("PE_WSOT", &PeopleKilledByOthers, STAT_TYPE_INT, 0, 0); // People wasted by others
			return 0;
		}
	}
	if (line == offset++) {
		BuildStatLine("CAR_EXP", &CarsExploded, STAT_TYPE_INT, 0, 0); // Road Vehicles destroyed
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("BOA_EXP", &BoatsExploded, STAT_TYPE_INT, 0, 0); // Boats destroyed
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("HEL_DST", &HelisDestroyed, STAT_TYPE_INT, 0, 0); // Planes & Helicopters destroyed
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("TYREPOP", &TyresPopped, STAT_TYPE_INT, 0, 0); // Tires popped with gunfire
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_STAR", &WantedStarsAttained, STAT_TYPE_INT, 0, 0); // Total number of wanted stars attained
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_STGN", &WantedStarsEvaded, STAT_TYPE_INT, 0, 0); // Total number of wanted stars evaded
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("TM_BUST", &TimesArrested, STAT_TYPE_INT, 0, 0); // Times busted
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("TM_DED", &TimesDied, STAT_TYPE_INT, 0, 0); // Hospital visits
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_HEAD", &HeadsPopped, STAT_TYPE_INT, 0, 0); // Number of headshots
		return 0;
	}
	if (line == offset++) {
		if (!isDaysPassedInitialised) {
			storedDaysPassed |= 0xFFFFFFFF;
			isDaysPassedInitialised = true;
		}
		if (!isSpendingInitialised) {
			storedSpending = 0.0f;
			isSpendingInitialised = true;
		}
		if (storedDaysPassed != DaysPassed) {
			storedSpending = static_cast<float>(((nTimeInMilliseconds & 0xFF) + 0x50) * 255.44f);
			storedDaysPassed = DaysPassed;
		}
		BuildStatLine("DAYPLC", &storedSpending, STAT_TYPE_CASH, 0, 0); // Daily police spending
		return 0;
	}
	int highestId = 0;
	int highestCount = 0;
	for (int i = 7; i < 16; i++) {
		if (PedsKilledOfThisType[i] > highestCount) {
			highestCount = PedsKilledOfThisType[i];
			highestId = i;
		}
	}
	if (highestId > 0) {
		if (line == offset++) {
			BuildStatLine("ST_GANG", 0, 0, 0, 0); // Least favorite gang
			return 0;
		}
		if (line == offset++) {
			switch (highestId - 7) {
			case 0:
				AddTextLine("ST_GNG1");
				return 0;
			case 1:
				AddTextLine("ST_GNG2");
				return 0;
			case 2:
				AddTextLine("ST_GNG3");
				return 0;
			case 3:
				AddTextLine("ST_GNG4");
				return 0;
			case 4:
				AddTextLine("ST_GNG5");
				return 0;
			case 5:
				AddTextLine("ST_GNG6");
				return 0;
			case 6:
				AddTextLine("ST_GNG7");
				return 0;
			case 7:
				AddTextLine("ST_GNG8");
				return 0;
			}
		}
	}
	if (line == offset++) {
		int total =
			PedsKilledOfThisType[7] +
			PedsKilledOfThisType[8] +
			PedsKilledOfThisType[9] +
			PedsKilledOfThisType[10] +
			PedsKilledOfThisType[11] +
			PedsKilledOfThisType[12] +
			PedsKilledOfThisType[13] +
			PedsKilledOfThisType[14] +
			PedsKilledOfThisType[15];
		BuildStatLine("GNG_WST", &total, STAT_TYPE_INT, 0, 0); // Gang members wasted
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("DED_CRI", &PedsKilledOfThisType[18], STAT_TYPE_INT, 0, 0); // Criminals wasted
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("KGS_EXP", &KgsOfExplosivesUsed, STAT_TYPE_INT, 0, 0); // Kgs of explosives used
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("BUL_FIR", &RoundsFiredByPlayer, STAT_TYPE_INT, 0, 0); // Bullets fired
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("BUL_HIT", &BulletsThatHit, STAT_TYPE_INT, 0, 0); // Bullets that hit
		return 0;
	}
	if (line == offset++) {
		int ratio = 0;
		if (RoundsFiredByPlayer) {
			ratio = static_cast<int>(BulletsThatHit * 100.0f / RoundsFiredByPlayer);
		}
		BuildStatLine("ACCURA", &ratio, STAT_TYPE_PERCENT, 0, 0); // Accuracy
		return 0;
	}
	// fixes inaccurate unit conversions
	if (PrefsLanguage == 0) {
		if (line == offset++) {
			float distance = DistanceTravelledOnFoot * METRES_TO_MILES;
			BuildStatLine("FEST_DF", &distance, STAT_TYPE_FLOAT, 0, 0); // Dist. traveled on foot (miles)
			return 0;
		}
		if (line == offset++) {
			float distance = DistanceTravelledByCar * METRES_TO_MILES;
			BuildStatLine("FEST_DC", &distance, STAT_TYPE_FLOAT, 0, 0); // Dist. traveled by car (miles)
			return 0;
		}
		if (line == offset++) {
			float distance = DistanceTravelledByBike * METRES_TO_MILES;
			BuildStatLine("DISTBIK", &distance, STAT_TYPE_FLOAT, 0, 0); // Dist. traveled by bike (miles)
			return 0;
		}
		if (line == offset++) {
			float distance = DistanceTravelledByBoat * METRES_TO_MILES;
			BuildStatLine("DISTBOA", &distance, STAT_TYPE_FLOAT, 0, 0); // Dist. traveled by boat (miles)
			return 0;
		}
		if (line == offset++) {
			float distance = DistanceTravelledByGolfCart * METRES_TO_MILES;
			BuildStatLine("DISTGOL", &distance, STAT_TYPE_FLOAT, 0, 0); // Dist. traveled by golf cart (miles)
			return 0;
		}
		if (line == offset++) {
			float distance = DistanceTravelledByHelicopter * METRES_TO_MILES;
			BuildStatLine("DISTHEL", &distance, STAT_TYPE_FLOAT, 0, 0); // Dist. traveled by helicopter (miles)
			return 0;
		}
		// fixes distance by plane omission
		if (line == offset++) {
			float distance = (
				DistanceTravelledOnFoot +
				DistanceTravelledByCar +
				DistanceTravelledByBoat +
				DistanceTravelledByGolfCart +
				DistanceTravelledByBike +
				DistanceTravelledByHelicopter +
				DistanceTravelledByPlane) * METRES_TO_MILES;
			BuildStatLine("TOT_DIS", &distance, STAT_TYPE_FLOAT, 0, 0); // Total distance traveled (miles)
			return 0;
		}
		// fixes distance in feet omission
		if (line == offset++) {
			float distance = MaximumJumpDistance * METRES_TO_FEET;
			BuildStatLine("MXCARD", &distance, STAT_TYPE_FLOAT, 0, 0); // Max. INSANE Jump dist. (ft)
			return 0;
		}
		// fixes distance in feet omission
		if (line == offset++) {
			float distance = MaximumJumpHeight * METRES_TO_FEET;
			BuildStatLine("MXCARJ", &distance, STAT_TYPE_FLOAT, 0, 0); // Max. INSANE Jump height (ft)
			return 0;
		}
	} else {
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(DistanceTravelledOnFoot));
			BuildStatLine("FESTDFM", &distance, STAT_TYPE_FLOAT, 0, 0); // Distance traveled on foot (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(DistanceTravelledByCar));
			BuildStatLine("FESTDCM", &distance, STAT_TYPE_FLOAT, 0, 0); // Distance traveled by car (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(DistanceTravelledByBike));
			BuildStatLine("DISTBIM", &distance, STAT_TYPE_FLOAT, 0, 0); // Distance traveled by bike (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(DistanceTravelledByBoat));
			BuildStatLine("DISTBOM", &distance, STAT_TYPE_FLOAT, 0, 0); // Distance traveled by boat (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(DistanceTravelledByGolfCart));
			BuildStatLine("DISTGOM", &distance, STAT_TYPE_FLOAT, 0, 0); // Distance traveled by golf cart (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(DistanceTravelledByHelicopter));
			BuildStatLine("DISTHEM", &distance, STAT_TYPE_FLOAT, 0, 0); // Distance traveled by helicopter (m)
			return 0;
		}
		// fixes distance by plane omission
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(
				DistanceTravelledOnFoot +
				DistanceTravelledByCar +
				DistanceTravelledByBoat +
				DistanceTravelledByGolfCart +
				DistanceTravelledByBike +
				DistanceTravelledByHelicopter +
				DistanceTravelledByPlane));
			BuildStatLine("TOTDISM", &distance, STAT_TYPE_FLOAT, 0, 0); // Total distance traveled (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(MaximumJumpDistance));
			BuildStatLine("MXCARDM", &distance, STAT_TYPE_FLOAT, 0, 0); // Max. INSANE Jump dist. (m)
			return 0;
		}
		if (line == offset++) {
			float distance = static_cast<float>(static_cast<int>(MaximumJumpHeight));
			BuildStatLine("MXCARJM", &distance, STAT_TYPE_FLOAT, 0, 0); // Max. INSANE Jump height (m)
			return 0;
		}
	}
	if (line == offset++) {
		BuildStatLine("MXFLIP", &MaximumJumpFlips, STAT_TYPE_INT, 0, 0); // Max. INSANE Jump flips
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("NOUNIF", &NumberOfUniqueJumpsFound, STAT_TYPE_INT, &TotalNumberOfUniqueJumps, 0); // Unique Jumps completed
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("MXJUMP", &MaximumJumpSpins, STAT_TYPE_DEGREE, 0, 0); // Max. INSANE Jump rotation
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("BSTSTU", 0, 0, 0, 0); // Best INSANE stunt so far
		return 0;
	}
	if (line == offset++) {
		switch (BestStuntJump - 1) {
		case 0:
			AddTextLine("INSTUN"); // Insane stunt
			return 0;
		case 1:
			AddTextLine("PRINST"); // Perfect insane stunt
			return 0;
		case 2:
			AddTextLine("DBINST"); // Double insane stunt
			return 0;
		case 3:
			AddTextLine("DBPINS"); // Perfect double insane stunt
			return 0;
		case 4:
			AddTextLine("TRINST"); // Triple insane stunt
			return 0;
		case 5:
			AddTextLine("PRTRST"); // Perfect triple insane stunt
			return 0;
		case 6:
			AddTextLine("QUINST"); // Quadruple insane stunt
			return 0;
		case 7:
			AddTextLine("PQUINS"); // Perfect quadruple insane stunt
			return 0;
		default:
			AddTextLine("NOSTUC"); // No INSANE stunts completed
			return 0;
		}
	}
	return offset;
}
