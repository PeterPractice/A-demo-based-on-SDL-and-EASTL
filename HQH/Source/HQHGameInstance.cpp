#include "HQHGameInstance.h"

HQHGameInstance::HQHGameInstance()
{
	HQH::Log("HQHGameInstance::HQHGameInstance\n");

	HQH::Random::SrandByTime();
}

HQHGameInstance::~HQHGameInstance()
{
	HQH::Log("HQHGameInstance::~HQHGameInstance\n");
}
