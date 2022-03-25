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

uint32_t PtrNode, EntryInfoNode, Ped, Vehicle, Building, Treadable, Object, Dummy, AudioScriptObject, ColModel;
uint32_t PtrNodeSize, EntryInfoNodeSize, PedSize, VehicleSize, BuildingSize, TreadableSize, ObjectSize, DummySize, AudioScriptObjectSize, ColModelSize;
uintptr_t ms_pPtrNodePool_0016F1A4, ms_pEntryInfoNodePool_0016F1F2, ms_pEntryInfoNodePool_0016F20A, ms_pPedPool_0016F242, ms_pPedPool_0016F258, 
ms_pVehiclePool_0016F290, ms_pVehiclePool_0016F2A6, ms_pBuildingPool_0016F2E4, ms_pTreadablePool_0016F31C, ms_pObjectPool_0016F36E,
ms_pObjectPool_0016F386, ms_pDummyPool_0016F3C4, ms_pAudioScriptObjectPool_0016F40E, ms_pAudioScriptObjectPool_0016F424, ms_pColModelPool_0016F462;

uintptr_t _Znaj;

float WorldMaxX, WorldMaxY, WorldMinX, WorldMinY;
uintptr_t CTheZones_Init_00189834, CTheZones_Init_00189946;

void *ObjsPtr, *TobjPtr, *WeaponPtr, *VehiclesPtr, *PedPtr, *__2dfxPtr;
uintptr_t CBaseModelInfo_CBaseModelInfo = 0;
uintptr_t CVehicleModelInfo_CVehicleModelInfo = 0;

void* _ZN10CModelInfo16ms_modelInfoPtrsE, *_ZN10CModelInfo18ms_modelInfoHashesE, *_ZN10CStreaming16ms_aInfoForModelE;
uintptr_t CModelInfo_GetModelInfo_001EF95C, CTimeModelInfo_FindOtherTimeModel_001FDE2E, CTimeModelInfo_FindOtherTimeModel_001FDE82,
CTimeModelInfo_FindOtherTimeModel_001FDE74, CGame_ShutDownForRestart_0020D18A, CGame_ShutDownForRestart_0020D1A4;
uint32_t ID;

uintptr_t CVisibilityPlugins_Initialise_00215AFE, CVisibilityPlugins_Initialise_00215B58, CVisibilityPlugins_Initialise_00215A4A, CVisibilityPlugins_Initialise_00215AA4;
uint32_t AlphaEntityList, AlphaEntityListSub, AlphaUnderwaterEntityList, AlphaUnderwaterEntityListSub,
AlphaList, AlphaListSub, AlphaBoatAtomicList, AlphaBoatAtomicListSub;

void* gImgFiles, * gImg;
void* VisibleEntityPtrs;

static void InitialiseStoreCBaseModelInfo(void* Memptr, unsigned int numberOfElements, unsigned int elementSize, void (*func)(char* pObject), Android_III_VC_LimitAdjuster::eLimitType type)
{
	if (type == Android_III_VC_LimitAdjuster::eLimitType::objs)
	{
		for (unsigned int i = 0; i < numberOfElements; i++)
		{
			char* pObject = (char*)Memptr + 0x840 + i * elementSize;
			call::Method<void, char*, int>(CBaseModelInfo_CBaseModelInfo, pObject, 1);
			func(pObject);
		}
	}
	else if (type == Android_III_VC_LimitAdjuster::eLimitType::tobj)
	{
		for (unsigned int i = 0; i < numberOfElements; i++)
		{
			char* pObject = (char*)Memptr + 0x874 + i * elementSize;
			call::Method<void, char*, int>(CBaseModelInfo_CBaseModelInfo, pObject, 3);
			func(pObject);
		}
	}
	else if (type == Android_III_VC_LimitAdjuster::eLimitType::weapon)
	{
		for (unsigned int i = 0; i < numberOfElements; i++)
		{
			char* pObject = (char*)Memptr + 0xD3C + i * elementSize;
			call::Method<void, char*, int>(CBaseModelInfo_CBaseModelInfo, pObject, 4);
			func(pObject);
		}
	}
	else if (type == Android_III_VC_LimitAdjuster::hier)
	{
		for (unsigned int i = 0; i < numberOfElements; i++)
		{
			char* pObject = (char*)Memptr + 0xBE0 + i * elementSize;
			call::Method<void, char*, int>(CBaseModelInfo_CBaseModelInfo, pObject, 5);
			func(pObject);
		}
	}
	else if (type == Android_III_VC_LimitAdjuster::eLimitType::vehicles)
	{
		for (unsigned int i = 0; i < numberOfElements; i++)
		{
			char* pObject = (char*)Memptr + 0xD8C + i * elementSize;
			call::Method<void>(CVehicleModelInfo_CVehicleModelInfo, pObject);
		}	
	}
	else if (type == Android_III_VC_LimitAdjuster::eLimitType::ped)
	{
		for (unsigned int i = 0; i < numberOfElements; i++)
		{
			char* pObject = (char*)Memptr + 0x238 + i * elementSize;
			call::Method<void, char*, int>(CBaseModelInfo_CBaseModelInfo, pObject, 7);
			func(pObject);
		}
	}
}

static TARGET_THUMB NAKED void CModelInfo_GetModelInfo_001EF94C()
{
	__asm(
	".thumb\n"
		".hidden CModelInfo_GetModelInfo_001EF95C\n"
		".hidden ID\n"
		"ADDS R7, #1\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, ID)
		"CMP R7, R3\n"
		"ADD.W R6, R6, #4\n"
		"ADD.W R8, R8, #4\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CModelInfo_GetModelInfo_001EF95C)
		);
}

static TARGET_THUMB NAKED void CTimeModelInfo_FindOtherTimeModel_001FDE24()
{
	__asm(
	".thumb\n"
		".hidden CTimeModelInfo_FindOtherTimeModel_001FDE2E\n"
		".hidden ID\n"
		"MOVS R6, #0\n"
		"LDRB.W R12, [SP]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(LR, ID)
		
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CTimeModelInfo_FindOtherTimeModel_001FDE2E)
		);
}

