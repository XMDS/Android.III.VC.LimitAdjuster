#pragma once
#include <vector>
#include <sys/mman.h>

struct bytePattern
{
	struct byteEntry
	{
		uint8_t nValue;
		bool bUnknown;
	};
	std::vector<byteEntry> vBytes;
};

enum call_mode
{
	BL = 0,
	BLX = 1
};

namespace ARMHook
{
	class hook
	{
	public:
		static uintptr_t GetLibraryAddress(const char* library);
		static uintptr_t GetLibraryLength(const char* library);
		static const char* GetLibraryFileName(uintptr_t LibAddr);
		static uintptr_t GetSymbolAddress(void* handle, const char* name);
		static uintptr_t GetSymbolAddress(uintptr_t LibAddr, const char* name);
		static int unprotect(uintptr_t addr, size_t len);
		static void WriteMemory(void* addr, void* data, size_t size);
		static void* ReadMemory(void* addr, void* data, size_t size);
		static void HookPLTInternal(void* addr, void* func, void** original);
		static bool HookInternal(void* addr, void* func, void** original);
		static uintptr_t GetAddressFromPatter(const char* pattern, const char* library);

		static uintptr_t InitialiseTrampolines(uintptr_t addr, size_t size);
		static void ReplaceThumbCall(uintptr_t addr, uintptr_t func);
		static void ReplaceArmCall(uintptr_t addr, uintptr_t func);
		static void HookThumbFunc(void* func, uint32_t startSize, void* func_to, void** func_orig);
		static void HookArmFunc(void* func, uint32_t startSize, void* func_to, void** func_orig);
		static uintptr_t GetThumbCallAddr(uintptr_t addr, call_mode mode);
	};	
}