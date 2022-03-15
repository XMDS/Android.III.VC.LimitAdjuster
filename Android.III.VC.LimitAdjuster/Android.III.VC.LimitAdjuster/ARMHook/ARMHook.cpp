#include "ARMHook.h"
#include <android/log.h>
#include <dlfcn.h>
#include <ctype.h>
#include <unistd.h>

#pragma comment (lib, "libsubstrate-armv7a_Cydia.a")

extern "C" bool MSHookFunction(void* symbol, void* replace, void** result);

#define HOOK_PROC_THUMB "\x01\xB4\x01\xB4\x01\x48\x01\x90\x01\xBD\x00\xBF\x00\x00\x00\x00"
/*
push{ r0 }
push{ r0 }
ldr r0, [pc, #4]
str r0, [sp, #4]
pop{ r0, pc }
nop
func
*/
#define HOOK_PROC_ARM "\x04\xF0\x1F\xE5\x00\x00\x00\x00" //ldr pc, [pc, #-4] func

uintptr_t hook_addr_start = 0;
uintptr_t hook_addr_end = 0;
uintptr_t arm_mmap_start = 0;
uintptr_t arm_mmap_end = 0;

namespace ARMHook
{
    uintptr_t hook::GetLibraryAddress(const char* library)
    {
        char filename[0xFF] = { 0 }, buffer[2048] = { 0 };
        FILE* fp = 0;
        uintptr_t address = 0;

        fp = fopen("/proc/self/maps", "rt");
        if (fp != NULL)
        {
            while (fgets(buffer, sizeof(buffer), fp))
            {
                if (strstr(buffer, library))
                {
                    address = (uintptr_t)strtoul(buffer, 0, 16);
                    break;
                }
            }
            fclose(fp);
        }
        return address;
    }

    uintptr_t hook::GetLibraryLength(const char* library)
    {
        char filename[0xFF] = {0}, buffer[2048] = {0};
        FILE* fp = 0;
        uintptr_t address = 0;

        fp = fopen("/proc/self/maps", "rt");
        if (fp != NULL)
        {
            while (fgets(buffer, sizeof(buffer), fp))
            {
                if (strstr(buffer, library))
                {
                    address = (uintptr_t)strtoul(buffer, 0, 16);
                    address = (uintptr_t)strtoul(&buffer[9], 0, 16) - address;
                    break;
                }
            }
            fclose(fp);
        }
        return address;
    }

    const char* hook::GetLibraryFileName(uintptr_t LibAddr)
    {
        Dl_info info;
        if (dladdr((void*)LibAddr, &info) == 0)
            return NULL;
        return info.dli_fname;
    }
    
    uintptr_t hook::GetSymbolAddress(void* handle, const char* name)
    {
        return (uintptr_t)dlsym(handle, name);
    }

    uintptr_t hook::GetSymbolAddress(uintptr_t LibAddr, const char* name)
    {
        Dl_info info;
        if (dladdr((void*)LibAddr, &info) == 0)
            return 0;
        return (uintptr_t)dlsym(info.dli_fbase, name);
    }
    
    int hook::unprotect(uintptr_t addr, size_t len)
    {
        return mprotect((void*)(addr & 0xFFFFF000), len, PROT_READ | PROT_WRITE | PROT_EXEC);
    }

    void hook::WriteMemory(void* addr, void* data, size_t size)
    {
        unprotect((uintptr_t)addr, size);
        memcpy(addr, data, size);
        cacheflush((uintptr_t)addr, (uintptr_t)data + size, 0);
    }

    void* hook::ReadMemory(void* addr, void* data, size_t size)
    {
        unprotect((uintptr_t)addr, size);
        memcpy(data, addr, size);
        return data;
    }