static TARGET_THUMB NAKED void CTimeModelInfo_FindOtherTimeModel_001FDE68()
{
	__asm(
	".thumb\n"
		".hidden CTimeModelInfo_FindOtherTimeModel_001FDE82\n"
		".hidden CTimeModelInfo_FindOtherTimeModel_001FDE74\n"
		".hidden ID\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, ID)
		"CMP R6, R3\n"
		"BEQ 2f\n"
		"STR.W R6, [R9,#0x70]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CTimeModelInfo_FindOtherTimeModel_001FDE74)

		"2:\n"
		"MOVS R0, #0\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CTimeModelInfo_FindOtherTimeModel_001FDE82)
		);
}

static TARGET_THUMB NAKED void CGame_ShutDownForRestart_0020D19C()
{
	__asm(
	".thumb\n"
		".hidden CGame_ShutDownForRestart_0020D18A\n"
		".hidden CGame_ShutDownForRestart_0020D1A4\n"
		".hidden ID\n"
		"ADDS R4, #1\n"
		"ADDS R5, #0x14\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R7, ID)
		"CMP R4, R7\n"
		"BNE 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CGame_ShutDownForRestart_0020D1A4)

		"1:\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CGame_ShutDownForRestart_0020D18A)
		);
}

/*
uintptr_t GetObjectName_002081E8, GetObjectName_002081B4, GetObjectName_00208216;

static TARGET_THUMB NAKED void GetObjectName_0020819C()
{
	__asm(
	".thumb\n"
		".hidden GetObjectName_002081E8\n"
		".hidden GetObjectName_002081B4\n"
		".hidden GetObjectName_00208216\n"
		".hidden ID\n"
		"PUSH {R3,LR}\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, ID)
		"SUBS R3, #1\n"
		"CMP R0, R3\n"
		"MOV R2, R0\n"
		"BLE 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R3, ID)
		"SUBS R3, #4\n"
		"SUB R0, R0, R3\n"
		"SUBS R0, #4\n"
		"CMP.W R0, #0x568\n"
		"BLS 2f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(GetObjectName_002081B4)

		"1:\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(GetObjectName_002081E8)

		"2:\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(GetObjectName_00208216)
		);
}*/

void Android_III_VC_LimitAdjuster::SetModelIDLimit(unsigned int mID)
{
	if (mID > 6500)// GetObjectName
	{
		_ZN10CModelInfo18ms_modelInfoHashesE = malloc(mID * 4);
		memset(_ZN10CModelInfo18ms_modelInfoHashesE, NULL, mID * 4);

		_ZN10CModelInfo16ms_modelInfoPtrsE = malloc(mID * 4 + 4);
		memset(_ZN10CModelInfo16ms_modelInfoPtrsE, NULL, mID * 4 + 4);
		//_ZN10CStreaming16ms_aInfoForModelE = malloc(0x77C4 + mID);
		//memset(_ZN10CStreaming16ms_aInfoForModelE, NULL, 0x77C4 + mID);

		_ZN10CModelInfo16ms_modelInfoPtrsE = (void*)((uintptr_t)_ZN10CModelInfo16ms_modelInfoPtrsE + 4);
		patch::SetPointer(LibAddr + 0x00394D94, _ZN10CModelInfo16ms_modelInfoPtrsE);
		patch::SetPointer(LibAddr + 0x00396394, _ZN10CModelInfo18ms_modelInfoHashesE);
		//patch::SetPointer(LibAddr + 0x0039603C, _ZN10CStreaming16ms_aInfoForModelE);
		
		CModelInfo_GetModelInfo_001EF95C = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x001EF95C);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x001EF94C, (void*)&CModelInfo_GetModelInfo_001EF94C);

		CTimeModelInfo_FindOtherTimeModel_001FDE2E = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x001FDE2E);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x001FDE24, (void*)&CTimeModelInfo_FindOtherTimeModel_001FDE24);

		CTimeModelInfo_FindOtherTimeModel_001FDE82 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x001FDE82);
		CTimeModelInfo_FindOtherTimeModel_001FDE74 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x001FDE74);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x001FDE68, (void*)&CTimeModelInfo_FindOtherTimeModel_001FDE68);
		
		CGame_ShutDownForRestart_0020D1A4 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0020D1A4);
		CGame_ShutDownForRestart_0020D18A = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0020D18A);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0020D19C, (void*)&CGame_ShutDownForRestart_0020D19C);


		/*
		GetObjectName_002081B4 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x002081B4);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0020819C, (void*)&GetObjectName_0020819C);
		GetObjectName_002081E8 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x002081E8);
		GetObjectName_00208216 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00208216);*/
	}
}

void Android_III_VC_LimitAdjuster::SetIDEObjsLimit(unsigned int Objs)
{
	if (Objs > 3885)
	{
		unsigned int Size = 0x68;
		unsigned int structSize = sizeof(uint32_t) + Objs * Size + 0x840;
		ObjsPtr = malloc(structSize);
		memset(ObjsPtr, NULL, structSize);
		
		InitialiseStoreCBaseModelInfo(ObjsPtr, Objs, Size,
			[](char* pObject)
			{
				uintptr_t Address_vtable = LibAddr + 0x00392700;

				*(uintptr_t*)(pObject) = Address_vtable;
			}
		, objs);
		patch::SetPointer(LibAddr + 0xB38F0, (char*)(ObjsPtr) -(LibAddr + 0xB36F8));
		patch::SetPointer(LibAddr + 0xB38F4, (char*)(ObjsPtr) - (LibAddr + 0xB3724));
		patch::SetPointer(LibAddr + 0x1EF8E8, (char*)(ObjsPtr) - (LibAddr + 0x1EF74C));
		patch::SetPointer(LibAddr + 0x1EF90C, (char*)(ObjsPtr)- (LibAddr + 0x1EF8B4));
		patch::SetPointer(LibAddr + 0x1EFA88, (char*)(ObjsPtr) - (LibAddr + 0x1EFA4E));
		patch::SetPointer(LibAddr + 0x1EFC40, (char*)(ObjsPtr)- (LibAddr + 0x1EFAC8));
	}
}

