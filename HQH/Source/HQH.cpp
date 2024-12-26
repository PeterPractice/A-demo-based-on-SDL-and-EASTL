#include "HQH.H"
#include <EAMain/EAMain.h>

namespace HQH
{
    uint64_t Time()
    {
        return EA::StdC::GetTime();
    }

    const eastl::string& GetLogTimeString()
    {
        const int S_LENGTH = 25;
        static eastl::string s = "[2024.06.18-10.47.02:139]";
        s.clear();

        const uint64_t t = HQH::Time(); // nanoseconds

        //const time_t nTime = time(NULL);
        const time_t nTime = t / NANOSECONDS_IN_1_SECONDS;
        const struct tm* pTime = localtime(&nTime);
        const uint64_t iMilliseconds = (t / MICROSECONDS_IN_1_SECONDS) % MILLISECONDS_IN_1_SECONDS;

        int result = EA::StdC::StringPrintf(s, "[%4d.%02d.%02d-%02d.%02d.%02d:%03d]", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, iMilliseconds);
        EA_ASSERT(S_LENGTH == result);

        return s;
    }

    void ReportDefault(const char8_t* pMessage)
    {
        if (!pMessage)
        {
            return;
        }

        // It's possible that the underlying print back end can't handle large
        // output sizes. For example, the OutputDebugStringA call below drops
        // chars beyond about 4096.
        size_t       length = EA::StdC::Strlen(pMessage); // It might be faster to make a custom Strlen which quits after N chars.
        //const size_t kMaxLength = 1024;
#if defined(EA_PLATFORM_DESKTOP)
        const int kMaxLength = 2048;
#else
        const int kMaxLength = 512;
#endif

        if (length > kMaxLength)
        {
            EA_FAIL();

            for (size_t i = 0, copiedLength = 0; i < length; i += copiedLength)
            {
                char8_t buffer[kMaxLength + 1];
                size_t  c;

                copiedLength = ((length - i) >= kMaxLength) ? kMaxLength : (length - i);
                for (c = 0; c < copiedLength; c++)
                    buffer[c] = pMessage[i + c];
                buffer[c] = 0;
                ReportDefault(buffer);
            }
        }
        else
        {
#if defined(EA_PLATFORM_MICROSOFT) && !defined(CS_UNDEFINED_STRING) // No need to do this for Microsoft console platforms, as the fputs below covers that.
            OutputDebugStringA(GetLogTimeString().c_str());
            OutputDebugStringA(pMessage);
#endif

#if defined(EA_PLATFORM_ANDROID)
            // Android doesn't implement stdio (e.g. fputs), though sometimes we use compiler
            // linking statements to redirect stdio functions to our own implementations which
            // allow it to work.
            //
            // __android_log_write can write only 512 bytes at a time. Normally we don't write
            // so much text in unit test output, but if this becomes a problem then we can loop
            // and write blocks of the output. The primary downside to such an approach is that
            // __android_log_write appends a \n to your output for each call. See the EAStdC
            // EASprintfCore.cpp code for example loop code.
            AndroidReport(pMessage);
#else
            fputs(pMessage, stdout);
            fflush(stdout);
#endif
        }
    }

	void Log(const char8_t* pFormat, ...)
	{
        // EA::EAMain::Report, can only pass 3 valid arguments, from 4th arguments it will be a invalid value.
		//EA::EAMain::Report(pFormat);

        va_list arguments;
        va_start(arguments, pFormat);
        EA::EAMain::VReport(pFormat, arguments);
        va_end(arguments);
	}

    namespace Random
    {
        static uint32_t seed = 1;

        uint32_t RandBase()
        {
            // LCG: https://en.wikipedia.org/wiki/Linear_congruential_generator
            seed = seed * 1103515245 + 12345;   // glibc (used by GCC), ANSI C: Watcom, Digital Mars, CodeWarrior, IBM VisualAge C/C++
            //seed = seed * 214013 + 2531011;   // Microsoft Visual/QuickC/C++

            return seed;
        }

        uint32_t Rand31()
        {
            return RandBase() & RANDOM_31_MAX;
        }

        uint32_t Rand()
        {
            return (RandBase() >> 16) & RANDOM_MAX;
        }

        void Srand(uint32_t seedValue)
        {
            seed = seedValue;
        }

        void SrandByTime()
        {
            Srand((uint32_t)HQH::Time());
        }

        float RandFloat()
        {
            return Rand() * RANDOM_MAX_1;
        }

        int RandomModRangeInt(int minValue, int maxValue)
        {
            if (!(minValue <= maxValue))
            {
                EA_FAIL();

                return minValue;
            }

            const uint32_t m = maxValue - minValue + 1;
            EA_ASSERT((RANDOM_31_MAX + 1) >= m); // Large maxValue will be invalid

            return minValue + (Rand31() % m);
        }

        int RandModRange(int minValue, int maxValue)
        {
            if (!(minValue <= maxValue))
            {
                EA_FAIL();

                return minValue;
            }

            const uint32_t m = maxValue - minValue + 1;
            //EA_ASSERT((RANDOM_MAX + 1) >= m); // Large maxValue will be invalid
            if (!((RANDOM_MAX + 1) >= m))
            {
                return RandomModRangeInt(minValue, maxValue);
            }

            return minValue + (Rand() % m);
        }

        uint32_t Rand_0_Max(uint32_t maxValue)
        {
            return RandModRange(0, maxValue);
        }

        uint32_t RandD2()
        {
            return Rand_0_Max(1);
        }

        int Rand_1or1()
        {
			return (0 == RandD2()) ? -1 : 1;
        }

        bool RandBool()
        {
            return 0 != RandD2();
        }

        float RandomModRangeFloat(float minValue, float maxValue)
        {
            if (!(minValue <= maxValue))
            {
                EA_FAIL();

                return minValue;
            }

            return minValue + ((maxValue - minValue) * RandFloat());
        }
    } // Random
} // HQH
