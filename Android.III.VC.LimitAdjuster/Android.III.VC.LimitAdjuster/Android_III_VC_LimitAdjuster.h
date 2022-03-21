#pragma once

class Android_III_VC_LimitAdjuster
{
public:
	void SetIDEObjsLimit(unsigned int Objs);
	void SetIDETobjLimit(unsigned int Tobj);

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

	void SetAlphaEntityListLimit(unsigned int nAlphaEntityList);
	void SetAlphaUnderwaterEntityListLimit(unsigned int nAlphaUnderwaterEntityList);

	enum eLimitType
	{
		objs = 0,
		tobj = 1
	};
};

Android_III_VC_LimitAdjuster LimitAdjuster;
