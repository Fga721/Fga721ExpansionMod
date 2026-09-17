#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unistd.h>

#include "Logging.h"
#include "MemUtils.h"
#include "SexyTypes.h"
#include "Board.h"
#include "PvZ2/Zombie.h"
#include "PvZ2/Plant.h"
#include "Fga721ExampleMod.h"
#include "PvZ2/Zombie_CarnieMagician.h"
#include "PvZ2/Zombie_Piano.h"
#include "PvZ2/Zombie_EightiesArcade.h"
#include "PvZ2/Zombie_TombRaiser.h"
#include "PvZ2/Plant_PowerLily.h"

class ZombieAlmanac
{
public:
    void* vftable;
    std::map<SexyString, uint> m_aliasToId;
};

class PlantNameMapper
{
public:
    void* vftable;
    std::map<SexyString, uint> m_aliasToId;
};

std::vector<PlantType*> g_modPlantTypenames;
std::vector<ZombieType*> g_modZombieTypenames;

// recreamos las clases y creamos vector strings para registrar los typenames originales

#define REGISTER_PLANT_TYPENAME(typename) \
    g_modPlantTypenames.push_back(typename); \

#define REGISTER_ZOMBIE_TYPENAME(typename) \
    g_modZombieTypenames.push_back(typename); \

typedef void* (*plantTypeCtor)(PlantType*);
plantTypeCtor oPlantTypeCtor = nullptr;

void* hkPlantTypeCtor(PlantType* self)
{
    void* result = oPlantTypeCtor(self);
    REGISTER_PLANT_TYPENAME(self);
    return result;
}

// registra los typenames originales en una variable

typedef PlantNameMapper* (*PlantNameMapperCtor)(PlantNameMapper*);
PlantNameMapperCtor oPlantNameMapperCtor = nullptr;

void* hkCreatePlantNameMapper(PlantNameMapper* self)
{
    oPlantNameMapperCtor(self);
    self->m_aliasToId.clear();

    // borramos los ids

    for (size_t iter = 0; iter < g_modPlantTypenames.size(); iter++) // usamos la variable mod para calcular cuantas veces debe ejecutarse el ciclo for
    {
        PlantType* type = g_modPlantTypenames[iter];
        self->m_aliasToId.emplace(SexyString(type->TypeName), type->IntegerID); // crea las ids con el typename de la planta y su integerid
    }

    return self;
}

typedef void* (*zombieTypeCtor)(ZombieType*);
zombieTypeCtor oZombieTypeCtor = nullptr;

void* hkZombieTypeCtor(ZombieType* self)
{
    void* result = oZombieTypeCtor(self);
    REGISTER_ZOMBIE_TYPENAME(self);
    return result;
}

typedef ZombieAlmanac* (*ZombieAlmanacCtor)(ZombieAlmanac*);
ZombieAlmanacCtor oZombieAlmanacCtor = nullptr;

void* hkCreateZombieTypenameMap(ZombieAlmanac* self)
{
    oZombieAlmanacCtor(self);
    self->m_aliasToId.clear();

    for (size_t iter = 0; iter < g_modZombieTypenames.size(); iter++)
    {
        auto* type = g_modZombieTypenames[iter];
        self->m_aliasToId.emplace(SexyString(type->TypeName), type->IntegerID);
    }

    return self;
}

// memoria de momia

uint64 oCamelZombieFunc = 0;

typedef void(*camelMinigameModuleFunc)(int64, int64, char);
camelMinigameModuleFunc cmmFunc = (camelMinigameModuleFunc)Fga721GetActualOffset(0xAC4638);

void* vftable;

enum class ZombieState_CamelTouch {
    ZS_CAMELTOUCH_WaitingToRise = 18,
    ZS_CAMELTOUCH_RisingFromGround = 19,
    ZS_CAMELTOUCH_Stunned = 20
};

// Recreamos la clase del zombiecameltouch (muchas gracias a blazey por este codigo)

class ZombieCamelTouch
{
public:
    char pad1[1112];
    pvztime_t m_riseFromGroundDelay;
    char pad2[28];

    void EnterState(int state, bool a3)
    {
        return CallFunc<void, ZombieCamelTouch*, int, bool>(0xC3D428, this, state, a3);
    }

    virtual void UpdatePosition(Sexy::SexyVector3* newPos) {};

    static void SpawnFromGround(ZombieCamelTouch* thisPtr, Sexy::SexyVector3* groundPos, int delay);
};

static_assert(sizeof(ZombieCamelTouch) == 1152);
static_assert(offsetof(ZombieCamelTouch, m_riseFromGroundDelay) == 1120);

// funcion que hace que el zombie salga del suelo, con un delay y una posicion especifica

void ZombieCamelTouch::SpawnFromGround(ZombieCamelTouch* thisPtr, Sexy::SexyVector3* groundPos, int delay)
{
    thisPtr->m_riseFromGroundDelay = delay;
    thisPtr->UpdatePosition(groundPos);
    thisPtr->EnterState((int)ZombieState_CamelTouch::ZS_CAMELTOUCH_WaitingToRise, false);
}

// hacemos que la funcion vaya hasta otra funcion colchon para que almacene la llamada original, primero ejecutamos la funcion de la salida de los camellos del suelo

void hkCamelZombieFunc(int64 a1, int64 a2, char a3)
{
	ZombieCamelTouch::SpawnFromGround(reinterpret_cast<ZombieCamelTouch*>(a1), reinterpret_cast<Sexy::SexyVector3*>(a2), a3);
    cmmFunc(a1, a2, a3);
}

// Fix de la teletranspapum al teletransportar (gracias a renojson por el codigo)

typedef void (*TeleportatoMineTeleport)(void*, Sexy::RtWeakPtr<Zombie>*);
TeleportatoMineTeleport oTeleportatoMineTeleport = nullptr;

void hkFixTeleportatoMineTeleport(void* a1, Sexy::RtWeakPtr<Zombie>* a2) {
    oTeleportatoMineTeleport(a1, a2);
    Sexy::RtWeakPtr<Zombie> zombiePtr;
    zombiePtr.FromOther(a2);
    auto zombie = reinterpret_cast<Zombie*>(zombiePtr.Get());
    CallFunc<Zombie*>(0xC4BC48, zombie, zombie_condition_stun);
}

// bueno, como conclusion a esto es que el and64inlinehook es mrd (krishna te amo)
__attribute__((constructor))
void libFga721_main()
{
    // incializar hooks
    Fga721HookFunction(0xC6D080, (void*)hkPlantTypeCtor, (void**)&oPlantTypeCtor);
    Fga721HookFunction(0x11797B4, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor);
    Fga721HookFunction(0x10680BC, (void*)hkZombieTypeCtor, (void**)&oZombieTypeCtor);
    Fga721HookFunction(0x14665C4, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor);

    Fga721HookFunction(0xB18DC4, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc);
    Fga721HookFunction(0x1001C04, (void*)hkFixTeleportatoMineTeleport, (void**)&oTeleportatoMineTeleport);
    // Fga721HookFunction(0xBD873C, (void*)hkHealerConditionFunc, (void**)&header);
    // Fga721HookFunction(0xC0F91C, (void*)hkHealerImmuneToShrink, (void**)&header);

    // inicializar mods

    ZombieCarnieMagicianProps::modInit();
    ZombieEightiesArcadeProps::modInit();
    ZombieTombRaiserProps::modInit();
    ZombiePianoProps::modInit();
    PowerLilyProps::modInit();
    
    ZombieType::modInit();
    PlantType::modInit();

    LOGI("Finished initializing");
}