#ifndef HQH_H
#define HQH_H

#include <stdio.h>
#include <EAStdC/EASingleton.h>
#include <EAStdC/EAString.h>
#include <EAStdC/EADateTime.h>
#include <EAStdC/EASprintf.h>
#include <EASTL/string.h>
#if defined(EA_PLATFORM_MICROSOFT)
    #include <Windows.h>
#endif

#define CP_DEBUG

// SingletonAdapter
// Reference: \HQH7\EASTL-3.21.12\test\packages\EAStdC\test\source\TestSingleton.cpp, SingletonExplicit.
#define HQH_EA_STDC_SINGLETONADAPTER_SA(_ClassName) \
class _ClassName##SA : public EA::StdC::SingletonAdapter<_ClassName> \
{ \
}

namespace HQH
{
    const uint64_t MILLISECONDS_IN_1_SECONDS = UINT64_C(1000);
    const uint64_t MICROSECONDS_IN_1_SECONDS = UINT64_C(1000000);
    const uint64_t NANOSECONDS_IN_1_SECONDS = UINT64_C(1000000000);

    // Returns nanoseconds
    uint64_t Time();

    const eastl::string& GetLogTimeString();

    // Reference: \HQH7\EASTL-3.21.12\test\packages\EAMain\source\EAMain.cpp, static void ReportDefault(const char8_t* pMessage).
    void ReportDefault(const char8_t* pMessage);

	void Log(const char8_t* pFormat, ...);

	namespace Random
	{
        const uint32_t RANDOM_31_MAX = 0x7fffffff; // 2147483647
        // Reference: C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt\stdlib.h, RAND_MAX.
        const uint32_t RANDOM_MAX = 0x7fff; // 32767
        const float RANDOM_MAX_1 = 1.0f / float(RANDOM_MAX);

        // Reference 1: \HQH7\EASTL-3.21.12\test\packages\EAStdC\include\EAStdC\EARandom.h, RandomLinearCongruential.
        // Reference 2: https://en.wikipedia.org/wiki/Linear_congruential_generator.
        // Returns a pseudorandom number in the range[0, 2147483647]. Source: glibc (used by GCC).
        uint32_t Rand31();
        // Returns a pseudorandom number in the range[0, 32767]. Source: ANSI C: Watcom, Digital Mars, CodeWarrior, IBM VisualAge C/C++, C90, C99, C11: Suggestion in the ISO/IEC 9899, C17.
        uint32_t Rand();
        void Srand(uint32_t seedValue);
        void SrandByTime();

		// Returns a pseudorandom float number in the range[0.0, 1.0].
        float RandFloat();

        // Returns a pseudorandom number in the range[minValue, maxValue].
        int RandModRange(int minValue, int maxValue);

        // Returns a pseudorandom number in the range[0, maxValue].
        uint32_t Rand_0_Max(uint32_t maxValue);

        // Returns 0 or 1.
        uint32_t RandD2();
        // Returns -1 or 1.
		int Rand_1or1();
        // Returns true or false.
        bool RandBool();

        // Returns a pseudorandom float number in the range[minValue, maxValue].
        float RandomModRangeFloat(float minValue, float maxValue);
	} // Random
} // HQH

#endif // HQH_H
