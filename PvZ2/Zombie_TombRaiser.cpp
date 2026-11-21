#include "Zombie_TombRaiser.h"
#include <unordered_map>

typedef void* (*SpawnGraveFunc)(int64, void*, int, int);
SpawnGraveFunc oSpawnGrave = NULL;

typedef void* (*TombRaiserThrowFunc)(Zombie*, int*);
TombRaiserThrowFunc oTombRaiserThrow = NULL;

typedef void* (*TombraiserProjectileImpact)(void*);
TombraiserProjectileImpact oTombraiserProjectileImpact = NULL;

typedef ZombieTombRaiserProps* (*GetPropsFromComponentFuncTombRaiser)(void*);
GetPropsFromComponentFuncTombRaiser GetPropsTombRaiser = (GetPropsFromComponentFuncTombRaiser)Fga721GetActualOffset(0xB23988);

static SexyString CustomGrave = "gravestone_egypt";
float WillChangeGrave = false;

void* hkTombRaiserThrow(Zombie* self, int* gridPosition)
{
    ZombieTombRaiserProps* props = GetPropsTombRaiser(self); // obtiene la propiedad del zombie
    if (props != nullptr)
    {
        CustomGrave = props->GraveType.c_str(); // le da un valor a customgrave
    }

    return oTombRaiserThrow(self, gridPosition);
}

void* hkTombraiserProjectileImpact(void* projectile)
{
    WillChangeGrave = true; // al caer la tumba, el valor se vuelve true para que genere la tumba correspondiente
    return oTombraiserProjectileImpact(projectile);

}

void* hkSpawnGrave(int64 a1, void* OriginalGrave, int column, int row)
{
    if (WillChangeGrave == true) // vemos si el valor es true, si eliminamos esto, el juego piensa que todos los griditems son los del levantatumbas los cambia
    {
        if (!CustomGrave.empty())
        {
            WillChangeGrave = false;
            SexyString GraveType(CustomGrave.c_str()); // string para la tumba de la propiedad del zombie
            void* customGraveResult = oSpawnGrave(a1, &GraveType, column, row);
            CustomGrave.clear();
            return customGraveResult; // retorna la tumba nueva, reemplazando la original
        }
    }

    return oSpawnGrave(a1, OriginalGrave, column, row);
}

void* hkTombRaiserCtor()
{
    auto* props = new ZombieTombRaiserProps();

    typedef void* (*ctorWithThisPtr)(void*);
    ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
    baseCtor(props);

    *reinterpret_cast<int*>(uintptr_t(props)) = Fga721GetActualOffset(0x23E1138);

    WillChangeGrave = 0;

    return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieTombRaiserProps::oZombieTombRaiserPropsBuildSymbols = nullptr;

void ZombieTombRaiserProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
    oZombieTombRaiserPropsBuildSymbols(builder, rclass);
    RT_CLASS_REGISTER_STRING_PROPERTY(ZombieTombRaiserProps, GraveType);
}

void ZombieTombRaiserProps::modInit()
{
    LOGI("Initializing ZombieTombRaiserProps");

    Fga721HookFunction(0xB23EB4, (void*)hkTombRaiserThrow, (void**)&oTombRaiserThrow);
    Fga721HookFunction(0xB22EF8, (void*)hkTombraiserProjectileImpact, (void**)&oTombraiserProjectileImpact);
    Fga721HookFunction(0xAA230C, (void*)hkSpawnGrave, (void**)&oSpawnGrave);

    Fga721HookFunction(0xB217CC, (void*)buildSymbols, (void**)&oZombieTombRaiserPropsBuildSymbols);
    Fga721HookFunction(0xB2167C, (void*)hkTombRaiserCtor, nullptr);
}
