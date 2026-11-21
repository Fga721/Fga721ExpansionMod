#pragma once
#include "Plant.h"

class PowerLilyProps : public PlantPropertySheet
{
public:
	SexyString CollectableType = "plantfood";
	int CollectableCount = 1;
	float CollectableOffsetX = 0.0f;
	float CollectableOffsetY = -60.0f;

	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oPowerLilyPropsBuildSymbols;
	static void modInit();
	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};