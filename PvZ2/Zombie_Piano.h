#pragma once
#include "Zombie.h"
#include "Reflection/ReflectionBuilder.h"
#include "PvZ2/StringRestrictionSet.h"

class ZombiePianoProps : public ZombiePropertySheet
{
public:
	float FastMoveSpeed = 0.4f;
	PlantRestrictionSet PlantsWhichBreakPianoOnCollision;

	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombiePianoPropsBuildSymbols;
	static void modInit();
	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};