void Android_III_VC_LimitAdjuster::SetIDETobjLimit(unsigned int Tobj)
{
	if (Tobj > 385)
	{
		unsigned int Size = 0x74;
		unsigned int structSize = sizeof(uint32_t) + Tobj * Size + 0x874;
		TobjPtr = malloc(structSize);
		memset(TobjPtr, NULL, structSize);

		InitialiseStoreCBaseModelInfo(TobjPtr, Tobj, Size,
			[](char* pObject)
			{
				uintptr_t Address_vtable = LibAddr + 0x00392690;

				*(uintptr_t*)(pObject) = Address_vtable;
			}
		, tobj);
		patch::SetPointer(LibAddr + 0xB3904, (char*)(TobjPtr) - (LibAddr + 0xB373E));
		patch::SetPointer(LibAddr + 0xB3908, (char*)(TobjPtr) - (LibAddr + 0xB376C));
		patch::SetPointer(LibAddr + 0x1EF8EC, (char*)(TobjPtr) - (LibAddr + 0x1EF776));
		patch::SetPointer(LibAddr + 0x1EF910, (char*)(TobjPtr) - (LibAddr + 0x1EF8B8));
		patch::SetPointer(LibAddr + 0x1EFC48, (char*)(TobjPtr) - (LibAddr + 0x1EFADA));
		patch::SetPointer(LibAddr + 0x1EFCC8, (char*)(TobjPtr) - (LibAddr + 0x1EFC8E));
	}
}

void Android_III_VC_LimitAdjuster::SetWeaponLimit(unsigned int Weapon)
{
	if (Weapon > 37)
	{
		unsigned int Size = 0x6C;
		unsigned int structSize = sizeof(uint32_t) + Weapon * Size + 0xD3C;
		WeaponPtr = malloc(structSize);
		memset(WeaponPtr, NULL, structSize);
		
		InitialiseStoreCBaseModelInfo(WeaponPtr, Weapon, Size,
			[](char* pObject)
			{
				uintptr_t Address_vtable = LibAddr + 0x00392770;

				*(uintptr_t*)(pObject) = Address_vtable;
			}
		, weapon);
		patch::SetPointer(LibAddr + 0xB3918, (char*)(WeaponPtr) - (LibAddr + 0xB3786));
		patch::SetPointer(LibAddr + 0xB391C, (char*)(WeaponPtr) - (LibAddr + 0xB37B4));
		patch::SetPointer(LibAddr + 0x1EF8F0, (char*)(WeaponPtr) - (LibAddr + 0x1EF7A0));
		patch::SetPointer(LibAddr + 0x1EF914, (char*)(WeaponPtr) - (LibAddr + 0x1EF8BC));
		patch::SetPointer(LibAddr + 0x1EFC4C, (char*)(WeaponPtr) - (LibAddr + 0x1EFADE));
		patch::SetPointer(LibAddr + 0x1EFD18, (char*)(WeaponPtr) - (LibAddr + 0x1EFCDE));
	}
}

/*
void* Hier_VehiclesPtr;

void Android_III_VC_LimitAdjuster::SetIDEHier_VehiclesLimit(unsigned int Hier, unsigned int Vehicles)
{
	if (Vehicles > 110 || Hier > 5)
	{
		unsigned int HierSize = 0x54;
		unsigned int VehiclesSize = 0x198;
		unsigned int structSize;
		if (Vehicles > 110)
		{
			if (Hier > 5)
				structSize = sizeof(uint32_t) + Vehicles * VehiclesSize + 0xD8C + Hier * HierSize + 0xBE0;
			else
				structSize = sizeof(uint32_t) + Vehicles * VehiclesSize + 0xD8C + 5 * HierSize + 0xBE0;
		}
		else if (Hier > 5)
		{
			if (Vehicles > 110)
				structSize = sizeof(uint32_t) + Vehicles * VehiclesSize + 0xD8C + Hier * HierSize + 0xBE0;
			else
				structSize = sizeof(uint32_t) + 110 * VehiclesSize + 0xD8C + Hier * HierSize + 0xBE0;
		}
		Hier_VehiclesPtr = malloc(structSize);
		memset(Hier_VehiclesPtr, NULL, structSize);
		//InitialiseStoreCBaseModelInfo((char*)Hier_VehiclesPtr + Hier * HierSize + 0xBE0 + 4, Vehicles, VehiclesSize, nullptr, vehicles);
		InitialiseStoreCBaseModelInfo(Hier_VehiclesPtr, Hier, HierSize,
			[](char* pObject)
			{
				uintptr_t Address_vtable = LibAddr + 0x00392658;

				*(uintptr_t*)(pObject) = Address_vtable;
			}
		, hier);
		patch::SetPointer(LibAddr + 0xB3928, (char*)(Hier_VehiclesPtr) - (LibAddr + 0xB37C6));
		//patch::SetPointer(LibAddr + 0xB3930, (char*)((char*)Hier_VehiclesPtr + Hier * HierSize + 0xBE0) - (LibAddr + 0xB37F2));
		//patch::SetPointer(LibAddr + 0xB393C, (char*)((char*)Hier_VehiclesPtr + Hier * HierSize + 0xBE0) - (LibAddr + 0xB3828));
		patch::SetPointer(LibAddr + 0x1EF8F4, (char*)(Hier_VehiclesPtr) - (LibAddr + 0x1EF7CA));
		//patch::SetPointer(LibAddr + 0x1EF8F8, (char*)((char*)Hier_VehiclesPtr + Hier * HierSize + 0xBE0) - (LibAddr + 0x1EF7F4));
		//patch::SetPointer(LibAddr + 0x1EF924, (char*)((char*)Hier_VehiclesPtr + Hier * HierSize + 0xBE0) - (LibAddr + 0x1EF8CC));
		patch::SetPointer(LibAddr + 0x1EFC5C, (char*)(Hier_VehiclesPtr) - (LibAddr + 0x1EFAEE));
		patch::SetPointer(LibAddr + 0x1EFD68, (char*)(Hier_VehiclesPtr) - (LibAddr + 0x1EFD2C));
		//patch::SetPointer(LibAddr + 0x1EFDDC, (char*)((char*)Hier_VehiclesPtr + Hier * HierSize + 0xBE0) - (LibAddr + 0x1EFD7E));
	}
}*/


void Android_III_VC_LimitAdjuster::SetIDEVehiclesLimit(unsigned int Vehicles)
{
	if (Vehicles > 110)
	{
		unsigned int Size = 0x198;
		unsigned int structSize = sizeof(uint32_t) + Vehicles * Size + 0xD8C;
		VehiclesPtr = malloc(structSize);
		memset(VehiclesPtr, NULL, structSize);
		InitialiseStoreCBaseModelInfo(VehiclesPtr, Vehicles, Size, nullptr, vehicles);
		
		patch::SetPointer(LibAddr + 0xB3930, (char*)(VehiclesPtr) - (LibAddr + 0xB37F2));
		patch::SetPointer(LibAddr + 0xB393C, (char*)(VehiclesPtr) - (LibAddr + 0xB3828));
		patch::SetPointer(LibAddr + 0x1EF8F8, (char*)(VehiclesPtr) - (LibAddr + 0x1EF7F4));
		patch::SetPointer(LibAddr + 0x1EF924, (char*)(VehiclesPtr) - (LibAddr + 0x1EF8CC));
		patch::SetPointer(LibAddr + 0x1EFC5C, (char*)(VehiclesPtr) - (LibAddr + 0x1EFAEE));
		patch::SetPointer(LibAddr + 0x1EFDDC, (char*)(VehiclesPtr) - (LibAddr + 0x1EFD7E));
	}
}

