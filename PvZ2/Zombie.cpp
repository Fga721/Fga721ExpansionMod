#include "Reflection/ReflectionBuilder.h"
#include "Zombie.h"

void Zombie::SetStatusesFromDamageInfo(DamageInfo* dmgInfo)
{
	CallFunc<void, Zombie*, DamageInfo*>(0xC431BC, this, dmgInfo);
}

bool Zombie::IsInGridItem()
{
	bool conds = this->m_conditionTracker.m_conditionFlags[zombie_condition_icecubed]
		|| this->m_conditionTracker.m_conditionFlags[zombie_condition_present_boxed]
		|| this->m_conditionTracker.m_conditionFlags[zombie_condition_stoneblocked];
	return conds;
}

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