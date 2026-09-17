#pragma once
#include "Plant_PowerLily.h"
#include "PlantFramework.h"
#include "SexyTypes.h"
#include "Board.h"
#include "MemUtils.h"
#include "Sexy/RtWeakPtr.h"

typedef void (*PlantPowerLilyTrigger)(PlantFramework*, int64 a2);

void hkPlantPowerLilyTrigger(PlantFramework* self, int64 a2)
{
    auto* props = reinterpret_cast<PowerLilyProps*>(self->m_plant->m_propertySheet.Get());
    Sexy::SexyVector3 spawnPos(self->m_plant->m_position.x + props->CollectableOffsetX, self->m_plant->m_position.y + props->CollectableOffsetY, self->m_plant->m_position.z);
    for (int i = 0; i < props->CollectableCount; i++) {
        CallFunc<void, Board*, SexyString, Sexy::SexyVector3*>(0xAA4180, Board::GetBoard(), props->CollectableType, &spawnPos);
    }
}

void* hkPowerLilyConstruct()
{
    auto* props = new PowerLilyProps();

    typedef void* (*ctorWithThisPtr)(void*);
    ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0x611410);
    baseCtor(props);

    *reinterpret_cast<uintptr_t*>(props) = Fga721GetActualOffset(0x237E158);

    return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc PowerLilyProps::oPowerLilyPropsBuildSymbols = nullptr;

void PowerLilyProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
    if (oPowerLilyPropsBuildSymbols != nullptr)
    {
        oPowerLilyPropsBuildSymbols(builder, rclass);
    }

    RT_CLASS_REGISTER_STRING_PROPERTY(PowerLilyProps, CollectableType);
    RT_CLASS_REGISTER_STANDARD_PROPERTY(PowerLilyProps, CollectableCount);
    RT_CLASS_REGISTER_STANDARD_PROPERTY(PowerLilyProps, CollectableOffsetY);
}

void PowerLilyProps::modInit()
{
    LOGI("Initializing PowerLilyProps");

    Fga721HookFunction(0xED5688, (void*)hkPlantPowerLilyTrigger, nullptr);
    // 0xAA4180

    Fga721HookFunction(0x61AC34, (void*)hkPowerLilyConstruct, nullptr);
    Fga721HookFunction(0x61AD50, (void*)buildSymbols, (void**)&oPowerLilyPropsBuildSymbols);
}