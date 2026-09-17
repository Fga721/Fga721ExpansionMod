#pragma once
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include "Logging.h"

extern uintptr_t g_libAddress;
// Get base address of a library (.so) loaded in memory.
uintptr_t Fga721GetLibraryAddress(const char* libName);
// Get actual offset of address inside libPVZ2.so
uintptr_t Fga721GetActualOffset(uintptr_t offset);
// Hook a function in libPVZ2
void Fga721HookFunction(uintptr_t offset, void* replace, void** result);
// Copy vftable from memory
void* CopyVFTable(uintptr_t vftableAddr, int64_t numVFuncs);
// Copy vftable from memory with destination
void CopyVFTable(void* dest, intptr_t vftableAddr, int64_t numVFuncsToCopy);
// Patch a virtual function without the need to hook it
void PatchVFTable(void* vftable, void* funcAddr, int64_t index);
// Set an RtClass to the vftable in a ctor
void SetVFTable(void* obj, uintptr_t newVftablePtr);
// Call a function from libPVZ2.so. It supports multiple parameters, so it's very flexible and shortens the time of decompiling functions
template<typename R, typename... Args>
R CallFunc(uintptr_t funcOffset, Args... args)
{
    typedef R(*func)(Args...);
    func castedFunc = (func)Fga721GetActualOffset(funcOffset);
    return castedFunc(args...);
}