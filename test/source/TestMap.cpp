/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#include "TestMap.h"
#include "EASTLTest.h"
#include <EASTL/map.h>
#include <EASTL/string.h>
#include <EASTL/vector>

EA_DISABLE_ALL_VC_WARNINGS()
#ifndef EA_COMPILER_NO_STANDARD_CPP_LIBRARY
	#include <map>
#endif
EA_RESTORE_ALL_VC_WARNINGS()

using namespace std;


// Template instantations.
// These tell the compiler to compile all the functions for the given class.
template class std::map<int, int>;
template class std::multimap<int, int>;
template class std::map<TestObject, TestObject>;
template class std::multimap<TestObject, TestObject>;


///////////////////////////////////////////////////////////////////////////////
// typedefs
//
typedef std::map<int, int> VM1;
typedef std::map<TestObject, TestObject> VM4;
typedef std::multimap<int, int> VMM1;
typedef std::multimap<TestObject, TestObject> VMM4;

#ifndef EA_COMPILER_NO_STANDARD_CPP_LIBRARY
	typedef std::map<int, int> VM3;
	typedef std::map<TestObject, TestObject> VM6;
	typedef std::multimap<int, int> VMM3;
	typedef std::multimap<TestObject, TestObject> VMM6;
#endif

///////////////////////////////////////////////////////////////////////////////