void Android_III_VC_LimitAdjuster::SetIDEPedLimit(unsigned int Ped)
{
	if (Ped > 130)
	{
		unsigned int Size = 0x6C;
		unsigned int structSize = sizeof(uint32_t) + Ped * Size + 0x238;
		PedPtr = malloc(structSize);
		memset(PedPtr, NULL, structSize);

		InitialiseStoreCBaseModelInfo(PedPtr, Ped, Size,
			[](char* pObject)
			{
				uintptr_t Address_vtable = LibAddr + 0x003926C8;

				*(uintptr_t*)(pObject) = Address_vtable;
			}
		, ped);
		patch::SetPointer(LibAddr + 0xB394C, (char*)(PedPtr) - (LibAddr + 0xB3842));
		patch::SetPointer(LibAddr + 0xB3950, (char*)(PedPtr) - (LibAddr + 0xB3872));
		patch::SetPointer(LibAddr + 0x1EF8FC, (char*)(PedPtr) - (LibAddr + 0x1EF820));
		patch::SetPointer(LibAddr + 0x1EF918, (char*)(PedPtr) - (LibAddr + 0x1EF8C0));
		patch::SetPointer(LibAddr + 0x1EFC50, (char*)(PedPtr) - (LibAddr + 0x1EFAE2));
		patch::SetPointer(LibAddr + 0x1EFE2C, (char*)(PedPtr) - (LibAddr + 0x1EFDF0));
	}
}

void Android_III_VC_LimitAdjuster::SetIDE2dfxLimit(unsigned int _2dfx)
{
	if (_2dfx > 1210)
	{
		unsigned int Size = 0x34;
		unsigned int structSize = _2dfx * Size + 0x38;
		__2dfxPtr = malloc(structSize);
		memset(__2dfxPtr, NULL, structSize);

		patch::SetPointer(LibAddr + 0xB395C, (char*)(__2dfxPtr) - (LibAddr + 0xB388A));
		patch::SetPointer(LibAddr + 0xB3960, (char*)(__2dfxPtr) - (LibAddr + 0xB38AE));
		patch::SetPointer(LibAddr + 0x1EF740, (char*)(__2dfxPtr) - (LibAddr + 0x1EF724));
		patch::SetPointer(LibAddr + 0x1EF900, (char*)(__2dfxPtr) - (LibAddr + 0x1EF84A));
		patch::SetPointer(LibAddr + 0x1EF904, (char*)(__2dfxPtr) - (LibAddr + 0x1EF858));
		patch::SetPointer(LibAddr + 0x1EF91C, (char*)(__2dfxPtr) - (LibAddr + 0x1EF8C4));
		patch::SetPointer(LibAddr + 0x1EFC54, (char*)(__2dfxPtr) - (LibAddr + 0x1EFAE6));
		patch::SetPointer(LibAddr + 0x1EFE90, (char*)(__2dfxPtr) - (LibAddr + 0x1EFE8E));
	}
}

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

static TARGET_THUMB NAKED void Pools_Initialise_0016F21A()
{
	__asm(
	".thumb\n"
		".hidden PedSize\n"
		".hidden Ped\n"
		".hidden ms_pPedPool_0016F242\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, PedSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Ped)
		"BL 1f\n"
		"MOV.W R2, #0xFFFFFFFF\n"
		"MOVS R3, #0\n"
		"STR R2, [R5, #0xC]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Ped)
		"STR R0, [R5, #8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pPedPool_0016F242)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F24E()
{
	__asm(
	".thumb\n"
		".hidden Ped\n"
		".hidden ms_pPedPool_0016F258\n"
		"BIC.W R2, R2, #0x7F\n"
		"STRB R2, [R1,R3]\n"
		"ADDS R3, #1\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, Ped)
		"CMP R3, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pPedPool_0016F258)
		);
}

void Android_III_VC_LimitAdjuster::SetPedPoolLimit(unsigned int nPed)
{
	if (nPed > 140)
	{
		PedSize = nPed * 0x730;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pPedPool_0016F242 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F242);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F21A, (void*)&Pools_Initialise_0016F21A);
		
		ms_pPedPool_0016F258 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F258);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F24E, (void*)&Pools_Initialise_0016F24E);
	}
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F268()
{
	__asm(
	".thumb\n"
		".hidden VehicleSize\n"
		".hidden Vehicle\n"
		".hidden ms_pVehiclePool_0016F290\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, VehicleSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Vehicle)
		"BL 1f\n"
		"MOV.W R2, #0xFFFFFFFF\n"
		"MOVS R3, #0\n"
		"STR R2, [R5, #0xC]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Vehicle)
		"STR R0, [R5, #8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pVehiclePool_0016F290)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F29C()
{
	__asm(
	".thumb\n"
		".hidden Vehicle\n"
		".hidden ms_pVehiclePool_0016F2A6\n"
		"BIC.W R2, R2, #0x7F\n"
		"STRB R2, [R1,R3]\n"
		"ADDS R3, #1\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, Vehicle)
		"CMP R3, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pVehiclePool_0016F2A6)
		);
}

void Android_III_VC_LimitAdjuster::SetVehiclePoolLimit(unsigned int nVehicle)
{
	if (nVehicle > 110)
	{
		VehicleSize = nVehicle * 0x5E0;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pVehiclePool_0016F290 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F290);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F268, (void*)&Pools_Initialise_0016F268);

		ms_pVehiclePool_0016F2A6 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F2A6);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F29C, (void*)&Pools_Initialise_0016F29C);
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

