#pragma once

class Android_III_VC_LimitAdjuster
{
public:
	void SetIDEObjsLimit(unsigned int Objs);
	void SetIDETobjLimit(unsigned int Tobj);
	void SetWeaponLimit(unsigned int Weapon);

	//void SetIDEHier_VehiclesLimit(unsigned int Hier, unsigned int Vehicles);
	void SetIDEVehiclesLimit(unsigned int Vehicles);
	void SetIDEPedLimit(unsigned int Ped);
	void SetIDE2dfxLimit(unsigned int _2dfx);
	void SetModelIDLimit(unsigned int mID);

	void SetPtrNodePoolLimit(unsigned int nPtrNode);
	void SetEntryInfoNodePoolLimit(unsigned int nEntryInfoNode);
	void SetPedPoolLimit(unsigned int nPed);
	void SetVehiclePoolLimit(unsigned int nVehicle);
	void SetBuildingPoolLimit(unsigned int nBuilding);
	void SetTreadablePoolLimit(unsigned int nTreadable);
	void SetObjectPoolLimit(unsigned int nObject);
	void SetDummyPoolLimit(unsigned int nDummy);
	void SetAudioScriptObjectPoolLimit(unsigned int nAudioScriptObject);
	void SetColModelPoolLimit(unsigned int nColModel);

	void SetImageLimit(unsigned int img);
	
	void SetAlphaListLimit(unsigned int nAlphaList);
	void SetAlphaBoatAtomicListLimit(unsigned int nAlphaBoatAtomicList);
	void SetAlphaEntityListLimit(unsigned int nAlphaEntityList);
	void SetAlphaUnderwaterEntityListLimit(unsigned int nAlphaUnderwaterEntityList);

	void SetVisibleEntityPtrs(unsigned int nVisibleEntityPtrs);

	enum eLimitType
	{
		objs = 0,
		tobj = 1,
		weapon = 2,
		hier = 3,
		vehicles = 4,
		ped = 5
	};
};

Android_III_VC_LimitAdjuster LimitAdjuster;
