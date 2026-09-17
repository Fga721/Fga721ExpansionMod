#pragma once
#include "Zombie.h"
#include "Reflection/ReflectionBuilder.h"

class ZombieTombRaiserProps : public ZombiePropertySheet
{
public:
    float TimeBetweenCasts = 0.0f;
    float TimeBetweenRaisings = 6.0f;
    float NumberOfTombsToSpawn = 2.0f;
    Sexy::RtWeakPtr<Projectile> Projectile;
    SexyString GraveType = "gravestone_egypt";

    static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieTombRaiserPropsBuildSymbols;
    static void modInit();
    static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};
