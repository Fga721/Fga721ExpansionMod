#include "Zombie_BullVeteran.h"

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieBullVeteranProps::oZombieBullVeteranPropsBuildSymbols = nullptr;

void ZombieBullVeteranProps::modInit()
{
	LOGI("Initializing ZombieBullVeteranProps");

	Fga721HookFunction(0xDAE6CC, (void*)BullVetConstruct, nullptr);
	Fga721HookFunction(0xDAE804, (void*)buildSymbols, (void**)&oZombieBullVeteranPropsBuildSymbols);
}
