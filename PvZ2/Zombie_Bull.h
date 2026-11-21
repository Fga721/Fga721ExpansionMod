#pragma once
#include "Zombie.h"
#include "ZombieAnimRig.h"

class ZombieBullProps : public ZombiePropertySheet
{
public:
	Rect BuckRect = { -95, 10, 40, 125 };
	float BullEnterSpeed = 0.30f;
	float BullPawLocation = 810.0f;
	float BullRunSpeed = 1.0f;
	float BullRunAgainDelay = 3.0f;
	float BullRammingDamage = 1500.0f;
	float LaunchHeight = 250.0f;
	float LaunchAirTime = 0.75f;
	SexyString RiderType = "west_bullrider";
	std::vector<SexyString> RiderLayerToHide;
	float LaunchDistance = 256.0f;
	bool UseGetUpAnim = true;

	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieBullPropsBuildSymbols;
	static void modInit();
	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};

class ZombieBull : public Zombie
{
public:
	bool m_hasLaunched;
	bool m_hitEntity;
	bool m_walkCycled;
	char pad_align[1];
	int m_damageState;
};

static_assert(sizeof(ZombieBull) == 1104);
static_assert(offsetof(ZombieBull, m_hasLaunched) == 1096);
static_assert(offsetof(ZombieBull, m_hitEntity) == 1097);
static_assert(offsetof(ZombieBull, m_walkCycled) == 1098);
static_assert(offsetof(ZombieBull, m_damageState) == 1100);

class ZombieAnimRig_Bull : public ZombieAnimRig
{
public:
	bool m_running;
};
static_assert(sizeof(ZombieAnimRig_Bull) == 672);
static_assert(offsetof(ZombieAnimRig_Bull, m_running) == 664);