int TestMap()
{
	int nErrorCount = 0;

	#ifndef EA_COMPILER_NO_STANDARD_CPP_LIBRARY
		{   // Test construction
			nErrorCount += TestMapConstruction<VM1, VM3, false>();
			nErrorCount += TestMapConstruction<VM4, VM6, false>();

			nErrorCount += TestMapConstruction<VMM1, VMM3, true>();
			nErrorCount += TestMapConstruction<VMM4, VMM6, true>();
		}


		{   // Test mutating functionality.
			nErrorCount += TestMapMutation<VM1, VM3, false>();
			nErrorCount += TestMapMutation<VM4, VM6, false>();

			nErrorCount += TestMapMutation<VMM1, VMM3, true>();
			nErrorCount += TestMapMutation<VMM4, VMM6, true>();
		}
	#endif // EA_COMPILER_NO_STANDARD_CPP_LIBRARY


	{   // Test searching functionality.
		nErrorCount += TestMapSearch<VM1, false>();
		nErrorCount += TestMapSearch<VM4, false>();

		nErrorCount += TestMapSearch<VMM1, true>();
		nErrorCount += TestMapSearch<VMM4, true>();
	}


	{
		// C++11 emplace and related functionality
		nErrorCount += TestMapCpp11<std::map<int, TestObject>>();
		nErrorCount += TestMultimapCpp11<std::multimap<int, TestObject>>();
		nErrorCount += TestMapCpp11NonCopyable<std::map<int, NonCopyable>>();
	}

	{
		// C++17 try_emplace and related functionality
		nErrorCount += TestMapCpp17<std::map<int, TestObject>>();
	}


	{ // Misc tests

		// const key_compare& key_comp() const;
		// key_compare&       key_comp();
		VM1       vm;
		const VM1 vmc;

		const VM1::key_compare& kc = vmc.key_comp();
		vm.key_comp() = kc;
	}


	// Regressions against user bug reports.
	{
		// User reports that the following doesn't compile on GCC 4.1.1 due to unrecognized lower_bound.
		std::map<int, int> m;
		m[1] = 1;
		EATEST_VERIFY(m.size() == 1);
		m.erase(1);
		EATEST_VERIFY(m.empty());
	}

	{
		// User reports that EASTL_VALIDATE_COMPARE_ENABLED / EASTL_COMPARE_VALIDATE isn't compiling for this case.
		std::map<std::u8string, int> m; 
		m.find_as(EA_CHAR8("some string"), std::equal_to_2<std::u8string, const char8_t*>()); 
	}

	{
		// User reports that vector<map<enum,enum>> is crashing after the recent changes to add rvalue move and emplace support to rbtree.
		typedef std::map<int, int>     IntIntMap;
		typedef std::vector<IntIntMap> IntIntMapArray;

		IntIntMapArray v;
		v.push_back(IntIntMap());           // This was calling the rbtree move constructor, which had a bug.
		v[0][16] = 0;                       // The rbtree was in a bad internal state and so this line resulted in a crash.
		EATEST_VERIFY(v[0].validate());
		EATEST_VERIFY(v.validate());
	}

	{
		typedef std::map<int, int>     IntIntMap;
		IntIntMap map1;

		#if EASTL_EXCEPTIONS_ENABLED
			EATEST_VERIFY_THROW(map1.at(0));
		#endif
		map1[0]=1;
		#if EASTL_EXCEPTIONS_ENABLED
			EATEST_VERIFY_NOTHROW(map1.at(0));
		#endif
		EATEST_VERIFY(map1.at(0) == 1);

		const IntIntMap map2;
		const IntIntMap map3(map1);

		#if EASTL_EXCEPTIONS_ENABLED
			EATEST_VERIFY_THROW(map2.at(0));
			EATEST_VERIFY_NOTHROW(map3.at(0));
		#endif
		EATEST_VERIFY(map3.at(0) == 1);
	}

	// User regression test
	{
	#if !EASTL_RBTREE_LEGACY_SWAP_BEHAVIOUR_REQUIRES_COPY_CTOR
		typedef std::map<int, MoveOnlyTypeDefaultCtor> IntMOMap;

		IntMOMap m1, m2;
		m2[0] = MoveOnlyTypeDefaultCtor(0);
		m2[1] = MoveOnlyTypeDefaultCtor(1);

		EATEST_VERIFY( m1.empty());
		EATEST_VERIFY(!m2.empty());

		m1.swap(m2);

		EATEST_VERIFY(!m1.empty());
		EATEST_VERIFY( m2.empty());
	#endif
	}

//    todo:  create a test case for this.
//    {	
//      // User reports that an incorrectly wrapped pair key used to insert into an eastl map compiles when it should fire a compiler error about unconvertible types.
//		typedef std::pair<std::string, std::string> PairStringKey;
//        typedef std::map<PairStringKey, std::string> PairStringMap;
//
//        PairStringMap p1, p2;		
//
//        p1.insert(PairStringMap::value_type(PairStringKey("key1", "key2"), "data")).first->second = "other_data";
//
//        PairStringKey key("key1", "key2");
//		PairStringMap::value_type insert_me(key, "data");
//        p2.insert(insert_me).first->second = "other_data";
//
//		for(auto& e : p1)
//			printf("%s,%s = %s\n", e.first.first.c_str(), e.first.second.c_str(), e.second.c_str());
//
//		for(auto& e : p2)
//			printf("%s,%s = %s\n", e.first.first.c_str(), e.first.second.c_str(), e.second.c_str());
//
//        EATEST_VERIFY(p1 == p2); 
//    }

	{ // Test empty base-class optimization
		struct UnemptyLess : std::less<int>
		{
			int foo;
		};

		typedef std::map<int, int, std::less<int>> VM1;
		typedef std::map<int, int, UnemptyLess> VM2;

		EATEST_VERIFY(sizeof(VM1) < sizeof(VM2));
	}

	{ // Test erase_if
		std::map<int, int> m = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
		std::erase_if(m, [](auto p) { return p.first % 2 == 0; });
		VERIFY((m == std::map<int, int>{{1, 1},{3, 3}}));
	}

	{ // Test erase_if
		std::multimap<int, int> m = {{0, 0}, {0, 0}, {0, 0}, {1, 1}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {4, 4}, {4, 4}};
		std::erase_if(m, [](auto p) { return p.first % 2 == 0; });
		VERIFY((m == std::multimap<int, int>{{1, 1}, {1, 1}, {3, 3}}));
	}

	return nErrorCount;
}











