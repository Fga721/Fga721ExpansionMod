#include "Zombie_CarnieMagician.h"
#include "Zombie.h"
#include <new>

typedef ZombieCarnieMagicianProps* (*GetPropsFromComponentFuncMagician)(void*);
GetPropsFromComponentFuncMagician GetPropsMagician = (GetPropsFromComponentFuncMagician)Fga721GetActualOffset(0xBF7A78);

typedef void(*MagicianConditionFunc)(void*, int64);
MagicianConditionFunc oMagicianConditionFunc = nullptr;

void hkMagicianConditionFunc(void* componentPtr, int64 condition)
{
    if (componentPtr != nullptr)
    {
        ZombieCarnieMagicianProps* props = GetPropsMagician(componentPtr);
        if (props->IsInmuneToShrink == false)
        {
            return;
        }
    }
    if (oMagicianConditionFunc != nullptr)
    {
        oMagicianConditionFunc(componentPtr, condition);
    }
}

typedef bool(*MagicianImmuneToShrink)(void*);
MagicianImmuneToShrink oMagicianImmuneToShrink = nullptr;

bool hkMagicianImmuneToShrink(void* componentPtr)
{
    if (componentPtr != nullptr)
    {
        ZombieCarnieMagicianProps* props = GetPropsMagician(componentPtr);
        if (props != nullptr)
        {
            return props->IsInmuneToShrink;
        }
    }
    return true;
}

typedef void(*MagicianInitializeFamilyImmunities)(void*, int64);
MagicianInitializeFamilyImmunities oMagicianInitializeFamilyImmunities = nullptr;

void hkMagicianInitializeFamilyImmunities(void* componentPtr, int64_t a2)
{
    if (componentPtr != nullptr)
    {
        ZombieCarnieMagicianProps* props = GetPropsMagician(componentPtr);
        if (props->IsInmuneToShrink == false)
        {
            return;
        }
    }
    if (oMagicianInitializeFamilyImmunities != nullptr)
    {
        oMagicianInitializeFamilyImmunities(componentPtr, a2);
    }
}

// las 3 funciones comprueban el valor de isinmunetoshrink para ejecutar acciones

void* hkMagicianConstruct()
{
    auto* props = new ZombieCarnieMagicianProps();

    typedef void* (*ctorWithThisPtr)(void*);
    ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
    baseCtor(props);

    *reinterpret_cast<uintptr_t*>(props) = Fga721GetActualOffset(0x2417B18);

    return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieCarnieMagicianProps::oZombieCarnieMagicianPropsBuildSymbols = nullptr;

void ZombieCarnieMagicianProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
    if (oZombieCarnieMagicianPropsBuildSymbols != nullptr)
    {
        oZombieCarnieMagicianPropsBuildSymbols(builder, rclass);
    }

    RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieCarnieMagicianProps, IsInmuneToShrink);
}

void ZombieCarnieMagicianProps::modInit()
{
    LOGI("Initializing ZombieCarnieMagicianProps");

    Fga721HookFunction(0xBF7BD4, (void*)hkMagicianConditionFunc, (void**)&oMagicianConditionFunc);
    Fga721HookFunction(0xC12B7C, (void*)hkMagicianImmuneToShrink, (void**)&oMagicianImmuneToShrink);
    Fga721HookFunction(0xBF7BEC, (void*)hkMagicianInitializeFamilyImmunities, (void**)&oMagicianInitializeFamilyImmunities);

    Fga721HookFunction(0xBF6900, (void*)hkMagicianConstruct, nullptr);
    Fga721HookFunction(0xBF6B04, (void*)buildSymbols, (void**)&oZombieCarnieMagicianPropsBuildSymbols);
}
