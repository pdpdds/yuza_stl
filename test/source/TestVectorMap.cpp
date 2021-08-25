/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#include "TestMap.h"
#include "EASTLTest.h"
#include <EASTL/vector_map.h>
#include <EASTL/vector_multimap.h>
#include <EASTL/vector>
#include <EASTL/deque.h>
#include <EASTL/string.h>
#include <EASTL/fixed_string.h>
#include <EASTL/fixed_vector>
#include <EASTL/utility.h>

EA_DISABLE_ALL_VC_WARNINGS()
#ifndef EA_COMPILER_NO_STANDARD_CPP_LIBRARY
	#include <map>
#endif
EA_RESTORE_ALL_VC_WARNINGS()

using namespace std;


// Template instantations.
// These tell the compiler to compile all the functions for the given class.
template class std::vector_map<int, int>;
template class std::vector_multimap<float, int>;
template class std::vector_map<TestObject, TestObject>;
template class std::vector_multimap<TestObject, TestObject>;


///////////////////////////////////////////////////////////////////////////////
// typedefs
//
typedef std::vector_map<int, int> VM1;
typedef std::vector_map<int, int, std::less<int>, EASTLAllocatorType, std::deque<std::pair<int, int> > > VM2;

typedef std::vector_map<TestObject, TestObject> VM4;
typedef std::vector_map<TestObject, TestObject, std::less<TestObject>, EASTLAllocatorType, std::deque<std::pair<TestObject, TestObject> > > VM5;

typedef std::vector_multimap<int, int> VMM1;
typedef std::vector_multimap<int, int, std::less<int>, EASTLAllocatorType, std::deque<std::pair<int, int> > > VMM2;

typedef std::vector_multimap<TestObject, TestObject> VMM4;
typedef std::vector_multimap<TestObject, TestObject, std::less<TestObject>, EASTLAllocatorType, std::deque<std::pair<TestObject, TestObject> > > VMM5;

#ifndef EA_COMPILER_NO_STANDARD_CPP_LIBRARY
	typedef std::map<int, int> VM3;
	typedef std::map<TestObject, TestObject> VM6;
	typedef std::multimap<int, int> VMM3;
	typedef std::multimap<TestObject, TestObject> VMM6;
#endif
///////////////////////////////////////////////////////////////////////////////



