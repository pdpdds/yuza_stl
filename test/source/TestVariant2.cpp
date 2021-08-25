/**
 * NOTE:
 *
 * DO NOT INCLUDE EATest/EATest.h or ANY OTHER HEADER
 * There is a bug in MSVC whereby pushing/poping all warnings from a header does not reenable all warnings
 * in the TU that included the header.
 * For example C4805 will not reenabled.
 */

#include <EASTL/variant.h>

int TestVariantGeneratingComparisonOverloads()
{
	int nErrorCount = 0;

	{
		std::variant<int, float, bool> a;
		std::variant<int, float, bool> b;

		auto r = a == b;

		nErrorCount += !r;
	}

	{
		std::variant<int, float, bool> a;
		std::variant<int, float, bool> b;

		bool r = (a == b);

		nErrorCount += !r;
	}

	// A variant is permitted to hold the same type more than once, and to hold differently cv-qualified versions of the same type.

	{
		std::variant<int, int, int> a;
		std::variant<int, int, int> b;

		bool r = (a == b);

		nErrorCount += !r;
	}

	{
		std::variant<signed int, unsigned int> a;
		std::variant<signed int, unsigned int> b;

		bool r = (a == b);

		nErrorCount += !r;
	}

	{
		std::variant<int, bool> a;
		std::variant<int, bool> b;

		bool r = (a == b);

		nErrorCount += !r;
	}

	{
		std::variant<volatile int, int, const int, const volatile int> a;
		std::variant<volatile int, int, const int, const volatile int> b;

		bool r = (a == b);

		nErrorCount += !r;
	}

	{
		std::variant<volatile int, int, const int, const volatile int, bool> a;
		std::variant<volatile int, int, const int, const volatile int, bool> b;

		bool r = (a == b);

		nErrorCount += !r;
	}

	return nErrorCount;
}