static TARGET_THUMB NAKED void Pools_Initialise_0016F30E()
{
	__asm(
	".thumb\n"
		".hidden TreadableSize\n"
		".hidden Treadable\n"
		".hidden ms_pTreadablePool_0016F31C\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, TreadableSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, Treadable)
		"BL 1f\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pTreadablePool_0016F31C)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetTreadablePoolLimit(unsigned int nTreadable)
{
	if (nTreadable > 1)
	{
		TreadableSize = nTreadable * 0x68;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pTreadablePool_0016F31C = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F31C);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F30E, (void*)&Pools_Initialise_0016F30E);
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

static TARGET_THUMB NAKED void Pools_Initialise_0016F3EA()
{
	__asm(
	".thumb\n"
		".hidden AudioScriptObjectSize\n"
		".hidden AudioScriptObject\n"
		".hidden ms_pAudioScriptObjectPool_0016F40E\n"
		".hidden _Znaj\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AudioScriptObjectSize)
		"BL 1f\n"
		"STR R0, [R5]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AudioScriptObject)
		"BL 1f\n"
		"MOV.W R2, #0xFFFFFFFF\n"
		"MOVS R3, #0\n"
		"STR R2, [R5, #0xC]\n"
		"MOV R1, R0\n"
		"STR R0, [R5, #4]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AudioScriptObject)
		"STR R0, [R5, #8]\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pAudioScriptObjectPool_0016F40E)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

static TARGET_THUMB NAKED void Pools_Initialise_0016F41A()
{
	__asm(
	".thumb\n"
		".hidden AudioScriptObject\n"
		".hidden ms_pAudioScriptObjectPool_0016F424\n"
		"BIC.W R2, R2, #0x7F\n"
		"STRB R2, [R1,R3]\n"
		"ADDS R3, #1\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R6, AudioScriptObject)
		"CMP R3, R6\n"
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(ms_pAudioScriptObjectPool_0016F424)
		);
}

void Android_III_VC_LimitAdjuster::SetAudioScriptObjectPoolLimit(unsigned int nAudioScriptObject)
{
	if (nAudioScriptObject > 192)
	{
		AudioScriptObjectSize = nAudioScriptObject * 0x14;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		ms_pAudioScriptObjectPool_0016F40E = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F40E);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F3EA, (void*)&Pools_Initialise_0016F3EA);

		ms_pAudioScriptObjectPool_0016F424 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x0016F424);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x0016F41A, (void*)&Pools_Initialise_0016F41A);
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

static TARGET_THUMB NAKED void CVisibilityPlugins_Initialise_00215AE8()
{
	__asm(
	".thumb\n"
		".hidden AlphaEntityList\n"
		".hidden AlphaEntityListSub\n"
		".hidden CVisibilityPlugins_Initialise_00215AFE\n"
		".hidden _Znaj\n"
		"MOVW R3, #0xBC20\n"
		"MOVS R2, #0\n"
		"MOVT R3, #0x4CBE\n"
		"STR R2, [R5,#4]\n"
		"STR R3, [R5,#0x14]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AlphaEntityList)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, AlphaEntityListSub)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CVisibilityPlugins_Initialise_00215AFE)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetAlphaEntityListLimit(unsigned int nAlphaEntityList)
{
	{
		AlphaEntityList = nAlphaEntityList * 0x40;
		AlphaEntityListSub = AlphaEntityList - 0x10;
		_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
		CVisibilityPlugins_Initialise_00215AFE = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00215AFE);
		patch::NOPinstructions(INSTRUCTION_SET_THUMB, LibAddr + 0x00215B00, 4);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x00215AE8, (void*)&CVisibilityPlugins_Initialise_00215AE8);
	}
}

static TARGET_THUMB NAKED void CVisibilityPlugins_Initialise_00215B42()
{
	__asm(
	".thumb\n"
		".hidden AlphaUnderwaterEntityList\n"
		".hidden AlphaUnderwaterEntityListSub\n"
		".hidden CVisibilityPlugins_Initialise_00215B58\n"
		".hidden _Znaj\n"
		"MOVW R3, #0xBC20\n"
		"MOVS R2, #0\n"
		"MOVT R3, #0x4CBE\n"
		"STR R2, [R5,#4]\n"
		"STR R3, [R5,#0x14]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AlphaUnderwaterEntityList)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, AlphaUnderwaterEntityListSub)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CVisibilityPlugins_Initialise_00215B58)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetAlphaUnderwaterEntityListLimit(unsigned int nAlphaUnderwaterEntityList)
{
	AlphaUnderwaterEntityList = nAlphaUnderwaterEntityList * 0x40;
	AlphaUnderwaterEntityListSub = AlphaUnderwaterEntityList - 0x10;
	_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
	CVisibilityPlugins_Initialise_00215B58 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00215B58);
	patch::NOPinstructions(INSTRUCTION_SET_THUMB, LibAddr + 0x00215B5A, 4);
	patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x00215B42, (void*)&CVisibilityPlugins_Initialise_00215B42);
}

static TARGET_THUMB NAKED void CVisibilityPlugins_Initialise_00215A40()
{
	__asm(
	".thumb\n"
		".hidden AlphaList\n"
		".hidden AlphaListSub\n"
		".hidden CVisibilityPlugins_Initialise_00215A4A\n"
		".hidden _Znaj\n"
		"PUSH {R3-R7,LR}\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AlphaList)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, AlphaListSub)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CVisibilityPlugins_Initialise_00215A4A)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetAlphaListLimit(unsigned int nAlphaList)
{
	AlphaList = nAlphaList * 0x40;
	AlphaListSub = AlphaList - 0x10;
	_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
	CVisibilityPlugins_Initialise_00215A4A = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00215A4A);
	patch::NOPinstructions(INSTRUCTION_SET_THUMB, LibAddr + 0x00215A4C, 4);
	patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x00215A40, (void*)&CVisibilityPlugins_Initialise_00215A40);
}

static TARGET_THUMB NAKED void CVisibilityPlugins_Initialise_00215A8E()
{
	__asm(
	".thumb\n"
		".hidden AlphaBoatAtomicList\n"
		".hidden AlphaBoatAtomicListSub\n"
		".hidden CVisibilityPlugins_Initialise_00215AA4\n"
		".hidden _Znaj\n"
		"MOVW R3, #0xBC20\n"
		"MOVS R2, #0\n"
		"MOVT R3, #0x4CBE\n"
		"STR R2, [R5,#4]\n"
		"STR R3, [R5,#0x14]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, AlphaBoatAtomicList)
		"BL 1f\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, AlphaBoatAtomicListSub)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CVisibilityPlugins_Initialise_00215AA4)

		"1:\n"	// _Znaj
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(_Znaj)
		);
}

void Android_III_VC_LimitAdjuster::SetAlphaBoatAtomicListLimit(unsigned int nAlphaBoatAtomicList)
{
	AlphaBoatAtomicList = nAlphaBoatAtomicList * 0x40;
	AlphaBoatAtomicListSub = AlphaBoatAtomicList - 0x10;
	_Znaj = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00327E5C);
	CVisibilityPlugins_Initialise_00215AA4 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00215AA4);
	patch::NOPinstructions(INSTRUCTION_SET_THUMB, LibAddr + 0x00215AA6, 4);
	patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x00215A8E, (void*)&CVisibilityPlugins_Initialise_00215A8E);
}

