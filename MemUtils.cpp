#include "MemUtils.h"
#include "Logging.h"

#include "And64InlineHook.hpp"

uintptr_t g_libAddress = 0;

uintptr_t Fga721GetLibraryAddress(const char* libName) {
    FILE* fp = fopen("/proc/self/maps", "rt");
    if (fp == NULL) {
        perror("fopen");
        return 0;
    }

    uintptr_t addr = 0;
    char line[1024];

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, libName) != NULL) {
            addr = strtoul(line, NULL, 16);
            break;
        }
    }

    fclose(fp);
    return addr;
}

uintptr_t Fga721GetActualOffset(uintptr_t offset)
{
    if (g_libAddress == 0)
    {
        g_libAddress = Fga721GetLibraryAddress("libPVZ2.so");
    }
    return g_libAddress + offset;
}

void Fga721HookFunction(uintptr_t offset, void* replace, void** result)
{
    A64HookFunction((void*)Fga721GetActualOffset(offset), replace, result);
}

void* CopyVFTable(uintptr_t vftableAddr, int64_t numVFuncs)
{
    int64_t size = numVFuncs * sizeof(int64_t);
    void* vftableCopy = malloc(size);
    memcpy(vftableCopy, (const void*)vftableAddr, size);
    return vftableCopy;
}

void CopyVFTable(void* dest, intptr_t vftableAddr, int64_t numVFuncsToCopy)
{
    int64_t size = numVFuncsToCopy * sizeof(int64_t);
    memcpy(dest, (const void*)vftableAddr, size);
}

void PatchVFTable(void* vftable, void* funcAddr, int64_t index)
{
    ((reinterpret_cast<void**>(vftable))[index]) = funcAddr;
}

void SetVFTable(void* obj, uintptr_t newVftablePtr)
{
    *reinterpret_cast<int64_t*>(uintptr_t(obj)) = newVftablePtr;
}