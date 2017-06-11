#include "DefaultStats.h"

#define METRES_TO_MILES 0.0006213712f
#define METRES_TO_FEET 3.28084f

static float *(__thiscall *GetListenTimeArray)(void *) = (float *(__thiscall *)(void *))0x005F96C0;
static bool(__thiscall *IsMP3RadioChannelAvailable)(void *) = (bool(__thiscall *)(void *))0x005F9BB0;
static bool &nastyGame = *reinterpret_cast<bool *>(0x0068DD68);
static bool &isDaysPassedInitialised = *reinterpret_cast<bool *>(0x0070499C);
static int &storedDaysPassed = *reinterpret_cast<int *>(0x00704998);
static bool &isSpendingInitialised = *reinterpret_cast<bool *>(0x007049A4);
static int &storedSpending = *reinterpret_cast<int *>(0x007049A0);
static unsigned char &PrefsLanguage = *reinterpret_cast<unsigned char *>(0x00869680);
static int &foundPackages = *reinterpret_cast<int *>(0x0094ADD0);
static int &totalPackages = *reinterpret_cast<int *>(0x0094ADD4);
static unsigned int &nTimeInMilliseconds = *reinterpret_cast<unsigned int *>(0x00974B2C);
static unsigned char &PlayerInFocus = *reinterpret_cast<unsigned char *>(0x00A10AFB);
static void *DMAudio = reinterpret_cast<void *>(0x00A10B8A);

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
	// fixes odd possibility of division by 0
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
	// fixes ratio using constant total of 100
	if (line == offset++) {
		int found = *(int *)(PlayerInFocus * 0x170 + (unsigned int)&foundPackages);
		int total = *(int *)(PlayerInFocus * 0x170 + (unsigned int)&totalPackages);
		BuildStatLine("PERPIC", &found, STAT_TYPE_INT, &total, 0); // Hidden Packages found
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
		float spending;
		if (!isDaysPassedInitialised) {
			storedDaysPassed |= 0xFFFFFFFF;
			isDaysPassedInitialised = true;
		}
		if (!isSpendingInitialised) {
			storedSpending = 0;
			isSpendingInitialised = true;
		}
		if (storedDaysPassed != DaysPassed) {
			storedSpending = static_cast<int>(((nTimeInMilliseconds & 0xFF) + 0x50) * 255.44f);
			storedDaysPassed = DaysPassed;
		}
		spending = static_cast<float>(storedSpending);
		BuildStatLine("DAYPLC", &spending, STAT_TYPE_CASH, 0, 0); // Daily police spending
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
		// fixes distances by bike and plane omission
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
	if (line == offset++) {
		BuildStatLine("ST_WHEE", &LongestWheelie, STAT_TYPE_INT, 0, 0); // Longest Wheelie time (secs)
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_WHED", &LongestWheelieDist, STAT_TYPE_FLOAT, 0, 0); // Longest Wheelie distance (m)
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_STOP", &LongestStoppie, STAT_TYPE_INT, 0, 0); // Longest Stoppie time (secs)
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_STOD", &LongestStoppieDist, STAT_TYPE_FLOAT, 0, 0); // Longest Stoppie distance (m)
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_2WHE", &Longest2Wheel, STAT_TYPE_INT, 0, 0); // Longest 2 wheels time (secs)
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_2WHD", &Longest2WheelDist, STAT_TYPE_FLOAT, 0, 0); // Longest 2 wheels distance (m)
		return 0;
	}
	if (LoanSharks > 0.0 && line == offset++) {
		int loan = static_cast<int>(LoanSharks);
		BuildStatLine("ST_LOAN", &loan, STAT_TYPE_INT, 0, 0); // Visits From Loan Sharks
	}
	if (line == offset++) {
		BuildStatLine("FEST_CC", &CriminalsCaught, STAT_TYPE_INT, 0, 0); // Criminals killed on Vigilante Mission
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("FEST_HV", &HighestLevelVigilanteMission, STAT_TYPE_INT, 0, 0); // Highest Vigilante Mission level
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("PASDRO", &PassengersDroppedOffWithTaxi, STAT_TYPE_INT, 0, 0); // Passengers dropped off
		return 0;
	}
	if (line == offset++) {
		float money = static_cast<float>(MoneyMadeWithTaxi);
		BuildStatLine("MONTAX", &money, STAT_TYPE_CASH, 0, 0); // Cash made in taxi
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("FEST_LS", &LivesSavedWithAmbulance, STAT_TYPE_INT, 0, 0); // People saved in an Ambulance
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("FEST_HA", &HighestLevelAmbulanceMission, STAT_TYPE_INT, 0, 0); // Highest Paramedic Mission level
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("FEST_FE", &FiresExtinguished, STAT_TYPE_INT, 0, 0); // Total fires extinguished
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("FIRELVL", &HighestLevelFireMission, STAT_TYPE_INT, 0, 0); // Fire Truck Mission level
		return 0;
	}
	if (line == offset++) {
		int stores = static_cast<int>(StoresKnockedOff);
		int total = 15;
		BuildStatLine("ST_STOR", &stores, STAT_TYPE_INT, &total, 0); // Stores Knocked Off
		return 0;
	}
	if (MovieStunts > 0.0 && line == offset++) {
		int stunts = static_cast<int>(MovieStunts);
		int total = 0;
		BuildStatLine("ST_MOVI", &stunts, STAT_TYPE_INT, &total, 0); // Movie Stunts
		return 0;
	}
	if (line == offset++) {
		int assassinations = static_cast<int>(Assassinations);
		int total = 5;
		BuildStatLine("ST_ASSI", &assassinations, STAT_TYPE_INT, &total, 0); // Assassination Contracts Completed
		return 0;
	}
	if (PhotosTaken > 0 && line == offset++) {
		BuildStatLine("ST_PHOT", &PhotosTaken, STAT_TYPE_INT, 0, 0); // Photographs Taken
		return 0;
	}
	if (PizzasDelivered > 0.0 && line == offset++) {
		int pizzas = static_cast<int>(PizzasDelivered);
		BuildStatLine("ST_PIZZ", &pizzas, STAT_TYPE_INT, 0, 0); // Pizza's Delivered
		return 0;
	}
	if (GarbagePickups > 0.0 && line == offset++) {
		int garbage = static_cast<int>(GarbagePickups);
		BuildStatLine("ST_GARB", &garbage, STAT_TYPE_INT, 0, 0); // Garbage Pickups Made
		return 0;
	}
	if (IceCreamSold > 0.0 && line == offset++) {
		int icecream = static_cast<int>(IceCreamSold);
		BuildStatLine("ST_ICEC", &icecream, STAT_TYPE_INT, 0, 0); // 'Ice Cream' Sold
		return 0;
	}
	if (HighestScores[1] && line == offset++) {
		BuildStatLine("STHC_02", &HighestScores[1], STAT_TYPE_INT, 0, 0); // Best Percentage of hits for Shooter
		return 0;
	}
	if (FastestTimes[0] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[0];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_01", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Alloy Wheels Of Steel'
		return 0;
	}
	if (FastestTimes[1] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[1];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_02", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'The Driver'
		return 0;
	}
	if (FastestTimes[2] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[2];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_03", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time in Dirt Ring
		return 0;
	}
	if (FastestTimes[3] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[3];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_04", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on RC Plane Race
		return 0;
	}
	if (FastestTimes[4] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[4];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_05", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on RC Car Race
		return 0;
	}
	if (FastestTimes[5] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[5];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_06", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on RC helicopter Pickup
		return 0;
	}
	if (FastestTimes[6] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[6];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_07", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Terminal Velocity'
		return 0;
	}
	if (FastestTimes[7] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[7];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_08", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Ocean Drive'
		return 0;
	}
	if (FastestTimes[8] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[8];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_09", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Border Run'
		return 0;
	}
	if (FastestTimes[9] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[9];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_10", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Capital Cruise'
		return 0;
	}
	if (FastestTimes[10] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[10];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_11", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Tour!'
		return 0;
	}
	if (FastestTimes[11] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[11];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_12", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'V.C. Endurance'
		return 0;
	}
	if (FastestTimes[12] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[12];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_13", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on Downtown Chopper Checkpoint
		return 0;
	}
	if (FastestTimes[13] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[13];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_14", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on Ocean Beach Chopper Checkpoint
		return 0;
	}
	if (FastestTimes[14] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[14];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_15", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on Vice Point Chopper Checkpoint
		return 0;
	}
	if (FastestTimes[15] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[15];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_16", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on Little Haiti Chopper Checkpoint
		return 0;
	}
	if (FastestTimes[16] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[16];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_17", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'PCJ Playground'
		return 0;
	}
	if (FastestTimes[17] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[17];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_18", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Trial By Dirt'
		return 0;
	}
	if (FastestTimes[18] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[18];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_19", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time on 'Test Track'
		return 0;
	}
	if (FastestTimes[19] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[19];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_20", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time for 'Cone Crazy'
		return 0;
	}
	if (FastestTimes[22] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[22];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_23", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time for Checkpoint Charlie
		return 0;
	}
	if (HighestScores[0] && line == offset++) {
		BuildStatLine("STHC_01", &HighestScores[0], STAT_TYPE_INT, 0, 0); // Highest score for Shooter
		return 0;
	}
	if (HighestScores[3] && line == offset++) {
		BuildStatLine("STHC_04", &HighestScores[3], STAT_TYPE_INT, 0, 0); // Highest score with Keepie-Uppy beach ball
		return 0;
	}
	if (HighestScores[2] && line == offset++) {
		BuildStatLine("STHC_03", &HighestScores[2], STAT_TYPE_INT, 0, 0); // Number of drug deals made
		return 0;
	}
	if (BestPositions != 0x7FFFFFFF && line == offset++) {
		BuildStatLine("STHC_05", &BestPositions, STAT_TYPE_INT, 0, 0); // Hotring Best Result
		return 0;
	}
	if (FastestTimes[20] && line == offset++) {
		int minutes = 0, seconds = FastestTimes[20];
		while (seconds > 59) {
			minutes++;
			seconds -= 60;
		}
		if (seconds < 0) {
			seconds *= -1;
		}
		BuildStatLine("STFT_21", &minutes, STAT_TYPE_INT, &seconds, 1); // Fastest time in Hotring
		return 0;
	}
	if (FastestTimes[21] && line == offset++) {
		float time = static_cast<float>(static_cast<int>(FastestTimes[21] / 1000.0f));
		BuildStatLine("STFT_22", &time, STAT_TYPE_FLOAT, 0, 0); // Fastest lap time in Hotring
		return 0;
	}
	if (TopShootingRangeScore > 0.0 && line == offset++) {
		int score = static_cast<int>(TopShootingRangeScore);
		BuildStatLine("TOP_SHO", &score, STAT_TYPE_INT, 0, 0); // Top Shooting Range Score
		return 0;
	}
	if (ShootingRank > 0.0 && line == offset++) {
		int rank = static_cast<int>(ShootingRank);
		BuildStatLine("SHO_RAN", &rank, STAT_TYPE_INT, 0, 0); // Shooting Range Rank
		return 0;
	}
	if (line == offset++) {
		int hours = static_cast<int>(FlightTime / 3.6e6f);
		int minutes = (FlightTime / 60000) % 60;
		BuildStatLine("ST_FTIM", &hours, STAT_TYPE_INT, &minutes, 1); // Flight hours
		return 0;
	}
	// fixes incorrect pilot ranking display
	if (FlightTime >= 5 * 60 * 1000) {
		if (line == offset++) {
			BuildStatLine("ST_PRAN", 0, 0, 0, 0); // Pilot Ranking
			return 0;
		}
		if (line == offset++) {
			if (FlightTime < 10 * 60 * 1000) {
				AddTextLine("ST_PR01");
				return 0;
			}
			if (FlightTime < 20 * 60 * 1000) {
				AddTextLine("ST_PR02");
				return 0;
			}
			if (FlightTime < 30 * 60 * 1000) {
				AddTextLine("ST_PR03");
				return 0;
			}
			if (FlightTime < 60 * 60 * 1000) {
				AddTextLine("ST_PR04");
				return 0;
			}
			if (FlightTime < 90 * 60 * 1000) {
				AddTextLine("ST_PR05");
				return 0;
			}
			if (FlightTime < 120 * 60 * 1000) {
				AddTextLine("ST_PR06");
				return 0;
			}
			if (FlightTime < 150 * 60 * 1000) {
				AddTextLine("ST_PR07");
				return 0;
			}
			if (FlightTime < 180 * 60 * 1000) {
				AddTextLine("ST_PR08");
				return 0;
			}
			if (FlightTime < 210 * 60 * 1000) {
				AddTextLine("ST_PR09");
				return 0;
			}
			if (FlightTime < 240 * 60 * 1000) {
				AddTextLine("ST_PR10");
				return 0;
			}
			if (FlightTime < 300 * 60 * 1000) {
				AddTextLine("ST_PR11");
				return 0;
			}
			if (FlightTime < 600 * 60 * 1000) {
				AddTextLine("ST_PR12");
				return 0;
			}
			if (FlightTime < 1200 * 60 * 1000) {
				AddTextLine("ST_PR13");
				return 0;
			}
			if (FlightTime < 1500 * 60 * 1000) {
				AddTextLine("ST_PR14");
				return 0;
			}
			if (FlightTime < 1800 * 60 * 1000) {
				AddTextLine("ST_PR15");
				return 0;
			}
			if (FlightTime < 2942 * 60 * 1000) {
				AddTextLine("ST_PR16");
				return 0;
			}
			if (FlightTime < 3000 * 60 * 1000) {
				AddTextLine("ST_PR17");
				return 0;
			}
			if (FlightTime < 6000 * 60 * 1000) {
				AddTextLine("ST_PR18");
				return 0;
			}
			AddTextLine("ST_PR19");
			return 0;
		}
	}
	if (BloodRingKills > 0 && line == offset++) {
		BuildStatLine("ST_BRK", &BloodRingKills, STAT_TYPE_INT, 0, 0); // Number of bloodring kills
		return 0;
	}
	if (BloodRingTime > 0 && line == offset++) {
		BuildStatLine("ST_LTBR", &BloodRingTime, STAT_TYPE_INT, 0, 0); // Longest time in bloodring (secs)
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_DRWN", &TimesDrowned, STAT_TYPE_INT, 0, 0); // Fishes Fed
		return 0;
	}
	if (SeagullsKilled > 0 && line == offset++) {
		BuildStatLine("SEAGULL", &SeagullsKilled, STAT_TYPE_INT, 0, 0); // Seagulls Sniped
		return 0;
	}
	float *listeningTime = GetListenTimeArray(DMAudio);
	float mostTime = FavoriteRadioStationList[0], leastTime = FavoriteRadioStationList[0];
	int mostIndex = 0, leastIndex = 0;
	for (int i = 0; i < 10; i++) {
		FavoriteRadioStationList[i] = listeningTime[i];
		if (FavoriteRadioStationList[i] > mostTime) {
			// fixes possibility of showing mp3 station as most favorite if mp3 station is not available
			if (!(i == 9 && !IsMP3RadioChannelAvailable(DMAudio))) {
				mostTime = FavoriteRadioStationList[i];
				mostIndex = i;
			}
		}
		if (FavoriteRadioStationList[i] < leastTime) {
			// fixes possibility of showing wave 103 station as least favorite if mp3 station is not available
			if (!(i == 9 && !IsMP3RadioChannelAvailable(DMAudio))) {
				leastTime = FavoriteRadioStationList[i];
				leastIndex = i;
			}
		}
	}
	// fixes possibility of most favorite station also be least favorite station
	if (mostIndex != leastIndex) {
		if (line == offset++) {
			BuildStatLine("FST_MFR", 0, 0, 0, 0); // Most Favorite Radio Station
			return 0;
		}
		if (line == offset++) {
			switch (mostIndex) {
			case 0:
				AddTextLine("FEA_FM0");
				return 0;
			case 1:
				AddTextLine("FEA_FM1");
				return 0;
			case 2:
				AddTextLine("FEA_FM2");
				return 0;
			case 3:
				AddTextLine("FEA_FM3");
				return 0;
			case 4:
				AddTextLine("FEA_FM4");
				return 0;
			case 5:
				AddTextLine("FEA_FM5");
				return 0;
			case 6:
				AddTextLine("FEA_FM6");
				return 0;
			case 7:
				AddTextLine("FEA_FM7");
				return 0;
			case 8:
				AddTextLine("FEA_FM8");
				return 0;
			case 9:
				AddTextLine("FEA_MP3");
				return 0;
			default:
				AddTextLine("FEA_FM8");
				return 0;
			}
		}
		if (line == offset++) {
			BuildStatLine("FST_LFR", 0, 0, 0, 0); // Least Favorite Radio Station
			return 0;
		}
		if (line == offset++) {
			switch (leastIndex) {
			case 0:
				AddTextLine("FEA_FM0");
				return 0;
			case 1:
				AddTextLine("FEA_FM1");
				return 0;
			case 2:
				AddTextLine("FEA_FM2");
				return 0;
			case 3:
				AddTextLine("FEA_FM3");
				return 0;
			case 4:
				AddTextLine("FEA_FM4");
				return 0;
			case 5:
				AddTextLine("FEA_FM5");
				return 0;
			case 6:
				AddTextLine("FEA_FM6");
				return 0;
			case 7:
				AddTextLine("FEA_FM7");
				return 0;
			case 8:
				AddTextLine("FEA_FM8");
				return 0;
			case 9:
				AddTextLine("FEA_MP3");
				return 0;
			default:
				AddTextLine("FEA_FM8");
				return 0;
			}
		}
	}
	if (line == offset++) {
		BuildStatLine("SPRAYIN", &Sprayings, STAT_TYPE_INT, 0, 0); // Sprayings
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_WEAP", &WeaponBudget, STAT_TYPE_CASH, 0, 0); // Weapon Budget
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_FASH", &FashionBudget, STAT_TYPE_CASH, 0, 0); // Fashion Budget
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_PROP", &PropertyBudget, STAT_TYPE_CASH, 0, 0); // Property Budget
		return 0;
	}
	if (line == offset++) {
		BuildStatLine("ST_AUTO", &AutoPaintingBudget, STAT_TYPE_CASH, 0, 0); // Auto Repair and Painting Budget
		return 0;
	}
	if (line == offset++) {
		float money = static_cast<float>(PropertyDestroyed);
		BuildStatLine("ST_DAMA", &money, STAT_TYPE_CASH, 0, 0); // Property Destroyed
		return 0;
	}
	if (NumPropertyOwned > 0) {
		if (line == offset++) {
			BuildStatLine("PROPOWN", &NumPropertyOwned, STAT_TYPE_INT, 0, 0); // Property Owned
			return 0;
		}
		if (PropertyOwned[0] && line == offset++) {
			AddTextLine("STPR_1");
			return 0;
		}
		if (PropertyOwned[1] && line == offset++) {
			AddTextLine("STPR_2");
			return 0;
		}
		if (PropertyOwned[2] && line == offset++) {
			AddTextLine("STPR_3");
			return 0;
		}
		if (PropertyOwned[3] && line == offset++) {
			AddTextLine("STPR_4");
			return 0;
		}
		if (PropertyOwned[4] && line == offset++) {
			AddTextLine("STPR_5");
			return 0;
		}
		if (PropertyOwned[5] && line == offset++) {
			AddTextLine("STPR_6");
			return 0;
		}
		if (PropertyOwned[6] && line == offset++) {
			AddTextLine("STPR_7");
			return 0;
		}
		if (PropertyOwned[7] && line == offset++) {
			AddTextLine("STPR_8");
			return 0;
		}
		if (PropertyOwned[8] && line == offset++) {
			AddTextLine("STPR_9");
			return 0;
		}
		if (PropertyOwned[9] && line == offset++) {
			AddTextLine("STPR_10");
			return 0;
		}
		if (PropertyOwned[10] && line == offset++) {
			AddTextLine("STPR_11");
			return 0;
		}
		if (PropertyOwned[11] && line == offset++) {
			AddTextLine("STPR_12");
			return 0;
		}
		if (PropertyOwned[12] && line == offset++) {
			AddTextLine("STPR_13");
			return 0;
		}
		if (PropertyOwned[13] && line == offset++) {
			AddTextLine("STPR_14");
			return 0;
		}
		if (PropertyOwned[14] && line == offset++) {
			AddTextLine("STPR_15");
			return 0;
		}
	}
	return offset;
}
