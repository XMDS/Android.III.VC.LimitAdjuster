#include "Android_III_VC_LimitAdjuster.h"
#include <unistd.h>
#include "CLEO_SDK/cleo.h"
#include "ARMHook/patch.h"
#include "ARMHook/ARMHook.h"
#include "ARMHook/call.h"
#include "ini/inireader.h"

#ifdef __clang__
#define TARGET_ARM __attribute__((target("no-thumb-mode")))
#define TARGET_THUMB  __attribute__((target("thumb-mode")))
#endif

// naked
#ifdef __GNUC__
#define NAKED __attribute__((naked))
#else
#define NAKED __declspec(naked)
#endif

#define INIPath "/storage/emulated/0/cleo/Android_III_VC_LimitAdjuster.ini"

using namespace ARMHook;
cleo_ifs_t* cleo = nullptr;
uintptr_t LibAddr;
void (*CReplay_Display)();

uint32_t PtrNode, EntryInfoNode, Building, Object, Dummy, ColModel;
uint32_t PtrNodeSize, EntryInfoNodeSize, BuildingSize, ObjectSize, DummySize, ColModelSize;
uintptr_t ms_pPtrNodePool_0016F1A4, ms_pEntryInfoNodePool_0016F1F2, ms_pEntryInfoNodePool_0016F20A, ms_pBuildingPool_0016F2E4, 
ms_pObjectPool_0016F36E, ms_pObjectPool_0016F386, ms_pDummyPool_0016F3C4, ms_pColModelPool_0016F462;

uintptr_t _Znaj;

//void* newmen;

/*
void Android_III_VC_LimitAdjuster::SetIDELimit(unsigned int iObjectsType1)
{
	if (iObjectsType1 > 3885)
	{
		unsigned int Size = 0x68;
		unsigned int structSize = sizeof(uint32_t) + iObjectsType1 * Size;
		newmen = new char[structSize];
		memset(newmen, NULL, structSize);

		uintptr_t newmen1 = (uintptr_t)newmen;
		patch::SetPointer(LibAddr + 0xB38F0, (void*)((newmen1) -(LibAddr + 0xB36F8)));
		patch::SetPointer(LibAddr + 0xB38F4, (void*)((newmen1) - (LibAddr + 0xB3724)));
		patch::SetPointer(LibAddr + 0x1EF8E8, (void*)((newmen1) - (LibAddr + 0x1EF74C)));
		patch::SetPointer(LibAddr + 0x1EF90C, (void*)((newmen1)- (LibAddr + 0x1EF8B4)));
		patch::SetPointer(LibAddr + 0x1EFA88, (void*)((newmen1) - (LibAddr + 0x1EFA4E)));
		patch::SetPointer(LibAddr + 0x1EFC40, (void*)((newmen1)- (LibAddr + 0x1EFAC8)));
		cleo->PrintToCleoLog("'Android_III_VC_LimitAdjuster' 233333332");
	}
}*/

