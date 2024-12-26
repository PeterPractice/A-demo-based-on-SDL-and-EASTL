#include "HQHDebugManager.h"
#include <EAStdC/EAString.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/map.h>
#include <EASTL/sort.h>

HQHDebugManager::HQHDebugManager()
{
	HQH::Log("HQHDebugManager::HQHDebugManager\n");
}

HQHDebugManager::~HQHDebugManager()
{
	HQH::Log("HQHDebugManager::~HQHDebugManager\n");
}

void HQHDebugManager::RunDebug(int flag)
{
#ifdef CP_DEBUG
	HQH::Log("HQHDebugManager::RunDebug, flag: %d.\n", flag);

	switch (flag)
	{
	case 1:
	{
		Debug1_EASTL();
	}
	break;

	case 2:
	{
		Debug2_Random();
	}
	break;
	}
#endif // CP_DEBUG
}

#ifdef CP_DEBUG
bool TestVectorSort(const int& a, const int& b)
{
	return a < b;
}

// Test EASTL
void HQHDebugManager::Debug1_EASTL()
{
	HQH::Log("HQHDebugManager::Debug1_EASTL\n");

	// Test algorithm
	{
		HQH::Log("Test algorithm:\n");

		int a = 1;
		int b = 10;
		HQH::Log("min(%d, %d): %d\n", a, b, eastl::min(a, b));
		HQH::Log("max(%d, %d): %d\n", a, b, eastl::max(a, b));

		int c = -1;
		HQH::Log("clamp(%d, %d, %d): %d\n", c, a, b, eastl::clamp(c, a, b));

		int d = 20;
		HQH::Log("clamp(%d, %d, %d): %d\n", d, a, b, eastl::clamp(d, a, b));

		int e = 6;
		HQH::Log("clamp(%d, %d, %d): %d\n", e, a, b, eastl::clamp(e, a, b));

		/* Output:
Test algorithm:
min(1, 10): 1
max(1, 10): 10
clamp(-1, 1, 10): 1
clamp(20, 1, 10): 10
clamp(6, 1, 10): 6
		*/
	}

	// Test char
	{
		HQH::Log("Test char:\n");

		const char* pChar = "Hello, EASTL.";

		char charBuffer[32];
		char* pCharBuffer = charBuffer;
		EA::StdC::Strcpy(pCharBuffer, pChar);
		EA::StdC::Strcat(pCharBuffer, "++++++++");
		
		eastl_size_t pCharLength = EA::StdC::Strlen(pChar);
		eastl_size_t pCharBufferLength = EA::StdC::Strlen(pCharBuffer);

		HQH::Log("pChar: %s pCharLength: %d.\n", pChar, pCharLength);
		HQH::Log("pCharBuffer: %s pCharBufferLength: %d.\n", pCharBuffer, pCharBufferLength);

		/* Output:
Test char:
pChar: Hello, EASTL. pCharLength: 13.
pCharBuffer: Hello, EASTL.++++++++ pCharBufferLength: 21.
		*/
	}

	// Test string
	{
		HQH::Log("Test string:\n");

		eastl::string s = "Hello, EASTL.";

		eastl_size_t sLength = s.length();

		HQH::Log("s: %s sLength: %d.\n", s.c_str(), sLength);

		/* Output:
Test string:
s: Hello, EASTL. sLength: 13.
		*/
	}

	// Test vector
	{
		HQH::Log("Test vector:\n");

		eastl::vector<int> v = {1, 2};
		v.push_back(5);
		v.push_back(4);
		v.push_back(3);

		eastl::sort(v.begin(), v.end(), TestVectorSort);

		HQH::Log("v:\n");
		for (eastl::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		{
			HQH::Log("%d\n", *it);
		}

		/* Output:
Test vector:
v:
1
2
3
4
5
		*/
	}

	// Test map
	{
		HQH::Log("Test map:\n");

		eastl::map<int, eastl::string> m = { {1, "Line 1, Hello."}, {2, "Line 2, EASTL."} };
		m.insert(eastl::make_pair(3, "Line 3, map."));
		m.insert(eastl::pair<int, eastl::string>(4, "Line 4, insert."));
		m.insert(eastl::map<int, eastl::string>::value_type(5, "Line 5, value."));
		m.insert(m.end(), eastl::make_pair(6, "Line 6, pair."));

		HQH::Log("m:\n");
		for (eastl::map<int, eastl::string>::const_iterator it = m.begin(); it != m.end(); ++it)
		{
			HQH::Log("Key: %d, Value: %s\n", it->first, it->second);
		}

		/* Output:
Test map:
m:
Key: 1, Value: Line 1, Hello.
Key: 2, Value: Line 2, EASTL.
Key: 3, Value: Line 3, map.
Key: 4, Value: Line 4, insert.
Key: 5, Value: Line 5, value.
Key: 6, Value: Line 6, pair.
		*/
	}
}

void HQHDebugManager::Debug2_Random()
{
	HQH::Log("HQHDebugManager::Debug2_Random\n");

	// Test random number
	{
		HQH::Log("Test random number:\n");

		const int n = 10;

		HQH::Log("Rand31:\n");
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::Rand31());
		}
		/* Output:
Rand31:
[0]625136513
[1]279677990
[2]1763864679
[3]1486056980
[4]1506289341
[5]691291314
[6]1272687619
[7]138631040
[8]911569337
[9]421394942
		*/

		HQH::Log("Rand:\n");
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::Rand());
		}
		/* Output:
Rand:
[0]11363
[1]22598
[2]32210
[3]24667
[4]23260
[5]4228
[6]32742
[7]22789
[8]15250
[9]3448
		*/

		HQH::Log("RandFloat:\n");
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%f\n", i, HQH::Random::RandFloat());
		}
		/* Output:
RandFloat:
[0]0.040681
[1]0.163182
[2]0.527818
[3]0.676626
[4]0.526170
[5]0.060366
[6]0.273385
[7]0.371654
[8]0.161168
[9]0.080874
		*/

		int minValue = -10;
		int maxValue = 10;
		HQH::Log("RandModRange, minValue: %d, maxValue: %d:\n", minValue, maxValue);
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::RandModRange(minValue, maxValue));
		}
		/* Output:
RandModRange, minValue: -10, maxValue: 10:
[0]9
[1]-8
[2]7
[3]-7
[4]4
[5]5
[6]-4
[7]1
[8]0
[9]-7
		*/

		minValue = -1000000;
		maxValue = 1000000;
		HQH::Log("RandModRange, minValue: %d, maxValue: %d:\n", minValue, maxValue);
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::RandModRange(minValue, maxValue));
		}
		/* Output:
RandModRange, minValue: -1000000, maxValue: 1000000:
[0]640792
[1]-31586
[2]486822
[3]-301145
[4]-285653
[5]-541942
[6]-94174
[7]-688767
[8]-511543
[9]-22411
		*/

		maxValue = 10;
		HQH::Log("Rand_0_Max, maxValue: %d:\n", maxValue);
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::Rand_0_Max(maxValue));
		}
		/* Output:
Rand_0_Max, maxValue: 10:
[0]1
[1]10
[2]7
[3]3
[4]2
[5]8
[6]5
[7]9
[8]5
[9]4
		*/

		maxValue = 1000000;
		HQH::Log("Rand_0_Max, maxValue: %d:\n", maxValue);
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::Rand_0_Max(maxValue));
		}
		/* Output:
Rand_0_Max, maxValue: 1000000:
[0]907770
[1]418099
[2]922356
[3]95644
[4]763274
[5]296787
[6]851832
[7]795650
[8]812214
[9]191899
		*/

		HQH::Log("RandD2:\n");
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::RandD2());
		}
		/* Output:
RandD2:
[0]1
[1]1
[2]0
[3]1
[4]0
[5]1
[6]1
[7]1
[8]1
[9]0
		*/

		HQH::Log("Rand_1or1:\n");
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%d\n", i, HQH::Random::Rand_1or1());
		}
		/* Output:
Rand_1or1:
[0]1
[1]-1
[2]1
[3]-1
[4]-1
[5]-1
[6]-1
[7]1
[8]1
[9]-1
		*/

		HQH::Log("RandBool:\n");
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%s\n", i, HQH::Random::RandBool() ? "true" : "false");
		}
		/* Output:
RandBool:
[0]false
[1]false
[2]true
[3]false
[4]false
[5]true
[6]false
[7]true
[8]false
[9]false
		*/

		float fMinValue = -1.0f;
		float fMaxValue = 1.0f;
		HQH::Log("RandomModRangeFloat, fMinValue: %f, fMaxValue: %f:\n", fMinValue, fMaxValue);
		for (int i = 0; n > i; ++i)
		{
			HQH::Log("[%d]%f\n", i, HQH::Random::RandomModRangeFloat(fMinValue, fMaxValue));
		}
		/* Output:
RandomModRangeFloat, fMinValue: -1.000000, fMaxValue: 1.000000:
[0]0.098483
[1]0.030061
[2]0.680959
[3]0.702078
[4]-0.236427
[5]-0.770562
[6]0.089572
[7]0.573840
[8]0.434736
[9]0.910520
		*/
	}
}

#endif // CP_DEBUG
