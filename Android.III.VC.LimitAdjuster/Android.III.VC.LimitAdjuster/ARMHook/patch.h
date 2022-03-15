#pragma once
#include "Assembly/UsefulMacros.h"
#include "Assembly/eInstructionSet.h"
#include <stdint.h>
#include <vector>

namespace ARMHook
{
	class patch
	{
	public:
		static void WriteMemoryData(uintptr_t addr, void* data, int size);
		static void SetUint8(uintptr_t addr, uint8_t value);
		static void SetUint16(uintptr_t addr, uint16_t value);
		static void SetUint32(uintptr_t addr, uint32_t value);
		static void SetPointer(uintptr_t addr, void* value);
		static void SetFloat(uintptr_t addr, float value);
		static void NOPinstructions(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, int iSize);
		static void RedirectCodeEx(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, uintptr_t to);
		static void RedirectCodeEx(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, const void* to);
		static void RedirectFunction(uintptr_t functionJumpAddress, void* to);
		static void DisableFunctionByName(const char* name);
	};
}