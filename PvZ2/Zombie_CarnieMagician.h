#pragma once
#include "ZombieWithActionsProps.h"
#include "Reflection/ReflectionBuilder.h"
#include "PvZ2/StringRestrictionSet.h"

class ZombieCarnieMagicianProps : public ZombieWithActionsProps
{
public:
	float TeleportOtherStartTime = 6.0f;
	float TeleportSelfStartTime = 23.0f;
	float DoveSpawnStartTime = 33.0f;
	float TimeBetweenTeleportOther = 15.0f; 
	float TimeBetweenTeleportSelf = 20.0f;
	float TimeBetweenDoveSpawn = 23.0f;
	float TeleportationFailPercentage = 5.0f;
	PlantRestrictionSet ImmuneToPlantRestrictionSet;
	bool IsInmuneToShrink = false;

	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieCarnieMagicianPropsBuildSymbols;
	static void modInit();
	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};
