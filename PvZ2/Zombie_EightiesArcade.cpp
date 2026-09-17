#include "Zombie_EightiesArcade.h"
#include "Zombie.h"
#include "Board.h"
#include "GridItem.h"

typedef ZombieEightiesArcadeProps* (*GetPropsFromComponentFuncArcade)(void*);
GetPropsFromComponentFuncArcade GetPropsArcade = (GetPropsFromComponentFuncArcade)Fga721GetActualOffset(0xB271C4);

typedef void(*arcadeZombiePushGridItem)(Zombie*, int);
arcadeZombiePushGridItem oArcadeZombiePushGridItem = nullptr;

// the type should be ZombieEightiesArcade*
void hkArcadeZombiePushGridItem(Zombie* self, int a2)
{
    ZombieEightiesArcadeProps* props = GetPropsArcade(self);

    if (props->GridItemType == "eightiesarcadecabinet") // si el gi es el predeterminado, ejecuta la funcion original; esto es necesario ya que si no lo hacemos provoca bugs
    {
        oArcadeZombiePushGridItem(self, a2);
    }
    else
    {
        int spawnPosY = (540 - self->m_position.y) / 76 * -1 + 5;
        auto* gridItem = GridItem::SpawnGridItemAt(props->GridItemType, 10, spawnPosY);
    }
}

void* HkArcadeConstruct() // offset: 0xB276AC
{
    auto* props = new ZombieEightiesArcadeProps();

    typedef void* (*ctorWithThisPtr)(void*);
    ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
    baseCtor(props);

    *reinterpret_cast<int*>(uintptr_t(props)) = Fga721GetActualOffset(0x23EBC78);
    return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieEightiesArcadeProps::oZombieEightiesArcadePropsBuildSymbols = nullptr;

void ZombieEightiesArcadeProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass) // offset posible: 0xB27824
{
    oZombieEightiesArcadePropsBuildSymbols(builder, rclass);
    RT_CLASS_REGISTER_STRING_PROPERTY(ZombieEightiesArcadeProps, GridItemType);
}

void ZombieEightiesArcadeProps::modInit()
{
    LOGI("Initializing ZombieEightiesArcadeProps");

    Fga721HookFunction(0xB273E0, (void*)hkArcadeZombiePushGridItem, (void**)&oArcadeZombiePushGridItem);
    Fga721HookFunction(0xB276AC, (void*)HkArcadeConstruct, nullptr);
    Fga721HookFunction(0xB27824, (void*)buildSymbols, (void**)&oZombieEightiesArcadePropsBuildSymbols);
}