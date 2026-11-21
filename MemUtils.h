#pragma once
#include <unwind.h>
#include <dlfcn.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include "Logging.h"
#include <cstdint>
#include <type_traits>

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
// Get a virtual function from vftable
void* GetVirtualFunc(void* obj, int index);
// Call a function from libPVZ2.so. It supports multiple parameters, so it's very flexible and shortens the time of decompiling functions
template<typename R, typename... Args>
R CallFunc(uintptr_t funcOffset, Args... args)
{
    typedef R(*func)(Args...);
    func castedFunc = (func)Fga721GetActualOffset(funcOffset);
    return castedFunc(args...);
}
// Call a virtual function from libPVZ2.so. The vfunc index should be correct (ex: it usually should be divided by 4 in 32 bit and 8 in 64 bit)
template<typename R, typename... Args>
R CallVirtualFunc(void* obj, int index, Args... args)
{
    void* func = GetVirtualFunc(obj, index);
    auto castedFunc = reinterpret_cast<R(*)(void*, Args...)>(func);
    return castedFunc(obj, args...);
}
// Calls a func with an argument x8 (use this for func recreations)
template<typename S>
S CallFuncX8(uintptr_t funcOffset, uintptr_t arg0, uintptr_t arg1, uintptr_t arg8)
{
    uintptr_t fn = Fga721GetActualOffset(funcOffset);

    S result{};

    asm volatile(
        "mov x0, %[a0]\n"
        "mov x1, %[a1]\n"
        "mov x8, %[a8]\n"
        "blr %[fn]\n"
        "mov %[result], x0\n"
        : [result] "=&r"(result)
        : [a0] "r"(arg0),
        [a1] "r"(arg1),
        [a8] "r"(arg8),
        [fn]  "r"(fn)
        : "x0", "x1", "x8",
        "x9", "x10", "x11", "x12",
        "x13", "x14", "x15", "x16",
        "x17", "x30", "memory", "cc"
        );

    return result;
}
static inline void CallIndirectX0X8(uintptr_t function, uintptr_t arg0, void* output)
{
    asm volatile(
        "mov x0, %[arg0]\n"
        "mov x8, %[output]\n"
        "blr %[function]\n"

        :
        : [arg0] "r"(arg0),
        [output] "r"(output),
        [function] "r"(function)

        : "x0", "x1", "x2", "x3",
        "x4", "x5", "x6", "x7",
        "x8", "x9", "x10", "x11",
        "x12", "x13", "x14", "x15",
        "x16", "x17", "x30",
        "v0", "v1", "v2", "v3",
        "v4", "v5", "v6", "v7",
        "v16", "v17", "v18", "v19",
        "v20", "v21", "v22", "v23",
        "v24", "v25", "v26", "v27",
        "v28", "v29", "v30", "v31",
        "memory", "cc"
        );
}