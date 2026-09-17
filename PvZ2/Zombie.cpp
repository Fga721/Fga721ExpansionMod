#include "Reflection/ReflectionBuilder.h"
#include "Zombie.h"

Reflection::CRefManualSymbolBuilder::ConstructFunc ZombieType::oZombieTypeConstruct = nullptr;
Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieType::oZombieTypeBuildSymbols = nullptr;

void ZombieType::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
	oZombieTypeBuildSymbols(builder, rclass);
	RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieType, IntegerID);
}

void ZombieType::modInit()
{
    LOGI("Initializing ZombieType");

	Fga721HookFunction(0x106828C, (void*)buildSymbols, (void**)&oZombieTypeBuildSymbols);
}