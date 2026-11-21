#include "Zombie_Gargantuar.h"
#include "ZombieHelper.h"
#include "Board.h"

typedef int64(*zombieGargLaunch)(ZombieGargantuar*);
zombieGargLaunch oZombieGargantuarLaunch = nullptr;

int64 hkZombieGargantuarLaunch(ZombieGargantuar* self)
{
    if (ZombieHasCondition(self, zombie_condition_hypnotized))
    {
		auto* props = reinterpret_cast<ZombieGargantuarProps*>(self->m_propertySheet.Get());

        if (props != nullptr)
        {
            uintptr_t TRowAdd = reinterpret_cast<uintptr_t>(props) + 600;
            int* TRowPtr = reinterpret_cast<int*>(TRowAdd);

            int OTRow = *TRowPtr;

            float XPos = self->m_position.x;
            int CTRow = static_cast<int>(XPos / GRID_TILE_WIDTH);

            int NTRow = CTRow + props->HypnotizedImpRowsInFront;
            if (NTRow > 8) NTRow = 8;

            *TRowPtr = NTRow;

            int64 result = oZombieGargantuarLaunch(self);
            *TRowPtr = OTRow;

            return result;
        }
    }

    return oZombieGargantuarLaunch(self);
}

void* hkGargantuarConstruct()
{
    auto* props = new ZombieGargantuarProps();

    typedef void* (*ctorWithThisPtr)(void*);
    ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
    baseCtor(props);

    *reinterpret_cast<uintptr_t*>(props) = Fga721GetActualOffset(0x2432A08);

    return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieGargantuarProps::oZombieGargantuarPropsBuildSymbols = nullptr;

void ZombieGargantuarProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
    if (oZombieGargantuarPropsBuildSymbols != nullptr)
    {
        oZombieGargantuarPropsBuildSymbols(builder, rclass);
    }

    RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieGargantuarProps, HypnotizedImpRowsInFront);
}

void ZombieGargantuarProps::modInit()
{
    LOGI("Initializing ZombieGargantuarProps");
    Fga721HookFunction(0xB54604, (void*)hkZombieGargantuarLaunch, (void**)&oZombieGargantuarLaunch);

    Fga721HookFunction(0xDAA3EC, (void*)hkGargantuarConstruct, nullptr);
    Fga721HookFunction(0xDAA778, (void*)buildSymbols, (void**)&oZombieGargantuarPropsBuildSymbols);
}

