#pragma once
#include "Zombie_Bull.h"

class ZombieBullVeteranProps : public ZombieBullProps
{
public:
	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieBullVeteranPropsBuildSymbols;
	static void modInit();

	static void* BullVetConstruct()
	{
		auto* props = new ZombieBullVeteranProps();

		typedef void* (*ctorWithThisPtr)(void*);
		ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
		baseCtor(props);

		*reinterpret_cast<int*>(uintptr_t(props)) = Fga721GetActualOffset(0x2433048);
		return props;
	}

	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
	{
		RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullVeteranProps, BullRunAgainDelay);
		RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullVeteranProps, BullRammingDamage);
		RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullVeteranProps, LaunchHeight);
		RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullVeteranProps, LaunchAirTime);
		RT_CLASS_REGISTER_STRING_PROPERTY(ZombieBullVeteranProps, RiderType);
		RT_CLASS_REGISTER_STRING_VECTOR_PROPERTY(ZombieBullVeteranProps, RiderLayerToHide);
		RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullVeteranProps, LaunchDistance);
		RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullVeteranProps, UseGetUpAnim);
	};

};

