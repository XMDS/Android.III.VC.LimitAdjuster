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

float WorldMaxX, WorldMaxY, WorldMinX, WorldMinY;
uintptr_t CTheZones_Init_00189834, CTheZones_Init_00189946;

/*
char* newmen;

void Android_III_VC_LimitAdjuster::SetIDELimit(unsigned int iObjectsType1)
{
	if (iObjectsType1 > 3885)
	{
		unsigned int Size = 0x68;
		unsigned int structSize = sizeof(uint32_t) + iObjectsType1 * Size;
		newmen = new char[structSize];
		memset(newmen, NULL, structSize);

		newmen1 = (uintptr_t)newmen;
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

		float PlaneTrailsMinX = inireader.ReadFloat("WorldBoundary", "PlaneTrailsMinX", 1200.0);
		float PlaneTrailsMinY = inireader.ReadFloat("WorldBoundary", "PlaneTrailsMinY", -1600.0);
		float PlaneTrailsMaxX = inireader.ReadFloat("WorldBoundary", "PlaneTrailsMaxX", 1590.0);
		float PlaneTrailsMaxY = inireader.ReadFloat("WorldBoundary", "PlaneTrailsMaxY", 1000.0);

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

		//CPlaneTrails::Update
		patch::SetFloat(LibAddr + 0x001DF268, PlaneTrailsMaxX);
		patch::SetFloat(LibAddr + 0x001DF26C, PlaneTrailsMinX);
		patch::SetFloat(LibAddr + 0x001DF270, PlaneTrailsMaxY);
		patch::SetFloat(LibAddr + 0x001DF274, PlaneTrailsMinY);
		
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

