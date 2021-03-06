#pragma once

class __declspec(dllexport) Stats
{
public:
	static void(__cdecl *BuildStatLine)(char *, void *, int, void *, int);
	static float *FavoriteRadioStationList;
	static int &TyresPopped;
	static int *PedsKilledOfThisType;
	static int &HighestLevelVigilanteMission;
	static int &BoatsExploded;
	static float &ShootingRank;
	static float &TotalProgressInGame;
	static int &BestStuntJump;
	static int &LongestStoppie;
	static int &NumberOfUniqueJumpsFound;
	static int *FastestTimes;
	static int &TotalNumberMissions;
	static float &GarbagePickups;
	static float &DistanceTravelledByGolfCart;
	static int &NumberKillFrenziesPassed;
	static int &TotalNumberKillFrenzies;
	static float &LoanSharks;
	static int &HelisDestroyed;
	static int &IndustrialPassed;
	static int &LongestWheelie;
	static int &HighestLevelFireMission;
	static int &TimesDied;
	static int &RoundsFiredByPlayer;
	static int &TimesArrested;
	static float &IceCreamSold;
	static int &PeopleKilledByOthers;
	static int &PropertyDestroyed;
	static int &TotalNumberOfUniqueJumps;
	static int &FlightTime;
	static int &SeagullsKilled;
	static float &LongestWheelieDist;
	static float &PizzasDelivered;
	static int &PeopleKilledByPlayer;
	static int &KgsOfExplosivesUsed;
	static int &CriminalsCaught;
	static int &MaximumJumpFlips;
	static int &SuburbanPassed;
	static int &MaximumJumpSpins;
	static int &HighestLevelAmbulanceMission;
	static int &NumPropertyOwned;
	static float &HighestChaseValue;
	static int &DaysPassed;
	static float &MaximumJumpDistance;
	static int &PhotosTaken;
	static float &StoresKnockedOff;
	static int &CommercialPassed;
	static float &PropertyBudget;
	static int &TimesDrowned;
	static float &Longest2WheelDist;
	static int &LivesSavedWithAmbulance;
	static int &WantedStarsAttained;
	static int &WantedStarsEvaded;
	static float &LongestStoppieDist;
	static float &DistanceTravelledByHelicopter;
	static float &DistanceTravelledByPlane;
	static int &FiresExtinguished;
	static int &BulletsThatHit;
	static float &ProgressMade;
	static int *HighestScores;
	static int &HeadsPopped;
	static int &BloodRingKills;
	static float &MaximumJumpHeight;
	static float &FashionBudget;
	static int &PassengersDroppedOffWithTaxi;
	static int &SafeHouseVisits;
	static float &DistanceTravelledByBike;
	static int &BloodRingTime;
	static float &DistanceTravelledByBoat;
	static int &CarsExploded;
	static float &TopShootingRangeScore;
	static float &DistanceTravelledOnFoot;
	static int &MoneyMadeWithTaxi;
	static float &MovieStunts;
	static int &Sprayings;
	static int &NoMoreHurricanes;
	static int &Longest2Wheel;
	static float &DistanceTravelledByCar;
	static int &BestPositions;
	static float &WeaponBudget;
	static int &MissionsGiven;
	static float &AutoPaintingBudget;
	static float &Assassinations;
	static char *PropertyOwned;

	static bool AlwaysTrue();
	static bool AlwaysFalse();
	static void Register(bool(*condition)(), void(*function)());
	static void AddTextLine(const char *string);
};
