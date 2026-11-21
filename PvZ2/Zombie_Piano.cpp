#include "Zombie_Piano.h"
#include "Zombie.h"
#include "new"

typedef bool (*initZombiePianoList)(int64, int64);
initZombiePianoList oInitZombiePianoList = NULL;

std::vector<SexyString>* g_pianoList = NULL;
bool g_pianoListInitialized = false;

bool hkInitZombiePianoList(int64 a1, int64 a2)
{
    bool result = oInitZombiePianoList(a1, a2);

    if (!g_pianoListInitialized)
    {
        g_pianoList = reinterpret_cast<std::vector<SexyString>*>(Fga721GetActualOffset(0x2581BD0));

        g_pianoList->clear();
        g_pianoList->push_back(SexyString("cowboy"));
        g_pianoList->push_back(SexyString("cowboy_armor1"));
        g_pianoList->push_back(SexyString("cowboy_armor2"));
        g_pianoList->push_back(SexyString("cowboy_armor4"));
        g_pianoListInitialized = true;
    }

    return result;
} // no pude hacer un softcode del piano, porque no habia un self definido; aca esta todo anyways


void* hkPianoConstruct()
{
    auto* props = new ZombiePianoProps();

    typedef void* (*ctorWithThisPtr)(void*);
    ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
    baseCtor(props);

    *reinterpret_cast<uintptr_t*>(props) = Fga721GetActualOffset(0x24332C8);

    g_pianoListInitialized = false;

    return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombiePianoProps::oZombiePianoPropsBuildSymbols = nullptr;

void ZombiePianoProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
    if (oZombiePianoPropsBuildSymbols != nullptr)
    {
        oZombiePianoPropsBuildSymbols(builder, rclass);
    }
}

void ZombiePianoProps::modInit()
{
    LOGI("Initializing ZombiePianoProps");
    Fga721HookFunction(0xC1D1FC, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList);

    Fga721HookFunction(0xDAF9E8, (void*)hkPianoConstruct, nullptr);
    Fga721HookFunction(0xDAFB44, (void*)buildSymbols, (void**)oZombiePianoPropsBuildSymbols);
}
