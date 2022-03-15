#pragma once

class Android_III_VC_LimitAdjuster
{
public:
	//void SetIDELimit(unsigned int iObjectsType1);
	void SetPtrNodePoolLimit(unsigned int nPtrNode);
	void SetEntryInfoNodePoolLimit(unsigned int nEntryInfoNode);

	void SetBuildingPoolLimit(unsigned int nBuilding);
	void SetObjectPoolLimit(unsigned int nObject);

	void SetDummyPoolLimit(unsigned int nDummy);
	void SetColModelPoolLimit(unsigned int nColModel);
};

Android_III_VC_LimitAdjuster LimitAdjuster;