    void hook::HookPLTInternal(void* addr, void* func, void** original)
    {
        if (addr == NULL || func == NULL)
            return;
        unprotect((uintptr_t)addr, 4);
        if (original != NULL)
            *((uintptr_t*)original) = *(uintptr_t*)addr;
        *(uintptr_t*)addr = (uintptr_t)func;
    }
    
    bool hook::HookInternal(void* addr, void* func, void** original)
    {
        if (addr == NULL || func == NULL) 
            return false;
        unprotect((uintptr_t)addr, PAGE_SIZE);
        return MSHookFunction(addr, func, original);
    }

    bool compareData(const uint8_t* data, const bytePattern::byteEntry* pattern, size_t patternlength)
    {
        int index = 0;
        for (size_t i = 0; i < patternlength; i++)
        {
            auto byte = *pattern;
            if (!byte.bUnknown && *data != byte.nValue) 
                return false;

            ++data;
            ++pattern;
            ++index;
        }
        return index == patternlength;
    }

    uintptr_t hook::GetAddressFromPatter(const char* pattern, const char* library)
    {
        bytePattern ret;
        const char* input = &pattern[0];
        while (*input)
        {
            bytePattern::byteEntry entry;
            if (isspace(*input)) ++input;
            if (isxdigit(*input))
            {
                entry.bUnknown = false;
                entry.nValue = (uint8_t)std::strtol(input, NULL, 16);
                input += 2;
            }
            else
            {
                entry.bUnknown = true;
                input += 2;
            }
            ret.vBytes.emplace_back(entry);
        }

        auto patternstart = ret.vBytes.data();
        auto length = ret.vBytes.size();

        uintptr_t pMemoryBase = GetLibraryAddress(library);
        size_t nMemorySize = GetLibraryLength(library) - length;

        for (size_t i = 0; i < nMemorySize; i++)
        {
            uintptr_t addr = pMemoryBase + i;
            if (compareData((const uint8_t*)addr, patternstart, length)) 
                return addr;
        }
        return 0;
    }