void Android_III_VC_LimitAdjuster::SetImageLimit(unsigned int img)
{
	if (img > 16)
	{
		gImgFiles = malloc(img * 4);
		gImg = malloc(img * 0x20 + 4);
		patch::SetPointer(LibAddr + 0x00394C8C, gImgFiles);
		patch::SetPointer(LibAddr + 0x0014094C, (char*)(gImg) - (LibAddr + 0x1408E6));
		patch::SetPointer(LibAddr + 0x00140954, (char*)(gImg) - (LibAddr + 0x14090A));
		patch::SetPointer(LibAddr + 0x00140978, (char*)(gImg) - (LibAddr + 0x14096A));
		patch::SetPointer(LibAddr + 0x001409E0, (char*)(gImg) - (LibAddr + 0x140990));
		patch::SetPointer(LibAddr + 0x001409EC, (char*)(gImg) - (LibAddr + 0x1409D8));
		patch::SetPointer(LibAddr + 0x00140A40, (char*)(gImg) - (LibAddr + 0x1409FC));
		patch::SetPointer(LibAddr + 0x00140A50, (char*)(gImg) - (LibAddr + 0x140A4E));
	}
}

void Android_III_VC_LimitAdjuster::SetVisibleEntityPtrs(unsigned int nVisibleEntityPtrs)
{
	if (nVisibleEntityPtrs > 2000)
	{
		VisibleEntityPtrs = malloc(nVisibleEntityPtrs * 4);
		patch::SetPointer(LibAddr + 0x003946FC, VisibleEntityPtrs);
	}
}

static TARGET_THUMB NAKED void CTheZones_Init_00189822()
{
	__asm(
	".thumb\n"
		".hidden CTheZones_Init_00189834\n"
		".hidden WorldMaxX\n"
		".hidden WorldMaxY\n"
		"MOVS R0, #1\n"
		"STRH R0, [R1]\n"
		"LDR.W R1, [R8,R12]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R10, WorldMaxX)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R9, WorldMaxY)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CTheZones_Init_00189834)
		);
}

