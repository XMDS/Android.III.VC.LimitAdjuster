#include "patch.h"
#include "ARMHook.h"
#include <unistd.h>

namespace ARMHook
{
	void patch::WriteMemoryData(uintptr_t addr, void* data, int size)
	{
		hook::WriteMemory((void*)addr, data, size);
	}

	void patch::SetUint8(uintptr_t addr, uint8_t value)
	{
		hook::WriteMemory((void*)addr, &value, sizeof(value));
	}

	void patch::SetUint16(uintptr_t addr, uint16_t value)
	{
		hook::WriteMemory((void*)addr, &value, sizeof(value));
	}

	void patch::SetUint32(uintptr_t addr, uint32_t value)
	{
		hook::WriteMemory((void*)addr, &value, sizeof(value));
	}

	void patch::SetPointer(uintptr_t addr, void* value)
	{
		hook::WriteMemory((void*)addr, &value, sizeof(value));
	}

	void patch::SetFloat(uintptr_t addr, float value)
	{
		hook::WriteMemory((void*)addr, &value, sizeof(value));
	}

	//by fastamn92
	void patch::NOPinstructions(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, int iSize)
	{
		hook::unprotect(dwAddress, iSize);
		if (sourceInstructionSet == INSTRUCTION_SET_THUMB)
		{
			for (int i = 0; i < iSize; i += 2)
			{
				*((unsigned char*)dwAddress + i + 0) = 0x00;
				*((unsigned char*)dwAddress + i + 1) = 0xBF;
			}
		}
		else if (sourceInstructionSet == INSTRUCTION_SET_ARM)
		{
			for (int i = 0; i < iSize; i += 4)
			{
				*((unsigned char*)dwAddress + i + 0) = 0x00;
				*((unsigned char*)dwAddress + i + 1) = 0xF0;
				*((unsigned char*)dwAddress + i + 2) = 0x20;
				*((unsigned char*)dwAddress + i + 3) = 0xE3;
			}
		}
	}

	void patch::RedirectCodeEx(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, uintptr_t to)
	{
		return RedirectCodeEx(sourceInstructionSet, dwAddress, (const void*)to);
	}

	//by fastamn92
	void patch::RedirectCodeEx(eInstructionSet sourceInstructionSet, uintptr_t dwAddress, const void* to)
	{
		// Thumb trampoline may take 8 bytes (if address is aligned to value of 4) or 10 bytes.
		if (sourceInstructionSet == INSTRUCTION_SET_THUMB)
		{
			char code[12];
			unsigned int sizeOfData = 0;

			if (dwAddress % 4 == 0)
			{
				*(uint32_t*)(code + 0) = 0xF000F8DF;	// // LDR.W             R0, [PC, #0]
				*(const void**)(code + 4) = to;	// pointer, where to jump
				sizeOfData = 8;
			}
			else
			{
				*(uint32_t*)(code + 0) = 0xBF00;	// NOP
				*(uint32_t*)(code + 2) = 0xF000F8DF;	// // LDR.W             R0, [PC, #0]

				*(const void**)(code + 6) = to;	// pointer, where to jump
				sizeOfData = 10;
			}

			WriteMemoryData(dwAddress, code, sizeOfData);
		}
		else if (sourceInstructionSet == INSTRUCTION_SET_ARM)
		{
			char code[8];

			*(uint32_t*)(code + 0) = 0xE51FF004;	// // LDR             R0, [PC, #0]
			*(const void**)(code + 4) = to;	// pointer, where to jump
			WriteMemoryData(dwAddress, code, sizeof(code));
		}
	}

	void patch::RedirectFunction(uintptr_t functionJumpAddress, void* to)
	{
		RedirectCodeEx(
			GET_INSTRUCTION_SET_FROM_ADDRESS(functionJumpAddress),
			GET_CODE_START(functionJumpAddress),
			to
		);
	}

	/*
	void CPatch::DisableFunctionByName(const char* name)
	{
		uintptr_t address = (uintptr_t)dlsym(NULL, name);
		if (!address)
			return;

		if (address % 2)	// is THUMB?
		{
			address = address & (~1);
			CPatch::PatchUINT16(address, 0x4770);	// BX LR
		}
	}*/
}
