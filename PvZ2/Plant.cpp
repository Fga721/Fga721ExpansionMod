#include "Reflection/ReflectionBuilder.h"
#include "Plant.h"

Reflection::CRefManualSymbolBuilder::ConstructFunc PlantType::oPlantTypeConstruct = nullptr;
Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc PlantType::oPlantTypeBuildSymbols = nullptr;

void PlantType::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
	oPlantTypeBuildSymbols(builder, rclass);
	RT_CLASS_REGISTER_STANDARD_PROPERTY(PlantType, IntegerID);
}

void PlantType::modInit()
{
	LOGI("Initializing PlantType");

	Fga721HookFunction(0xC6BF48, (void*)buildSymbols, (void**)&oPlantTypeBuildSymbols);
}