int TestVectorMap()
{
	int nErrorCount = 0;

	#ifndef EA_COMPILER_NO_STANDARD_CPP_LIBRARY
		{   // Test construction
			nErrorCount += TestMapConstruction<VM1, VM3, false>();
			nErrorCount += TestMapConstruction<VM2, VM3, false>();
			nErrorCount += TestMapConstruction<VM4, VM6, false>();
			nErrorCount += TestMapConstruction<VM5, VM6, false>();

			nErrorCount += TestMapConstruction<VMM1, VMM3, true>();
			nErrorCount += TestMapConstruction<VMM2, VMM3, true>();
			nErrorCount += TestMapConstruction<VMM4, VMM6, true>();
			nErrorCount += TestMapConstruction<VMM5, VMM6, true>();
		}


		{   // Test mutating functionality.
			nErrorCount += TestMapMutation<VM1, VM3, false>();
			nErrorCount += TestMapMutation<VM2, VM3, false>();
			nErrorCount += TestMapMutation<VM4, VM6, false>();
			nErrorCount += TestMapMutation<VM5, VM6, false>();

			nErrorCount += TestMapMutation<VMM1, VMM3, true>();
			nErrorCount += TestMapMutation<VMM2, VMM3, true>();
			nErrorCount += TestMapMutation<VMM4, VMM6, true>();
			nErrorCount += TestMapMutation<VMM5, VMM6, true>();
		}
	#endif // EA_COMPILER_NO_STANDARD_CPP_LIBRARY


	{   // Test search functionality.
		nErrorCount += TestMapSearch<VM1, false>();
		nErrorCount += TestMapSearch<VM2, false>();
		nErrorCount += TestMapSearch<VM4, false>();
		nErrorCount += TestMapSearch<VM5, false>();

		nErrorCount += TestMapSearch<VMM1, true>();
		nErrorCount += TestMapSearch<VMM2, true>();
		nErrorCount += TestMapSearch<VMM4, true>();
		nErrorCount += TestMapSearch<VMM5, true>();
	}


	{
		// C++11 emplace and related functionality
		nErrorCount += TestMapCpp11<std::vector_map<int, TestObject> >();
		nErrorCount += TestMapCpp11<std::vector_map<int, TestObject, std::less<int>, EASTLAllocatorType, std::deque<std::pair<int, TestObject> > > >();

		nErrorCount += TestMultimapCpp11<std::vector_multimap<int, TestObject> >();
		nErrorCount += TestMultimapCpp11<std::vector_multimap<int, TestObject, std::less<int>, EASTLAllocatorType, std::deque<std::pair<int, TestObject> > > >();
	}


    {
        // insert at the upper bound of a range
        VMM1 vmm = {{0, 0}};
        VERIFY(vmm.emplace(0, 0) != vmm.begin());
    }


	{ // Misc tests

		// const key_compare& key_comp() const;
		// key_compare&       key_comp();
		VM2       vm;
		const VM2 vmc;

		const VM2::key_compare& kc = vmc.key_comp();
		vm.key_comp() = kc;

		// ensure count can be called from a const object
		vmc.count(0);
	}

	{
		const VMM1 vmm;

		// ensure count can be called from a const object
		vmm.count(0);
	}

	{
		// Misc testing
		typedef std::fixed_vector<std::pair<int, float>, 8> FV;
		typedef std::vector_map<int, float, std::less<int>, FV::allocator_type, FV> FixedVectorMap;

		FixedVectorMap fvm;

		for(int i = FV::kMaxSize - 1; i >= 0; i--)
			fvm.insert(std::pair<int, float>(i, (float)i));

		FixedVectorMap::iterator it = fvm.find(3);
		EATEST_VERIFY(it != fvm.end());
	}

	{
		// Misc testing
		typedef std::fixed_string<char, 16>   KeyStringType;
		typedef std::fixed_string<char, 24>   ValueStringType;
		typedef std::pair<ValueStringType, bool> StringMapValueType;

		typedef std::vector_map<KeyStringType, StringMapValueType> StringMapType;
		StringMapType stringMap;

		stringMap.reserve(20);
		EATEST_VERIFY(stringMap.capacity() == 20);

		StringMapValueType& v1 = stringMap["abc"];
		EATEST_VERIFY(strlen(v1.first.c_str()) == 0);
		v1.first.clear();
		EATEST_VERIFY(strlen(v1.first.c_str()) == 0);

		StringMapValueType& v2 = stringMap["def"];
		EATEST_VERIFY(strlen(v2.first.c_str()) == 0);
		v2.first = "def";
		EATEST_VERIFY(strlen(v2.first.c_str()) == 3);
	}

	{
		// Regression for problem observed in EAWebKit
		typedef std::vector_map<std::string, void*> TestVectorMap;

		TestVectorMap tvm;

		tvm["Parameters"]      = NULL;
		tvm["ThemeParameters"] = NULL; 
		tvm["CookieInfo"]      = NULL; 
		tvm["DiskCacheInfo"]   = NULL; 
		tvm["RamCacheInfo"]    = NULL;
		tvm["SSLCert"]         = NULL;
		tvm["AllowedDomain"]   = NULL;
	}

	{     // find_as predicate
		{ // vector_map
			std::vector_map<string, int> vss = {{"abc", 11},   {"def", 22}, {"ghi", 33}, {"jklmnop", 44},
												  {"qrstu", 55}, {"vw", 66},  {"x", 77},   {"yz", 88}};
			VERIFY(vss.find_as("GHI", TestStrCmpI_2()) != vss.end());
		}

		{ // const vector_map
			const std::vector_map<string, int> vss = {{"abc", 11},   {"def", 22}, {"ghi", 33}, {"jklmnop", 44},
														{"qrstu", 55}, {"vw", 66},  {"x", 77},   {"yz", 88}};
			VERIFY(vss.find_as("GHI", TestStrCmpI_2()) != vss.end());
		}

		// vector_multimap
		{
			std::vector_multimap<string, int> vss = {{"abc", 11},   {"def", 22}, {"ghi", 33}, {"jklmnop", 44},
													   {"qrstu", 55}, {"vw", 66},  {"x", 77},   {"yz", 88}};
			VERIFY(vss.find_as("GHI", TestStrCmpI_2()) != vss.end());
		}

		// const vector_multimap
		{
			const std::vector_multimap<string, int> vss = {{"abc", 11},   {"def", 22}, {"ghi", 33}, {"jklmnop", 44},
															 {"qrstu", 55}, {"vw", 66},  {"x", 77},   {"yz", 88}};
			VERIFY(vss.find_as("GHI", TestStrCmpI_2()) != vss.end());
		}
	}

	return nErrorCount;
}