    uintptr_t hook::InitialiseTrampolines(uintptr_t addr, size_t size)
    {
        hook_addr_start = addr;
        hook_addr_end = hook_addr_start + size;

        arm_mmap_start = (uintptr_t)mmap(0, PAGE_SIZE, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        mprotect((void*)(arm_mmap_start & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_EXEC | PROT_WRITE);
        arm_mmap_end = arm_mmap_start + PAGE_SIZE;
        return  arm_mmap_end;
    }

    void CheckMemorySpaceLimit()
    {
        if (hook_addr_end < (hook_addr_start + 0x10) || arm_mmap_end < (arm_mmap_start + 0x20))
        {
            __android_log_write(ANDROID_LOG_ERROR, "ARMHook", "Error!!! Space limit reached.");
            exit(1);
        }
    }

    void hook::ReplaceThumbCall(uintptr_t addr, uintptr_t func)
    {
        CheckMemorySpaceLimit();
        addr &= ~1;
        uint32_t hex = ((hook_addr_start - addr - 4) >> 12) & 0x7FF | 0xF000 | ((((hook_addr_start - addr - 4) >> 1) & 0x7FF | 0xF800) << 16);
        WriteMemory((void*)addr, &hex, 4);
        uintptr_t local = hook_addr_start & ~1;
        char code[16];
        memcpy(code, HOOK_PROC_THUMB, 16);
        *(uint32_t*)&code[12] = (func | 1);
        WriteMemory((void*)local, code, 16);
        unprotect(hook_addr_start, 16);
        hook_addr_start += 16;
    }

    void hook::ReplaceArmCall(uintptr_t addr, uintptr_t func)
    {
        CheckMemorySpaceLimit();
        uintptr_t a = hook_addr_start - addr;
        uintptr_t b = a - 1;
        uintptr_t c = a - 4;
        if (c >= 0)
            b = c;
        uint32_t hex = ((b >> 2) - 1) & 0xFFFFFF | 0xEB000000;
        WriteMemory((void*)addr, &hex, 4);
        char code[8];
        memcpy(code, HOOK_PROC_ARM, 8);
        *(uint32_t*)&code[4] = (func | 1);
        WriteMemory((void*)hook_addr_start, code, 8);
        hook_addr_start += 16;
    }

    void hook::HookThumbFunc(void* func, uint32_t startSize, void* func_to, void** func_orig)
    {
        CheckMemorySpaceLimit();
        uintptr_t addr = (uintptr_t)func & ~1;
        uintptr_t start = arm_mmap_start;
        WriteMemory((void*)arm_mmap_start, (void*)addr, startSize);
        if (startSize << 30)
            *(uint32_t*)(start + startSize) = 18112;
        uintptr_t size = start + startSize;
        if (startSize << 30)
            size += 2;
        char code[16];
        memcpy(code, HOOK_PROC_THUMB, 16);
        *(uint32_t*)&code[12] = ((addr + startSize) | 1);
        WriteMemory((void*)(size & ~1), code, 16);
        *func_orig = (void*)(arm_mmap_start + 1);
        arm_mmap_start += 32;
        addr &= ~1;
        uint32_t hex = ((hook_addr_start - addr - 4) >> 12) & 0x7FF | 0xF000 | ((((hook_addr_start - addr - 4) >> 1) & 0x7FF | 0xB800) << 16);
        WriteMemory((void*)addr, &hex, 4);
        char code2[16];
        memcpy(code2, HOOK_PROC_THUMB, 16);
        *(uint32_t*)&code2[12] = ((uintptr_t)func_to | 1);
        WriteMemory((void*)(hook_addr_start & ~1), code2, 16);
        hook_addr_start += 16;
    }

    void hook::HookArmFunc(void* func, uint32_t startSize, void* func_to, void** func_orig)
    {
        CheckMemorySpaceLimit();
        uintptr_t start = arm_mmap_start;
        WriteMemory((void*)arm_mmap_start, func, startSize);
        if (startSize << 30)
            *(uint32_t*)(start + startSize) = 18112;
        uintptr_t size = start + startSize;
        if (startSize << 30)
            size += 2;
        char code[8];
        memcpy(code, HOOK_PROC_ARM, 8);
        *(uint32_t*)&code[4] = ((uintptr_t)func + startSize) & ~1;
        WriteMemory((void*)size, code, 8);
        *func_orig = (void*)arm_mmap_start;
        arm_mmap_start += 32;
        uintptr_t a = hook_addr_start - (uintptr_t)func;
        uintptr_t b = a - 1;
        uintptr_t c = a - 4;
        if (c >= 0)
            b = c;
        uint32_t hex = ((b >> 2) - 1) & 0xFFFFFF | 0xEA000000;
        WriteMemory(func, &hex, 4);
        char code2[8];
        memcpy(code2, HOOK_PROC_ARM, 8);
        *(uint32_t*)&code2[4] = ((uintptr_t)func_to | 1);
        WriteMemory((void*)hook_addr_start, code2, 8);
        hook_addr_start += 16;
    }

    uintptr_t hook::GetThumbCallAddr(uintptr_t addr, call_mode mode)
    {
        uint16_t high, low;
        ReadMemory((void*)addr, &high, 2);
        ReadMemory((void*)(addr + 2), &low, 2);
        high &= 0x7FF;
        low &= 0x7FF;
        int32_t off = ((high << 12) | (low << 1));
        if (!(off & 0x80000000))
        {
            off = ~(off - 1);
            off &= 0x7FFFFF;
            if (mode)
            {
                if (addr % 4 == 0)
                    return addr + 4 - off;
                else
                    return addr + 2 - off;
            }
            return addr + 4 - off;
        }
        off &= 0x7FFFFF;
        if (mode)
        {
            if (addr % 4 == 0)
                return addr + 4 + off;
            else
                return addr + 2 + off;
        }
        return addr + 4 + off;
    }
}