static TARGET_THUMB NAKED void Pools_Initialise_0016F176()
{
	__asm(
	".thumb\n"
		".hidden PtrNodeSize\n"
		".hidden PtrNode\n"
		".hidden ms_pPtrNodePool_0016F1A4\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, PtrNodeSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, PtrNode)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, PtrNode)
		"MOV R6, R2\n"
		"MOVS R3, #0\n"
		"STR R2, [R5,#8]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		"MOV.W R0, #0xFFFFFFFF\n"
		"STR R0, [R5, #0xC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pPtrNodePool_0016F1A4)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetPtrNodePoolLimit(unsigned int nPtrNode)
{
	if (nPtrNode > 50000)
	{
		PtrNodeSize = nPtrNode * 0xC;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pPtrNodePool_0016F1A4 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F1A4);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F176, (void*)&Pools_Initialise_0016F176);
	}
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F1CA()
{
	__asm(
	".thumb\n"
		".hidden EntryInfoNodeSize\n"
		".hidden EntryInfoNode\n"
		".hidden ms_pEntryInfoNodePool_0016F1F2\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, EntryInfoNodeSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, EntryInfoNode)
		"BL 1f\n"
		"MOV.W R2, #0xFFFFFFFF\n"
		"MOVS R3, #0\n"
		"STR R2, [R5, #0xC]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, EntryInfoNode)
		"STR R0, [R5, #8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pEntryInfoNodePool_0016F1F2)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F1FE()
{
	__asm(
	".thumb\n"
		".hidden EntryInfoNode\n"
		".hidden ms_pEntryInfoNodePool_0016F20A\n"
		"BIC.W R2, R2, #0x7F\n"
		"STRB R2, [R1,R3]\n"
		"ADDS R3, #1\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, EntryInfoNode)
		"CMP R3, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pEntryInfoNodePool_0016F20A)
		);
}

void Android_III_VC_LimitAdjuster::SetEntryInfoNodePoolLimit(unsigned int nEntryInfoNode)
{
	if (nEntryInfoNode > 3200)
	{
		EntryInfoNodeSize = nEntryInfoNode * 0x14;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pEntryInfoNodePool_0016F1F2 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F1F2);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F1CA, (void*)&Pools_Initialise_0016F1CA);

		ms_pEntryInfoNodePool_0016F20A = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F20A);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F1FE, (void*)&Pools_Initialise_0016F1FE);
	}
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F2B6()
{
	__asm(
	".thumb\n"
		".hidden BuildingSize\n"
		".hidden Building\n"
		".hidden ms_pBuildingPool_0016F2E4\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, BuildingSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Building)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, Building)
		"MOV R6, R2\n"
		"MOVS R3, #0\n"
		"STR R2, [R5,#8]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		"MOV.W R0, #0xFFFFFFFF\n"
		"STR R0, [R5, #0xC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pBuildingPool_0016F2E4)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetBuildingPoolLimit(unsigned int nBuilding)
{
	if (nBuilding > 7000)
	{
		BuildingSize = nBuilding * 0x68;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pBuildingPool_0016F2E4 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F2E4);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F2B6, (void*)&Pools_Initialise_0016F2B6);
	}
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F346()
{
	__asm(
	".thumb\n"
		".hidden ObjectSize\n"
		".hidden Object\n"
		".hidden ms_pObjectPool_0016F36E\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, ObjectSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Object)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, Object)
		"MOVS R3, #0\n"
		"STR R6, [R5, #0xC]\n"
		"STR R2, [R5, #8]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pObjectPool_0016F36E)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F37A()
{
	__asm(
	".thumb\n"
		".hidden Object\n"
		".hidden ms_pObjectPool_0016F386\n"
		"BIC.W R2, R2, #0x7F\n"
		"STRB R2, [R1,R3]\n"
		"ADDS R3, #1\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, Object)
		"CMP R3, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pObjectPool_0016F386)
		);
}

void Android_III_VC_LimitAdjuster::SetObjectPoolLimit(unsigned int nObject)
{
	if (nObject > 510)
	{
		ObjectSize = nObject * 0x1A4;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pObjectPool_0016F36E = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F36E);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F346, (void*)&Pools_Initialise_0016F346);

		ms_pObjectPool_0016F386 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F386);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F37A, (void*)&Pools_Initialise_0016F37A);
	}
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F396()
{
	__asm(
	".thumb\n"
		".hidden DummySize\n"
		".hidden Dummy\n"
		".hidden ms_pDummyPool_0016F3C4\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, DummySize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Dummy)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, Dummy)
		"MOV R6, R2\n"
		"MOVS R3, #0\n"
		"STR R2, [R5,#8]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		"MOV.W R0, #0xFFFFFFFF\n"
		"STR R0, [R5, #0xC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pDummyPool_0016F3C4)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetDummyPoolLimit(unsigned int nDummy)
{
	if (nDummy > 2340)
	{
		DummySize = nDummy * 0x6C;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pDummyPool_0016F3C4 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F3C4);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F396, (void*)&Pools_Initialise_0016F396);
	}
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F434()
{
	__asm(
	".thumb\n"
		".hidden ColModelSize\n"
		".hidden ColModel\n"
		".hidden ms_pColModelPool_0016F462\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, ColModelSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, ColModel)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, ColModel)
		"MOV R6, R2\n"
		"MOVS R3, #0\n"
		"STR R2, [R5,#8]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		"MOV.W R0, #0xFFFFFFFF\n"
		"STR R0, [R5, #0xC]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pColModelPool_0016F462)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetColModelPoolLimit(unsigned int nColModel)
{
	if (nColModel > 4400)
	{
		ColModelSize = nColModel * 0x4C;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pColModelPool_0016F462 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F462);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F434, (void*)&Pools_Initialise_0016F434);
	}
}

void MyDrawingEvent()
{
	call::Function<void>((uintptr_t)cleo->GetMainLibrarySymbol("_Z16PrintMemoryUsagev"));
	return CReplay_Display();
}

extern "C" __attribute__((visibility("default"))) void plugin_init(cleo_ifs_t * ifs)
{
	cleo = ifs;
	cleo->PrintToCleoLog("'Android_III_VC_LimitAdjuster' init!!!");
	LibAddr = (uintptr_t)cleo->GetMainLibraryLoadAddress();

	cleo->PrintToCleoLog("load 'Android_III_VC_LimitAdjuster.ini'");
	inireader.SetIniPath(INIPath);
	if (inireader.ReadBoolean("LimitAdjuster", "Enable", 0))
	{
		if (inireader.ReadBoolean("LimitAdjuster", "Text", 0))
		{
			patch::SetUint8(LibAddr + 0x0014E50C + 2, 0x22); //PtrNode
			patch::SetUint8(LibAddr + 0x0014E558 + 2, 0x40); //EntryInfoNode
			patch::SetUint8(LibAddr + 0x0014E5A4 + 2, 0x5E); //Ped
			patch::SetUint8(LibAddr + 0x0014E5F0 + 2, 0x7C); //Vehicle
			patch::SetUint8(LibAddr + 0x0014E63C + 2, 0x9A); //Building
			patch::SetUint8(LibAddr + 0x0014E688 + 2, 0xB8); //Treadable
			patch::SetUint8(LibAddr + 0x0014E6D4 + 2, 0xD6); //Object
			patch::SetUint8(LibAddr + 0x0014E71E + 2, 0xF4); //Dummy
			patch::SetUint16(LibAddr + 0x0014E768 + 2, 0x4101); //ColModel
			patch::SetUint16(LibAddr + 0x0014E7B0 + 2, 0x4109); //AudioScriptObjects
			hook::HookInternal(cleo->GetMainLibrarySymbol("_ZN7CReplay7DisplayEv"), (void*)MyDrawingEvent, (void**)&CReplay_Display);
		}
		PtrNode = inireader.ReadInteger("PoolLimit", "PtrNode", 50000);
		EntryInfoNode = inireader.ReadInteger("PoolLimit", "EntryInfoNode", 3200);
		Building = inireader.ReadInteger("PoolLimit", "Building", 7000);
		Object = inireader.ReadInteger("PoolLimit", "Object", 510);
		Dummy = inireader.ReadInteger("PoolLimit", "Dummy", 2340);
		ColModel = inireader.ReadInteger("PoolLimit", "ColModel", 4400);

		LimitAdjuster.SetPtrNodePoolLimit(PtrNode);
		LimitAdjuster.SetEntryInfoNodePoolLimit(EntryInfoNode);
		LimitAdjuster.SetBuildingPoolLimit(Building);
		LimitAdjuster.SetObjectPoolLimit(Object);
		LimitAdjuster.SetDummyPoolLimit(Dummy);
		LimitAdjuster.SetColModelPoolLimit(ColModel);
	}
}

