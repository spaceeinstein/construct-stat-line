#include "Stats.h"
#include <Windows.h>
#include "StatsSystem.h"

void(__cdecl *Stats::BuildStatLine)(char *, void *, int, void *, int) = (void(__cdecl *)(char *, void *, int, void *, int))0x004CAE8F;
float *Stats::FavoriteRadioStationList = reinterpret_cast<float *>(0x00862460);
int &Stats::TyresPopped = *reinterpret_cast<int *>(0x0094DB58);
int *Stats::PedsKilledOfThisType = reinterpret_cast<int *>(0x0094DB64);
int &Stats::HighestLevelVigilanteMission = *reinterpret_cast<int *>(0x0094DD60);
int &Stats::BoatsExploded = *reinterpret_cast<int *>(0x00974B04);
float &Stats::ShootingRank = *reinterpret_cast<float *>(0x00974B08);
float &Stats::TotalProgressInGame = *reinterpret_cast<float *>(0x00974B0C);
int &Stats::BestStuntJump = *reinterpret_cast<int *>(0x00974B30);
int &Stats::LongestStoppie = *reinterpret_cast<int *>(0x00974B3C);
int &Stats::NumberOfUniqueJumpsFound = *reinterpret_cast<int *>(0x00974B48);
int *Stats::FastestTimes = reinterpret_cast<int *>(0x00974B80);
int &Stats::TotalNumberMissions = *reinterpret_cast<int *>(0x00974BF0);
float &Stats::GarbagePickups = *reinterpret_cast<float *>(0x00974C00);
float &Stats::DistanceTravelledByGolfCart = *reinterpret_cast<float *>(0x00974C04);
int &Stats::NumberKillFrenziesPassed = *reinterpret_cast<int *>(0x00974C08);
int &Stats::TotalNumberKillFrenzies = *reinterpret_cast<int *>(0x00974C0C);
float &Stats::LoanSharks = *reinterpret_cast<float *>(0x00974C28);
int &Stats::HelisDestroyed = *reinterpret_cast<int *>(0x009751F0);
int &Stats::IndustrialPassed = *reinterpret_cast<int *>(0x009751F4);
int &Stats::LongestWheelie = *reinterpret_cast<int *>(0x0097530C);
int &Stats::HighestLevelFireMission = *reinterpret_cast<int *>(0x00975310);
int &Stats::TimesDied = *reinterpret_cast<int *>(0x00975320);
int &Stats::RoundsFiredByPlayer = *reinterpret_cast<int *>(0x0097532C);
int &Stats::TimesArrested = *reinterpret_cast<int *>(0x00975330);
float &Stats::IceCreamSold = *reinterpret_cast<float *>(0x00975390);
int &Stats::PeopleKilledByOthers = *reinterpret_cast<int *>(0x009753AC);
int &Stats::PropertyDestroyed = *reinterpret_cast<int *>(0x00975404);
int &Stats::TotalNumberOfUniqueJumps = *reinterpret_cast<int *>(0x00978530);
int &Stats::FlightTime = *reinterpret_cast<int *>(0x0097854C);
int &Stats::SeagullsKilled = *reinterpret_cast<int *>(0x0097869C);
float &Stats::LongestWheelieDist = *reinterpret_cast<float *>(0x009786C0);
float &Stats::PizzasDelivered = *reinterpret_cast<float *>(0x00978780);
int &Stats::PeopleKilledByPlayer = *reinterpret_cast<int *>(0x00978794);
int &Stats::KgsOfExplosivesUsed = *reinterpret_cast<int *>(0x009787A8);
int &Stats::CriminalsCaught = *reinterpret_cast<int *>(0x009787B4);
int &Stats::MaximumJumpFlips = *reinterpret_cast<int *>(0x009787DC);
int &Stats::SuburbanPassed = *reinterpret_cast<int *>(0x00978A0C);
int &Stats::MaximumJumpSpins = *reinterpret_cast<int *>(0x00978D14);
int &Stats::HighestLevelAmbulanceMission = *reinterpret_cast<int *>(0x00978DB8);
int &Stats::NumPropertyOwned = *reinterpret_cast<int *>(0x00978E08);
float &Stats::HighestChaseValue = *reinterpret_cast<float *>(0x00978E0C);
int &Stats::DaysPassed = *reinterpret_cast<int *>(0x0097F1F4);
float &Stats::MaximumJumpDistance = *reinterpret_cast<float *>(0x0097F210);
int &Stats::PhotosTaken = *reinterpret_cast<int *>(0x0097F21C);
float &Stats::StoresKnockedOff = *reinterpret_cast<float *>(0x0097F898);
int &Stats::CommercialPassed = *reinterpret_cast<int *>(0x009B489C);
float &Stats::PropertyBudget = *reinterpret_cast<float *>(0x009B48B0);
int &Stats::TimesDrowned = *reinterpret_cast<int *>(0x009B48B4);
float &Stats::Longest2WheelDist = *reinterpret_cast<float *>(0x009B48D0);
int &Stats::LivesSavedWithAmbulance = *reinterpret_cast<int *>(0x009B5EA8);
int &Stats::WantedStarsAttained = *reinterpret_cast<int *>(0x009B5EB8);
int &Stats::WantedStarsEvaded = *reinterpret_cast<int *>(0x009B5F30);
float &Stats::LongestStoppieDist = *reinterpret_cast<float *>(0x009B5F44);
float &Stats::DistanceTravelledByHelicopter = *reinterpret_cast<float *>(0x009B6A48);
float &Stats::DistanceTravelledByPlane = *reinterpret_cast<float *>(0x009B6A78);
int &Stats::FiresExtinguished = *reinterpret_cast<int *>(0x009B6A84);
int &Stats::BulletsThatHit = *reinterpret_cast<int *>(0x009B6CD4);
float &Stats::ProgressMade = *reinterpret_cast<float *>(0x009B6CDC);
int *Stats::HighestScores = reinterpret_cast<int *>(0x009B6E20);
int &Stats::HeadsPopped = *reinterpret_cast<int *>(0x009B6E38);
int &Stats::BloodRingKills = *reinterpret_cast<int *>(0x009B6E54);
float &Stats::MaximumJumpHeight = *reinterpret_cast<float *>(0x00A0CFD8);
float &Stats::FashionBudget = *reinterpret_cast<float *>(0x00A0D068);
int &Stats::PassengersDroppedOffWithTaxi = *reinterpret_cast<int *>(0x00A0D1DC);
int &Stats::SafeHouseVisits = *reinterpret_cast<int *>(0x00A0D228);
float &Stats::DistanceTravelledByBike = *reinterpret_cast<float *>(0x00A0D2D8);
int &Stats::BloodRingTime = *reinterpret_cast<int *>(0x00A0D2E0);
float &Stats::DistanceTravelledByBoat = *reinterpret_cast<float *>(0x00A0D384);
int &Stats::CarsExploded = *reinterpret_cast<int *>(0x00A0D388);
float &Stats::TopShootingRangeScore = *reinterpret_cast<float *>(0x00A0D8A4);
float &Stats::DistanceTravelledOnFoot = *reinterpret_cast<float *>(0x00A0D9B4);
int &Stats::MoneyMadeWithTaxi = *reinterpret_cast<int *>(0x00A0D9C8);
float &Stats::MovieStunts = *reinterpret_cast<float *>(0x00A0FC8C);
int &Stats::Sprayings = *reinterpret_cast<int *>(0x00A0FC94);
int &Stats::NoMoreHurricanes = *reinterpret_cast<int *>(0x00A0FCAC);
int &Stats::Longest2Wheel = *reinterpret_cast<int *>(0x00A0FCF8);
float &Stats::DistanceTravelledByCar = *reinterpret_cast<float *>(0x00A0FCFC);
int &Stats::BestPositions = *reinterpret_cast<int *>(0x00A0FD80);
float &Stats::WeaponBudget = *reinterpret_cast<float *>(0x00A0FDCC);
int &Stats::MissionsGiven = *reinterpret_cast<int *>(0x00A1023C);
float &Stats::AutoPaintingBudget = *reinterpret_cast<float *>(0x00A10298);
float &Stats::Assassinations = *reinterpret_cast<float *>(0x00A10918);
char *Stats::PropertyOwned = reinterpret_cast<char *>(0x00A10AFD);

bool Stats::AlwaysTrue()
{
	return true;
}

bool Stats::AlwaysFalse()
{
	return false;
}

void Stats::Register(bool(*condition)(), void(*function)())
{
	if (StatsSystem::total) {
		StatsSystem::line = StatsSystem::line->next = new Stat(condition, function);
	} else {
		StatsSystem::begin = StatsSystem::line = new Stat(condition, function);
	}
}

void Stats::AddTextLine(const char *string)
{
	void(__cdecl *UnicodeStrCpy)(wchar_t *, wchar_t const *) = (void(__cdecl *)(wchar_t *, wchar_t const *))0x005524D0;
	wchar_t *(__thiscall *Get)(unsigned int, const char *) = (wchar_t *(__thiscall *)(unsigned int, const char *))0x00584F30;
	wchar_t *uString2 = reinterpret_cast<wchar_t *>(0x007D9010);
	wchar_t *uString = reinterpret_cast<wchar_t *>(0x00821068);
	unsigned int TheText = 0x0094B220;

	uString[0] = 0;
	UnicodeStrCpy(uString2, Get(TheText, string));
}
