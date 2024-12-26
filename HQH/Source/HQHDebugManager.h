#ifndef HQHDEBUGMANAGER_H
#define HQHDEBUGMANAGER_H

#include "HQH.H"

class HQHDebugManager
{
public:
	HQHDebugManager();
	~HQHDebugManager();

	void RunDebug(int flag);

#ifdef CP_DEBUG
private:
	void Debug1_EASTL();
	void Debug2_Random();
#endif // CP_DEBUG
};
HQH_EA_STDC_SINGLETONADAPTER_SA(HQHDebugManager);

#endif // HQHDEBUGMANAGER_H
