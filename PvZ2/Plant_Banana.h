#pragma once
#include "Plant.h"
#include "PlantFramework.h"

class PlantBanana : public PlantFramework
{
	bool m_onlyTargetZombies;
	bool m_fireIgnoreBoardState;
	char _pad_to_16[6];
};
static_assert(sizeof(PlantBanana) == 24);

class BananaProps : public PlantPropertySheet
{
public:
    char _pad_fix_offset[4];
    int NumPlantFoodRockets;
    float FireTime;
    float PlantFoodFireTime;
    SexyVector2 TargetOffset;

    static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oBananaPropsBuildSymbols;
    static void modInit();
    static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};
static_assert(sizeof(BananaProps) == 480);

struct ResourceDescriptorStorage
{
    alignas(8) std::byte bytes[0x18]{};
};

struct RawDelegate3
{
    uintptr_t vtable;
    uintptr_t field08;
    uintptr_t field10;
    uintptr_t field18;
    uintptr_t field20;
};

struct RawDelegate1Plant
{
    uintptr_t vtable;
    uintptr_t callback;
    uintptr_t field10;
    uintptr_t self;
    uint32_t flag;
    uint32_t padding;
    uintptr_t invoker;
};