static TARGET_THUMB NAKED void CTheZones_Init_00189914()
{
	__asm(
	".thumb\n"
		".hidden CTheZones_Init_00189946\n"
		".hidden WorldMinX\n"
		".hidden WorldMinY\n"
		".hidden WorldMaxY\n"
		".hidden WorldMaxX\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R12, WorldMinX)
		"MOVS R6, #1\n"
		"LDR.W R4, [R8,R1]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R7, WorldMinY)
		"LDMIA.W R3, {R9,R1}\n"
		"MOVS R5, #0\n"
		"MOVT R5, #0xC3FA\n"
		"STR.W R2, [LR,#0x24]\n"
		"LSRS R3, R1, #0x10\n"
		"STRB.W R3, [LR,#6]\n"
		"STR.W R9, [LR]\n"
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R2, WorldMaxY)
		ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(R0, WorldMaxX)
		ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(CTheZones_Init_00189946)
		);
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
		float value = inireader.ReadFloat("WorldBoundary", "RenderValue", 50.0);
		WorldMinX = inireader.ReadFloat("WorldBoundary", "WorldMinX", -2400.0);
		WorldMinY = inireader.ReadFloat("WorldBoundary", "WorldMinY", -2000.0);
		WorldMaxX = inireader.ReadFloat("WorldBoundary", "WorldMaxX", 1600.0);
		WorldMaxY = inireader.ReadFloat("WorldBoundary", "WorldMaxY", 2000.0);

		float AircraftHeight = inireader.ReadFloat("WorldBoundary", "AircraftHeight", 80.0);
		float PedZ = inireader.ReadFloat("WorldBoundary", "PedZLow", -100.0);
		float CarZ = inireader.ReadFloat("WorldBoundary", "CarZLow", -100.0);

		float CarMinX = inireader.ReadFloat("WorldBoundary", "CarMinX", -2350.0);
		float CarMinY = inireader.ReadFloat("WorldBoundary", "CarMinY", -1950.0);
		float CarMaxX = inireader.ReadFloat("WorldBoundary", "CarMaxX", 1550.0);
		float CarMaxY = inireader.ReadFloat("WorldBoundary", "CarMaxY", 1950.0);

		float BoatMinX = inireader.ReadFloat("WorldBoundary", "BoatMinX", -2300.0);
		float BoatMinY = inireader.ReadFloat("WorldBoundary", "BoatMinY", -1900.0);
		float BoatMaxX = inireader.ReadFloat("WorldBoundary", "BoatMaxX", 1500.0);
		float BoatMaxY = inireader.ReadFloat("WorldBoundary", "BoatMaxY", 1900.0);

		float ProjectileMinX = inireader.ReadFloat("WorldBoundary", "ProjectileMinX", -2390.0);
		float ProjectileMinY = inireader.ReadFloat("WorldBoundary", "ProjectileMinY", -1990.0);
		float ProjectileMaxX = inireader.ReadFloat("WorldBoundary", "ProjectileMaxX", 1590.0);
		float ProjectileMaxY = inireader.ReadFloat("WorldBoundary", "ProjectileMaxY", 1990.0);

		patch::SetFloat(LibAddr + 0x0025B950, AircraftHeight);//CVehicle::FlyingControl
		patch::SetFloat(LibAddr + 0x001858BC, PedZ);//CWorld::RemoveFallenPeds
		patch::SetFloat(LibAddr + 0x001859FC, CarZ);//CWorld::RemoveFallenCars

		//CAutomobile::ProcessControl
		patch::SetFloat(LibAddr + 0x00239B78, CarMaxX);
		patch::SetFloat(LibAddr + 0x00239B7C, CarMaxY);
		patch::SetFloat(LibAddr + 0x0023A6A4, CarMinY);
		patch::SetFloat(LibAddr + 0x0023A6B4, CarMinX);

		//CBoat::ProcessControl
		patch::SetFloat(LibAddr + 0x002497F4, BoatMaxX);
		patch::SetFloat(LibAddr + 0x002497F8, BoatMinX);
		patch::SetFloat(LibAddr + 0x00249800, BoatMaxY);
		patch::SetFloat(LibAddr + 0x00249804, BoatMinY);

		//CProjectileInfo::Update
		patch::SetFloat(LibAddr + 0x002679FC, ProjectileMinX);
		patch::SetFloat(LibAddr + 0x00267A00, ProjectileMaxX);
		patch::SetFloat(LibAddr + 0x00267A04, ProjectileMinY);
		patch::SetFloat(LibAddr + 0x00267A08, ProjectileMaxY);
		
		//CWorld::ProcessLineOfSight
		patch::SetFloat(LibAddr + 0x00187FF4, WorldMinX);
		patch::SetFloat(LibAddr + 0x00187FF8, WorldMaxX);
		patch::SetFloat(LibAddr + 0x00187FFC, WorldMinY);
		patch::SetFloat(LibAddr + 0x00188000, WorldMaxY);

		//CRegisteredCorona::Update
		patch::SetFloat(LibAddr + 0x001D593C, WorldMinX);
		patch::SetFloat(LibAddr + 0x001D5940, WorldMaxX);
		patch::SetFloat(LibAddr + 0x001D5944, WorldMinY);
		patch::SetFloat(LibAddr + 0x001D5948, WorldMaxY);

		//GenerateHeli
		patch::SetFloat(LibAddr + 0x00254780, WorldMinX);
		patch::SetFloat(LibAddr + 0x00254784, WorldMaxX);
		patch::SetFloat(LibAddr + 0x00254788, WorldMinY);
		patch::SetFloat(LibAddr + 0x0025478C, WorldMaxY);

		//CBulletInfo::Update
		patch::SetFloat(LibAddr + 0x00264DA4, WorldMinX);
		patch::SetFloat(LibAddr + 0x00264DA8, WorldMaxX);
		patch::SetFloat(LibAddr + 0x00264DB0, WorldMinY);
		patch::SetFloat(LibAddr + 0x00264DB4, WorldMaxY);

		//CTheZones::Init
		patch::SetFloat(LibAddr + 0x00189970, WorldMinX);
		patch::SetFloat(LibAddr + 0x00189974, WorldMinY);
		CTheZones_Init_00189834 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00189834);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x00189822, (void*)&CTheZones_Init_00189822);
		patch::NOPinstructions(INSTRUCTION_SET_THUMB, LibAddr + 0x00189838, 4);
		patch::SetUint16(LibAddr + 0x00189912, 0x4681); //MOV R9, R0
		CTheZones_Init_00189946 = ASM_GET_THUMB_ADDRESS_FOR_JUMP(LibAddr + 0x00189946);
		patch::RedirectCodeEx(INSTRUCTION_SET_THUMB, LibAddr + 0x00189914, (void*)&CTheZones_Init_00189914);
		
		patch::SetFloat(LibAddr + 0x000E6E44, value);//CCarCtrl::ScanForPedDanger
		patch::SetFloat(LibAddr + 0x000E7B0C, value);//CCarCtrl::FindAngleToWeaveThroughTraffic
		patch::SetFloat(LibAddr + 0x000EAA28, value);//CCarCtrl::FindMaximumSpeedForThisCarInTraffic
		patch::SetFloat(LibAddr + 0x000F3C3C, value);//CGarage::FindDoorsEntities
		patch::SetFloat(LibAddr + 0x000FDA48, value);//CPedPath::CalcPedRoute
		patch::SetFloat(LibAddr + 0x0012A6A0, value);//CCam::Process_Editor
		patch::SetFloat(LibAddr + 0x00136F50, value);//CCamera::IsItTimeForNewcam
		patch::SetFloat(LibAddr + 0x0014588C, value);//CDummy::Add
		patch::SetFloat(LibAddr + 0x00145F1C, value);//CEntity::Add
		patch::SetFloat(LibAddr + 0x001460C4, value);//CEntity::Remove
		patch::SetFloat(LibAddr + 0x001659B4, value);//CPhysical::Add
		patch::SetFloat(LibAddr + 0x00165D68, value);//CPhysical::RemoveAndAdd
		patch::SetFloat(LibAddr + 0x0016DA4C, value);//CPlayerInfo::IsVehicleNearby
		patch::SetFloat(LibAddr + 0x0016E7B0, value);//CPlayerInfo::Process
		patch::SetFloat(LibAddr + 0x00177DEC, value);//CRenderer::ScanWorld
		patch::SetFloat(LibAddr + 0x00178530, value);//CRenderer::RequestObjectsInFrustum
		patch::SetFloat(LibAddr + 0x001839BC, value);//CWorld::TriggerExplosion
		patch::SetFloat(LibAddr + 0x00183B54, value);//CWorld::ProcessVerticalLine
		patch::SetFloat(LibAddr + 0x00183C5C, value);//CWorld::CastShadow
		patch::SetFloat(LibAddr + 0x00184074, value);//CWorld::FindObjectsInRange
		patch::SetFloat(LibAddr + 0x001844E0, value);//CWorld::FindObjectsOfTypeInRange
		patch::SetFloat(LibAddr + 0x0018480C, value);//CWorld::FindObjectsKindaColliding
		patch::SetFloat(LibAddr + 0x00184B1C, value);//CWorld::FindObjectsIntersectingCube
		patch::SetFloat(LibAddr + 0x00184E50, value);//CWorld::FindObjectsIntersectingAngledCollisionBox
		patch::SetFloat(LibAddr + 0x00185168, value);//CWorld::FindMissionEntitiesIntersectingCube
		patch::SetFloat(LibAddr + 0x00186380, value);//CWorld::ProcessVerticalLine_FillGlobeColPoints
		patch::SetFloat(LibAddr + 0x00187650, value);//CWorld::CallOffChaseForArea
		patch::SetFloat(LibAddr + 0x00188004, value);//CWorld::ProcessLineOfSight
		patch::SetFloat(LibAddr + 0x00188ABC, value);//CWorld::GetIsLineOfSightClear
		patch::SetFloat(LibAddr + 0x00188AC8, value);//
		patch::SetFloat(LibAddr + 0x0018962C, value);//CWorld::TestSphereAgainstWorld
		patch::SetFloat(LibAddr + 0x00194734, value);//CCivilianPed::UseNearbyAttractors
		patch::SetFloat(LibAddr + 0x00194B90, value);//CCivilianPed::EnterVacantNearbyCars
		patch::SetFloat(LibAddr + 0x001A5964, value);//CPed::BuildPedLists
		patch::SetFloat(LibAddr + 0x001A62D8, value);//CPed::LookForInterestingNodes
		patch::SetFloat(LibAddr + 0x001BA598, value);//CPed::ProcessObjective
		patch::SetFloat(LibAddr + 0x001D0244, value);//CPopulation::TestSafeForRealObject
		patch::SetFloat(LibAddr + 0x001E6EB0, value);//CGlass::HasGlassBeenShatteredAtCoors
		patch::SetFloat(LibAddr + 0x001FBAF0, value);//CShadows::GeneratePolysForStaticShadow
		patch::SetFloat(LibAddr + 0x001FD118, value);//CShadows::RenderStoredShadows
		patch::SetFloat(LibAddr + 0x00208A1C, value);//CStreaming::DeleteRwObjectsAfterDeath
		patch::SetFloat(LibAddr + 0x00208B00, value);//CStreaming::DeleteRwObjectsInOverlapSectorList
		patch::SetFloat(LibAddr + 0x00208D64, value);//CStreaming::DeleteFarAwayRwObjects
		patch::SetFloat(LibAddr + 0x00208E9C, value);//CStreaming::InstanceLoadedModels
		patch::SetFloat(LibAddr + 0x0020947C, value);//CStreaming::AddModelsToRequestList
		patch::SetFloat(LibAddr + 0x0020C520, value);//CStreaming::DeleteRwObjectsBehindCamera
		patch::SetFloat(LibAddr + 0x00235FB0, value);//CAutomobile::RcbanditCheckHitWheels
		patch::SetFloat(LibAddr + 0x00236734, value);//CPed::DeadPedMakesTyresBloody
		patch::SetFloat(LibAddr + 0x0024E15C, value);//CCrane::Update
		patch::SetFloat(LibAddr + 0x0025CE44, value);//CVehicle::DoBladeCollision
		patch::SetFloat(LibAddr + 0x00262830, value);//CWaterLevel::IsLocationOutOfWorldBounds_WS
		
		PtrNode = inireader.ReadInteger("PoolLimit", "PtrNode", 50000);
		EntryInfoNode = inireader.ReadInteger("PoolLimit", "EntryInfoNode", 3200);
		Ped = inireader.ReadInteger("PoolLimit", "Ped", 140);
		Vehicle = inireader.ReadInteger("PoolLimit", "Vehicle", 110);
		Building = inireader.ReadInteger("PoolLimit", "Building", 7000);
		Treadable = inireader.ReadInteger("PoolLimit", "Treadable", 1);
		Object = inireader.ReadInteger("PoolLimit", "Object", 510);
		Dummy = inireader.ReadInteger("PoolLimit", "Dummy", 2340);
		AudioScriptObject = inireader.ReadInteger("PoolLimit", "AudioScriptObject", 192);
		ColModel = inireader.ReadInteger("PoolLimit", "ColModel", 4400);

		LimitAdjuster.SetPtrNodePoolLimit(PtrNode);
		LimitAdjuster.SetEntryInfoNodePoolLimit(EntryInfoNode);
		LimitAdjuster.SetPedPoolLimit(Ped);
		LimitAdjuster.SetVehiclePoolLimit(Vehicle);
		LimitAdjuster.SetBuildingPoolLimit(Building);
		LimitAdjuster.SetTreadablePoolLimit(Treadable);
		LimitAdjuster.SetObjectPoolLimit(Object);
		LimitAdjuster.SetDummyPoolLimit(Dummy);
		LimitAdjuster.SetAudioScriptObjectPoolLimit(AudioScriptObject);
		LimitAdjuster.SetColModelPoolLimit(ColModel);

		CBaseModelInfo_CBaseModelInfo = (uintptr_t)cleo->GetMainLibrarySymbol("_ZN14CBaseModelInfoC2E13ModelInfoType");
		CVehicleModelInfo_CVehicleModelInfo = (uintptr_t)cleo->GetMainLibrarySymbol("_ZN17CVehicleModelInfoC2Ev");

		ID = inireader.ReadInteger("IDELimit", "ID", 6500);
		LimitAdjuster.SetModelIDLimit(ID);
		LimitAdjuster.SetIDEObjsLimit(inireader.ReadInteger("IDELimit", "Objs", 3885));
		LimitAdjuster.SetIDETobjLimit(inireader.ReadInteger("IDELimit", "Tobj", 385));
		//LimitAdjuster.SetWeaponLimit(inireader.ReadInteger("IDELimit", "Weapon", 37));
		//LimitAdjuster.SetIDEHier_VehiclesLimit(inireader.ReadInteger("IDELimit", "Hier", 5), inireader.ReadInteger("IDELimit", "Vehicles", 110));
		LimitAdjuster.SetIDEVehiclesLimit(inireader.ReadInteger("IDELimit", "Vehicles", 110));
		//LimitAdjuster.SetIDEPedLimit(inireader.ReadInteger("IDELimit", "Ped", 130));
		LimitAdjuster.SetIDE2dfxLimit(inireader.ReadInteger("IDELimit", "2dfx", 1210));

		LimitAdjuster.SetAlphaListLimit(inireader.ReadInteger("VisibilityLimit", "AlphaList", 5));
		LimitAdjuster.SetAlphaBoatAtomicListLimit(inireader.ReadInteger("VisibilityLimit", "AlphaBoatAtomicList", 5));
		LimitAdjuster.SetAlphaEntityListLimit(inireader.ReadInteger("VisibilityLimit", "AlphaEntityList", 50));
		LimitAdjuster.SetAlphaUnderwaterEntityListLimit(inireader.ReadInteger("VisibilityLimit", "AlphaUnderwaterEntityList", 7));
		
		LimitAdjuster.SetImageLimit(inireader.ReadInteger("ImageLimit", "IMG", 16));
		LimitAdjuster.SetVisibleEntityPtrs(inireader.ReadInteger("Renderer", "VisibleEntityPtrs", 2000));
	}
}

