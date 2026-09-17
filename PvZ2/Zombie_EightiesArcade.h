#pragma once
#include "ZombieWithActionsProps.h"

class ZombieEightiesArcadeProps : public ZombieWithActionsProps
{
public:
	SexyString JamStyle = "jam_8bit";
	SexyString GridItemType = "eightiesarcadecabinet";

	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieEightiesArcadePropsBuildSymbols;
	static void modInit();
	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};