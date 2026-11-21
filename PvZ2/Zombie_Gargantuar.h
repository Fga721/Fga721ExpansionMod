#pragma once
#include "Zombie.h"

using namespace Sexy;

class ZombieGargantuarProjectilePair {
public:
    float HealthPercentThrowImp;
    std::vector<SexyString> ProjectileLayersToHide;
};

class ZombieGargantuarProps : public ZombiePropertySheet
{
public:

    std::vector<ZombieGargantuarProjectilePair> HealthThresholdToImpAmmoLayers;
    float MinPosXThrowImp;
    float ThrowImpDuration;
    int32_t ImpTargetColumn;
    float ImpApex;
    Sexy::SexyVector3 ImpSpawnOffset;
    float ImpFlightTime;
    float SmashDuration;
    float SmashDamage;
    SexyString ImpType;
    SexyString SoundOnSmash;
    SexyString SoundOnCannon;
    int HypnotizedImpRowsInFront = 1;

    static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieGargantuarPropsBuildSymbols;
    static void modInit();
    static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass);
};

static_assert(offsetof(ZombieGargantuarProps, HealthThresholdToImpAmmoLayers) == 568);
static_assert(offsetof(ZombieGargantuarProps, ImpSpawnOffset) == 608);
static_assert(offsetof(ZombieGargantuarProps, ImpFlightTime) == 620);