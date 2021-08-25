/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#include <EABase/eabase.h>
#include <EAAssert/eaassert.h>
#include "EASTLTest.h"
#include <EASTL/memory.h>
#include <EASTL/functional.h>
#include <EASTL/hash_set.h>
#include <EASTL/set.h>
#include <EASTL/list.h>
#include <EAStdC/EAString.h>

EA_DISABLE_ALL_VC_WARNINGS()
#include <functional>
EA_RESTORE_ALL_VC_WARNINGS()

namespace
{

	// Used for std::function tests
	static int TestIntRet(int* p)
	{
		int ret = *p;
		*p += 1;
		return ret;
	}

	// Used for str_less tests below.
	template <typename T>
	struct Results
	{
		const T* p1;
		const T* p2;
		bool     expectedResult; // The expected result of the expression (p1 < p2)
	};


	// Used for const_mem_fun_t below.
	struct X
	{
		X() { }
		void DoNothing() const { }
	};

	template <typename T>
	void foo(typename T::argument_type arg)
	{
		typename T::result_type (T::*pFunction)(typename T::argument_type) const = &T::operator();
		T t(&X::DoNothing);
		(t.*pFunction)(arg);
	}


	// Used for equal_to_2 tests below.
	struct N1{
		N1(int x) : mX(x) { }
		int mX;
	};

	struct N2{
		N2(int x) : mX(x) { }
		int mX;
	};

	bool operator==(const N1& n1, const N1& n1a){ return (n1.mX == n1a.mX); }
	bool operator==(const N1& n1, const N2& n2) { return (n1.mX == n2.mX); }
	bool operator==(const N2& n2, const N1& n1) { return (n2.mX == n1.mX); }

	bool operator!=(const N1& n1, const N1& n1a){ return (n1.mX != n1a.mX); }
	bool operator!=(const N1& n1, const N2& n2) { return (n1.mX != n2.mX); }
	bool operator!=(const N2& n2, const N1& n1) { return (n2.mX != n1.mX); }

	bool operator< (const N1& n1, const N1& n1a){ return (n1.mX  < n1a.mX); }
	bool operator< (const N1& n1, const N2& n2) { return (n1.mX  < n2.mX); }
	bool operator< (const N2& n2, const N1& n1) { return (n2.mX  < n1.mX); }


	// Used for mem_fun tests below.
	struct TestClass
	{
		mutable int mX;

		TestClass() : mX(37) { }

		void Increment()
		{
			mX++;
		}

		void IncrementConst() const
		{
			mX++;
		}

		int MultiplyBy(int x)
		{
			return mX * x;
		}

		int MultiplyByConst(int x) const
		{
			return mX * x;
		}
	};
}


// Template instantations.
// These tell the compiler to compile all the functions for the given class.
typedef std::basic_string<char8_t,  MallocAllocator> String8MA;
typedef std::basic_string<char16_t, MallocAllocator> String16MA;

template struct std::string_hash<String8MA>;
template struct std::string_hash<String16MA>;

template class std::hash_set<String8MA,  std::string_hash<String8MA> >;
template class std::hash_set<String16MA, std::string_hash<String16MA> >;


// Helper function for testing our default hash implementations for pod types which
// simply returns the static_cast<size_t> of the val passed in
template<typename T>
int TestHashHelper(T val)
{
	int nErrorCount = 0;

	EATEST_VERIFY(std::hash<T>()(val) == static_cast<size_t>(val));

	return nErrorCount;
}

///////////////////////////////////////////////////////////////////////////////
// TestFunctional
//
int TestFunctional()
{
	using namespace std;

	int nErrorCount = 0;

	{
		// str_equal_to
		char p0[] = "";
		char p1[] = "hello";
		char p2[] = "world";
		char p3[] = "helllllo";
		char p4[] = "hello"; // Intentionally the same value as p1.

		// str_equal_to
		typedef hash_set<const char*, hash<const char*>, str_equal_to<const char*> > StringHashSet;
		StringHashSet shs;

		shs.insert(p1);
		shs.insert(p2);
		shs.insert(p3);

		StringHashSet::iterator it = shs.find(p0);
		EATEST_VERIFY(it == shs.end());

		it = shs.find(p1);
		EATEST_VERIFY(it != shs.end());

		it = shs.find(p2);
		EATEST_VERIFY(it != shs.end());

		it = shs.find(p4);
		EATEST_VERIFY(it != shs.end());
	}

	{
		// str_less<const char8_t*>
		Results<char> results8[] =
		{
			{      "",          "", false },
			{      "",         "a",  true },
			{      "a",         "", false },
			{      "a",        "a", false },
			{      "a",        "b",  true },
			{  "____a",    "____a", false },
			{  "____a",    "____b",  true },
			{  "____b",    "____a", false },
			{  "_\xff",       "_a", false },    // Test high values, which exercises the signed/unsiged comparison behavior.
			{     "_a",    "_\xff",  true }
		};

		str_less<const char*> sl8;
		for(size_t i = 0; i < EAArrayCount(results8); i++)
		{
			// Verify that our test is in line with the strcmp function.
			bool bResult = (EA::StdC::Strcmp(results8[i].p1, results8[i].p2) < 0);
			EATEST_VERIFY_F(bResult == results8[i].expectedResult, "Strcmp failure, test %zu. Expected \"%s\" to be %sless than \"%s\"", i, results8[i].p1, results8[i].expectedResult ? "" : "not ", results8[i].p2);

			// Verify that str_less achieves the expected results.
			bResult = sl8(results8[i].p1, results8[i].p2);
			EATEST_VERIFY_F(bResult == results8[i].expectedResult, "str_less test failure, test %zu. Expected \"%s\" to be %sless than \"%s\"", i, results8[i].p1, results8[i].expectedResult ? "" : "not ", results8[i].p2);
		}

		// str_less<const wchar_t*>
		Results<wchar_t> resultsW[] =
		{
			{        L"",            L"", false },
			{        L"",           L"a",  true },
			{        L"a",           L"", false },
			{        L"a",          L"a", false },
			{        L"a",          L"b",  true },
			{    L"____a",      L"____a", false },
			{    L"____a",      L"____b",  true },
			{    L"____b",      L"____a", false },
			{  L"_\xffff",         L"_a", false },   // Test high values, which exercises the signed/unsiged comparison behavior.
			{       L"_a",    L"_\xffff",  true }
		};

		str_less<const wchar_t*> slW;
		for(size_t i = 0; i < EAArrayCount(resultsW); i++)
		{
			// Verify that our test is in line with the strcmp function.
			bool bResult = (EA::StdC::Strcmp(resultsW[i].p1, resultsW[i].p2) < 0);
			EATEST_VERIFY_F(bResult == resultsW[i].expectedResult, "Strcmp failure, test %zu. Expected \"%s\" to be %sless than \"%s\"", i, results8[i].p1, results8[i].expectedResult ? "" : "not ", results8[i].p2);

			// Verify that str_less achieves the expected results.
			bResult = slW(resultsW[i].p1, resultsW[i].p2);
			EATEST_VERIFY_F(bResult == resultsW[i].expectedResult, "str_less test failure, test %zu. Expected \"%ls\" to be %sless than \"%ls\"", i, resultsW[i].p1, resultsW[i].expectedResult ? "" : "not ", resultsW[i].p2);
		}
	}

	{
		// str_less
		char p0[] = "";
		char p1[] = "hello";
		char p2[] = "world";
		char p3[] = "helllllo";
		char p4[] = "hello"; // Intentionally the same value as p1.

		typedef set<const char*, str_less<const char*> > StringSet;
		StringSet ss;

		ss.insert(p1);
		ss.insert(p2);
		ss.insert(p3);

		StringSet::iterator it = ss.find(p0);
		EATEST_VERIFY(it == ss.end());

		it = ss.find(p1);
		EATEST_VERIFY(it != ss.end());

		it = ss.find(p2);
		EATEST_VERIFY(it != ss.end());

		it = ss.find(p4);
		EATEST_VERIFY(it != ss.end());
	}

	{
		// equal_to_2
		N1 n11(1);
		N1 n13(3);
		N2 n21(1);
		N2 n22(2);
		//const N1 cn11(1);
		//const N1 cn13(3);

		equal_to_2<N1, N2> e;
		EATEST_VERIFY(e(n11, n21));
		EATEST_VERIFY(e(n21, n11));

		equal_to_2<N1, N1> es;
		EATEST_VERIFY(es(n11, n11));

		//equal_to_2<const N1, N1> ec; // To do: Make this case work.
		//EATEST_VERIFY(e(cn11, n11));

		// not_equal_to_2
		not_equal_to_2<N1, N2> n;
		EATEST_VERIFY(n(n11, n22));
		EATEST_VERIFY(n(n22, n11));

		not_equal_to_2<N1, N1> ns;
		EATEST_VERIFY(ns(n11, n13));

		// less_2
		less_2<N1, N2> le;
		EATEST_VERIFY(le(n11, n22));
		EATEST_VERIFY(le(n22, n13));

		less_2<N1, N1> les;
		EATEST_VERIFY(les(n11, n13));
	}


	{
		// Test defect report entry #297.
		const X x;
		foo< const_mem_fun_t<void, X> >(&x);
	}


	{
		// mem_fun (no argument version)
		TestClass  tc0, tc1, tc2;
		TestClass* tcArray[3] = { &tc0, &tc1, &tc2 };

		for_each(tcArray, tcArray + 3, mem_fun(&TestClass::Increment));
		EATEST_VERIFY((tc0.mX == 38) && (tc1.mX == 38) && (tc2.mX == 38));

		for_each(tcArray, tcArray + 3, mem_fun(&TestClass::IncrementConst));
		EATEST_VERIFY((tc0.mX == 39) && (tc1.mX == 39) && (tc2.mX == 39));
	}


	{
		// mem_fun (one argument version)
		TestClass  tc0, tc1, tc2;
		TestClass* tcArray[3]  = { &tc0, &tc1, &tc2 };
		int        intArray1[3] = { -1,  0,  2 };
		int        intArray2[3] = { -9, -9, -9 };

		transform(tcArray, tcArray + 3, intArray1, intArray2, mem_fun(&TestClass::MultiplyBy));
		EATEST_VERIFY((intArray2[0] == -37) && (intArray2[1] == 0) && (intArray2[2] == 74));

		intArray2[0] = intArray2[1] = intArray2[2] = -9;
		transform(tcArray, tcArray + 3, intArray1, intArray2, mem_fun(&TestClass::MultiplyByConst));
		EATEST_VERIFY((intArray2[0] == -37) && (intArray2[1] == 0) && (intArray2[2] == 74));
	}


	{
		// mem_fun_ref (no argument version)
		TestClass tcArray[3];

		for_each(tcArray, tcArray + 3, mem_fun_ref(&TestClass::Increment));
		EATEST_VERIFY((tcArray[0].mX == 38) && (tcArray[1].mX == 38) && (tcArray[2].mX == 38));

		for_each(tcArray, tcArray + 3, mem_fun_ref(&TestClass::IncrementConst));
		EATEST_VERIFY((tcArray[0].mX == 39) && (tcArray[1].mX == 39) && (tcArray[2].mX == 39));
	}


	{
		// mem_fun_ref (one argument version)
		TestClass tcArray[3];
		int       intArray1[3] = { -1,  0,  2 };
		int       intArray2[3] = { -9, -9, -9 };

		transform(tcArray, tcArray + 3, intArray1, intArray2, mem_fun_ref(&TestClass::MultiplyBy));
		EATEST_VERIFY((intArray2[0] == -37) && (intArray2[1] == 0) && (intArray2[2] == 74));

		intArray2[0] = intArray2[1] = intArray2[2] = -9;
		transform(tcArray, tcArray + 3, intArray1, intArray2, mem_fun_ref(&TestClass::MultiplyByConst));
		EATEST_VERIFY((intArray2[0] == -37) && (intArray2[1] == 0) && (intArray2[2] == 74));
	}


	{
		// Template instantations.
		// These tell the compiler to compile all the functions for the given class.
		std::hash_set<String8MA,  std::string_hash<String8MA> >  hs8;
		std::hash_set<String16MA, std::string_hash<String16MA> > hs16;

		EATEST_VERIFY(hs8.empty());
		EATEST_VERIFY(hs16.empty());
	}

	{
		// unary_compose
		/*
		std::vector<double> angles;
		std::vector<double> sines;

		std::transform(angles.begin(), angles.end(), sines.begin(),
				  std::compose1(std::negate<double>(),
						   std::compose1(std::ptr_fun(sin),
									std::bind2nd(std::multiplies<double>(), 3.14159 / 180.0))));
		*/

		// binary_compose
		list<int> L;

		std::list<int>::iterator in_range =
			 std::find_if(L.begin(), L.end(),
					 std::compose2(std::logical_and<bool>(),
							  std::bind2nd(std::greater_equal<int>(), 1),
							  std::bind2nd(std::less_equal<int>(), 10)));
		EATEST_VERIFY(in_range == L.end());
	}

	{
		nErrorCount += TestHashHelper<int>(4330);
		nErrorCount += TestHashHelper<bool>(true);
		nErrorCount += TestHashHelper<char>('E');
		nErrorCount += TestHashHelper<signed char>('E');
		nErrorCount += TestHashHelper<unsigned char>('E');
		nErrorCount += TestHashHelper<char8_t>('E');
		nErrorCount += TestHashHelper<char16_t>(0xEAEA);
		nErrorCount += TestHashHelper<char32_t>(0x00EA4330);
		#if !defined(EA_WCHAR_T_NON_NATIVE)
			nErrorCount += TestHashHelper<wchar_t>(L'E');
		#endif
		nErrorCount += TestHashHelper<signed short>(4330);
		nErrorCount += TestHashHelper<unsigned short>(4330u);
		nErrorCount += TestHashHelper<signed int>(4330);
		nErrorCount += TestHashHelper<unsigned int>(4330u);
		nErrorCount += TestHashHelper<signed long>(4330l);
		nErrorCount += TestHashHelper<unsigned long>(4330ul);
		nErrorCount += TestHashHelper<signed long long>(4330ll);
		nErrorCount += TestHashHelper<unsigned long long>(4330ll);
		nErrorCount += TestHashHelper<float>(4330.099999f);
		nErrorCount += TestHashHelper<double>(4330.055);
		nErrorCount += TestHashHelper<long double>(4330.0654l);

		{
			enum hash_enum_test { e1, e2, e3 };
			nErrorCount += TestHashHelper<hash_enum_test>(e1);
			nErrorCount += TestHashHelper<hash_enum_test>(e2);
			nErrorCount += TestHashHelper<hash_enum_test>(e3);
		}
	}


#if defined(EA_COMPILER_CPP11_ENABLED) && EASTL_VARIADIC_TEMPLATES_ENABLED
	// On platforms do not support variadic templates the std::invoke (std::mem_fn is built on std::invoke)
	// implementation is extremely basic and does not hold up.  A significant amount of code would have to be written
	// and I don't believe the investment is justified at this point.  If you require this functionality on older
	// compilers please contact us.
	//

	// std::invoke
	{
		struct TestStruct
		{
			TestStruct(int inValue) : value(inValue) {}
			void Add(int addAmount) { value += addAmount; }
			int GetValue() { return value; }
			int& GetValueReference() { return value; }
			int value;
		};

		struct TestFunctor
		{
			void operator()() { called = true; }
			bool called = false;
		};

		struct TestFunctorArguments
		{
			void operator()(int i) { value = i; }
			int value = 0;
		};

		{
			TestStruct a(42);
			std::invoke(&TestStruct::Add, a, 10);
			EATEST_VERIFY(a.value == 52);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::Add), TestStruct, int>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::Add), TestStruct, int>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			std::invoke(&TestStruct::Add, &a, 10);
			EATEST_VERIFY(a.value == 52);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::Add), TestStruct *, int>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::Add), TestStruct *, int>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			std::reference_wrapper<TestStruct> r(a);
			std::invoke(&TestStruct::Add, r, 10);
			EATEST_VERIFY(a.value == 52);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::Add), std::reference_wrapper<TestStruct>, int>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::Add), std::reference_wrapper<TestStruct>, int>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			std::invoke(&TestStruct::GetValueReference, a) = 43;
			EATEST_VERIFY(a.value == 43);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::GetValueReference), TestStruct &>::type, int &>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::GetValueReference), TestStruct &>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			EATEST_VERIFY(std::invoke(&TestStruct::value, a) == 42);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::value), TestStruct &>::type, int &>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::value), TestStruct &>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			std::invoke(&TestStruct::value, a) = 43;
			EATEST_VERIFY(a.value == 43);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::value), TestStruct &>::type, int &>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::value), TestStruct &>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			std::invoke(&TestStruct::value, &a) = 43;
			EATEST_VERIFY(a.value == 43);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::value), TestStruct *>::type, int &>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::value), TestStruct *>::value, "incorrect value for is_invocable");
		}
		{
			TestStruct a(42);
			std::reference_wrapper<TestStruct> r(a);
			std::invoke(&TestStruct::value, r) = 43;
			EATEST_VERIFY(a.value == 43);

			static_assert(std::is_same<typename std::invoke_result<decltype(&TestStruct::value), std::reference_wrapper<TestStruct>>::type, int &>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(&TestStruct::GetValue), std::reference_wrapper<TestStruct>>::value, "incorrect value for is_invocable");
		}

		#ifndef EA_COMPILER_GNUC
		{
			TestStruct a(42);
			EATEST_VERIFY(std::invoke(&TestStruct::GetValue, a) == 42);

			static_assert(
			    std::is_same<typename std::invoke_result<decltype(&TestStruct::GetValue), TestStruct*>::type, int>::value,
			    "incorrect type for invoke_result");

			static_assert(std::is_invocable<decltype(&TestStruct::GetValue), TestStruct*>::value, "incorrect value for is_invocable");
		}
		#endif
		{
			TestFunctor f;
			std::invoke(f);
			EATEST_VERIFY(f.called);

			static_assert(std::is_same<typename std::invoke_result<decltype(f)>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(f)>::value, "incorrect value for is_invocable");
		}
		{
			TestFunctorArguments f;
			std::invoke(f, 42);
			EATEST_VERIFY(f.value == 42);

			static_assert(std::is_same<typename std::invoke_result<decltype(f), int>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(f), int>::value, "incorrect value for is_invocable");
		}
		{
			static bool called = false;
			auto f = [] {called = true;};
			std::invoke(f);
			EATEST_VERIFY(called);

			static_assert(std::is_same<typename std::invoke_result<decltype(f)>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(f)>::value, "incorrect value for is_invocable");
		}
		{
			static int value = 0;
			auto f = [](int i) {value = i;};
			std::invoke(f, 42);
			EATEST_VERIFY(value == 42);

			static_assert(std::is_same<typename std::invoke_result<decltype(f), int>::type, void>::value, "incorrect type for invoke_result");
			static_assert(std::is_invocable<decltype(f), int>::value, "incorrect value for is_invocable");
		}
		{
			struct A {};
			struct B : public A {};

			struct TestStruct
			{
				A a() { return A(); };
				B b() { return B(); };
			};

			static_assert(!std::is_invocable_r<B, decltype(&TestStruct::a), TestStruct>::value, "incorrect value for is_invocable_r");
			static_assert(std::is_invocable_r<A, decltype(&TestStruct::b), TestStruct>::value, "incorrect value for is_invocable_r");
			static_assert(std::is_invocable_r<B, decltype(&TestStruct::b), TestStruct>::value, "incorrect value for is_invocable_r");
		}
	}

	// std::mem_fn
	{
		struct AddingStruct
		{
			AddingStruct(int inValue) : value(inValue) {}
			void Add(int addAmount) { value += addAmount; }
			void Add2(int add1, int add2) { value += (add1 + add2); }
			int value;
		};

		struct OverloadedStruct
		{
			OverloadedStruct(int inValue) : value(inValue) {}
			int &Value() { return value; }
			const int &Value() const { return value; }
			int value;
		};

		{
			AddingStruct a(42);
			std::mem_fn(&AddingStruct::Add)(a, 6);
			EATEST_VERIFY(a.value == 48);
		}
		{
			AddingStruct a(42);
			std::mem_fn(&AddingStruct::Add2)(a, 3, 3);
			EATEST_VERIFY(a.value == 48);
		}
		{
			AddingStruct a(42);
			auto fStructAdd = std::mem_fn(&AddingStruct::Add);
			fStructAdd(a,6);
			EATEST_VERIFY(a.value == 48);
		}
		{
			OverloadedStruct a(42);
			EATEST_VERIFY(std::mem_fn<int &()>(&OverloadedStruct::Value)(a) == 42);
			EATEST_VERIFY(std::mem_fn<const int &() const>(&OverloadedStruct::Value)(a) == 42);
		}
	}
#endif

	// std::function
	{
		{
			{
				struct Functor { int operator()() { return 42; } };
				std::function<int(void)> fn = Functor();
				EATEST_VERIFY(fn() == 42);
			}

			{
				struct Functor { int operator()(int in) { return in; } };
				std::function<int(int)> fn = Functor();
				EATEST_VERIFY(fn(24) == 24);
			}
		}

		{
			int val = 0;
			auto lambda = [&val] { ++val; };
			{
				std::function<void(void)> ff = std::bind(lambda);
				ff();
				VERIFY(val == 1);
			}
			{
				std::function<void(void)> ff = nullptr;
				ff = std::bind(lambda);
				ff();
				VERIFY(val == 2);
			}
		}

		{
			int val = 0;
			{
				std::function<int(int*)> ff = &TestIntRet;
				int ret = ff(&val);
				EATEST_VERIFY(ret == 0);
				EATEST_VERIFY(val == 1);
			}
			{
				std::function<int(int*)> ff;
				ff = &TestIntRet;
				int ret = ff(&val);
				EATEST_VERIFY(ret == 1);
				EATEST_VERIFY(val == 2);
			}
		}

		{
			struct Test { int x = 1; };
			Test t;
			const Test ct;

			{
				std::function<int(const Test&)> ff = &Test::x;
				int ret = ff(t);
				EATEST_VERIFY(ret == 1);
			}
			{
				std::function<int(const Test&)> ff = &Test::x;
				int ret = ff(ct);
				EATEST_VERIFY(ret == 1);
			}
			{
				std::function<int(const Test&)> ff;
				ff = &Test::x;
				int ret = ff(t);
				EATEST_VERIFY(ret == 1);
			}
			{
				std::function<int(const Test&)> ff;
				ff = &Test::x;
				int ret = ff(ct);
				EATEST_VERIFY(ret == 1);
			}
		}

		{
			struct TestVoidRet
			{
				void IncX() const
				{
					++x;
				}

				void IncX()
				{
					++x;
				}

				mutable int x = 0;
			};

			TestVoidRet voidRet;
			const TestVoidRet cvoidRet;

			{
				std::function<void(const TestVoidRet&)> ff = static_cast<void(TestVoidRet::*)() const>(&TestVoidRet::IncX);
				ff(cvoidRet);
				VERIFY(cvoidRet.x == 1);
			}
			{
				std::function<void(const TestVoidRet&)> ff = static_cast<void(TestVoidRet::*)() const>(&TestVoidRet::IncX);
				ff(voidRet);
				VERIFY(voidRet.x == 1);
			}
			{
				std::function<void(TestVoidRet&)> ff = static_cast<void(TestVoidRet::*)()>(&TestVoidRet::IncX);
				ff(voidRet);
				VERIFY(voidRet.x == 2);
			}
		}

		{
			int val = 0;
			struct Functor { void operator()(int* p) { *p += 1; } };
			Functor functor;
			{
				std::function<void(int*)> ff = std::reference_wrapper<Functor>(functor);
				ff(&val);
				EATEST_VERIFY(val == 1);
			}

			{
				std::function<void(int*)> ff;
				ff = std::reference_wrapper<Functor>(functor);
				ff(&val);
				EATEST_VERIFY(val == 2);
			}
		}

		{
			{
				auto lambda = []{};
				EA_UNUSED(lambda);
				static_assert(internal::is_functor_inplace_allocatable<decltype(lambda), EASTL_FUNCTION_DEFAULT_CAPTURE_SSO_SIZE>::value == true, "lambda equivalent to function pointer does not fit in std::function local memory.");
			}

			{
				std::function<void(void)> fn;

				EATEST_VERIFY(!fn);
				fn =  [] {};
				EATEST_VERIFY(!!fn);
			}

			{
				std::function<int(int)> fn = [](int param) { return param; };
				EATEST_VERIFY(fn(42) == 42);
			}

			{
				std::function<int(int)> fn = ReturnVal;
				EATEST_VERIFY(fn(42) == 42);
			}

			{
				std::function<int()> fn0 = ReturnZero;
				std::function<int()> fn1 = ReturnOne;

				EATEST_VERIFY(fn0() == 0 && fn1() == 1);
				swap(fn0, fn1);
				EATEST_VERIFY(fn0() == 1 && fn1() == 0);
			}

			{
				std::function<int()> fn0 = ReturnZero;
				std::function<int()> fn1 = ReturnOne;

				EATEST_VERIFY(fn0() == 0 && fn1() == 1);
				fn0 = fn1;
				EATEST_VERIFY(fn0() == 1 && fn1() == 1);
			}

			{
				std::function<int()> fn0 = ReturnZero;
				std::function<int()> fn1 = ReturnOne;

				EATEST_VERIFY(fn0() == 0 && fn1() == 1);
				fn0 = std::move(fn1);
				EATEST_VERIFY(fn0() == 1 && fn1 == nullptr);
			}

			{
				std::function<int(int)> f1(nullptr);
				EATEST_VERIFY(!f1);

				std::function<int(int)> f2 = nullptr;
				EATEST_VERIFY(!f2);
			}
		}

		{
			// test the default allocator path by using a lambda capture too large to fit into the std::function local
			// storage.
			uint64_t a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
			std::function<uint64_t(void)> fn = [=] { return a + b + c + d + e + f; };
			auto result = fn();
			EATEST_VERIFY(result == 21);
		}

		{
			struct Functor { void operator()() { return; } };
			std::function<void(void)> fn;
			std::function<void(void)> fn2 = nullptr;
			EATEST_VERIFY(!fn);
			EATEST_VERIFY(!fn2);
			EATEST_VERIFY(fn == nullptr);
			EATEST_VERIFY(fn2 == nullptr);
			EATEST_VERIFY(nullptr == fn);
			EATEST_VERIFY(nullptr == fn2);
			fn = Functor();
			fn2 = Functor();
			EATEST_VERIFY(!!fn);
			EATEST_VERIFY(!!fn2);
			EATEST_VERIFY(fn != nullptr);
			EATEST_VERIFY(fn2 != nullptr);
			EATEST_VERIFY(nullptr != fn);
			EATEST_VERIFY(nullptr != fn2);
			fn = nullptr;
			fn2 = fn;
			EATEST_VERIFY(!fn);
			EATEST_VERIFY(!fn2);
			EATEST_VERIFY(fn == nullptr);
			EATEST_VERIFY(fn2 == nullptr);
			EATEST_VERIFY(nullptr == fn);
			EATEST_VERIFY(nullptr == fn2);
		}

		{
			using std::swap;
			struct Functor { int operator()() { return 5; } };
			std::function<int(void)> fn = Functor();
			std::function<int(void)> fn2;
			EATEST_VERIFY(fn() == 5);
			EATEST_VERIFY(!fn2);
			fn.swap(fn2);
			EATEST_VERIFY(!fn);
			EATEST_VERIFY(fn2() == 5);
			swap(fn, fn2);
			EATEST_VERIFY(fn() == 5);
			EATEST_VERIFY(!fn2);
		}

		{
			uint64_t a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
			std::function<uint64_t(void)> fn([=] { return a + b + c + d + e + f; });

			auto result = fn();
			EATEST_VERIFY(result == 21);
		}

		// user regression "self assigment" tests
		{
			std::function<int(void)> fn = [cache = 0] () mutable  { return cache++; };

			EATEST_VERIFY(fn() == 0);
			EATEST_VERIFY(fn() == 1);
			EATEST_VERIFY(fn() == 2);

			EA_DISABLE_CLANG_WARNING(-Wunknown-pragmas)
			EA_DISABLE_CLANG_WARNING(-Wunknown-warning-option)
			EA_DISABLE_CLANG_WARNING(-Wself-assign-overloaded)
			fn = fn;
			EA_RESTORE_CLANG_WARNING()
			EA_RESTORE_CLANG_WARNING()
			EA_RESTORE_CLANG_WARNING()

			EATEST_VERIFY(fn() == 3);
			EATEST_VERIFY(fn() == 4);
			EATEST_VERIFY(fn() == 5);

			fn = std::move(fn);

			EATEST_VERIFY(fn() == 6);
			EATEST_VERIFY(fn() == 7);
			EATEST_VERIFY(fn() == 8);
		}

		// user regression for memory leak when re-assigning an std::function which already holds a large closure.
		{
				static int sCtorCount = 0;
				static int sDtorCount = 0;

				{
					struct local
					{
						local() { sCtorCount++; }
						local(const local&) {  sCtorCount++; }
						local(local&&)  {  sCtorCount++; }
						~local() { sDtorCount++; }

						void operator=(const local&) = delete; // suppress msvc warning
					} l;

					std::function<bool()> f;

					f = [l]() { return false; };

					// ensure closure resources are cleaned up when assigning to a non-null std::function.
					f = [l]() { return true; };
				}

				EATEST_VERIFY(sCtorCount == sDtorCount);
		}
	}

	// Checking _MSC_EXTENSIONS is required because the Microsoft calling convention classifiers are only available when
	// compiler specific C/C++ language extensions are enabled.
	#if defined(EA_PLATFORM_MICROSOFT) && defined(_MSC_EXTENSIONS)
	{
		// no arguments
		typedef void(__stdcall * StdCallFunction)();
		typedef void(__cdecl * CDeclFunction)();

		// only varargs
		typedef void(__stdcall * StdCallFunctionWithVarargs)(...);
		typedef void(__cdecl * CDeclFunctionWithVarargs)(...);

		// arguments and varargs
		typedef void(__stdcall * StdCallFunctionWithVarargsAtEnd)(int, int, int, ...);
		typedef void(__cdecl * CDeclFunctionWithVarargsAtEnd)(int, short, long, ...);

		static_assert(!std::is_function<StdCallFunction>::value, "is_function failure");
		static_assert(!std::is_function<CDeclFunction>::value, "is_function failure");
		static_assert(std::is_function<typename std::remove_pointer<StdCallFunction>::type>::value, "is_function failure");
		static_assert(std::is_function<typename std::remove_pointer<CDeclFunction>::type>::value, "is_function failure");
		static_assert(std::is_function<typename std::remove_pointer<StdCallFunctionWithVarargs>::type>::value, "is_function failure");
		static_assert(std::is_function<typename std::remove_pointer<CDeclFunctionWithVarargs>::type>::value, "is_function failure");
		static_assert(std::is_function<typename std::remove_pointer<StdCallFunctionWithVarargsAtEnd>::type>::value, "is_function failure");
		static_assert(std::is_function<typename std::remove_pointer<CDeclFunctionWithVarargsAtEnd>::type>::value, "is_function failure");
	}
	#endif

	// Test Function Objects
	#if defined(EA_COMPILER_CPP14_ENABLED)
	{
		// std::plus<void>
		{
			{
				auto result = std::plus<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 42);
			}

			{
				auto result = std::plus<>{}(40.0, 2.0);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 42.0);
			}

			{
				auto result = std::plus<>{}(std::string("4"), "2");
				EA_UNUSED(result);
				EATEST_VERIFY(result == "42");
			}
		}

		// std::minus<void>
		{
			{
				auto result = std::minus<>{}(6, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 4);
			}

			{
				auto result = std::minus<>{}(6.0, 2.0);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 4.0);
			}
		}

		// std::multiplies
		{
			{
				auto result = std::multiplies<>{}(6, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 12);
			}

			{
				auto result = std::multiplies<>{}(6.0, 2.0);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 12.0);
			}
		}


		// std::divides
		{
			{
				auto result = std::divides<>{}(6, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 3);
			}

			{
				auto result = std::divides<>{}(6.0, 2.0);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 3.0);
			}
		}

		// std::modulus
		{
			{
				auto result = std::modulus<>{}(6, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 0);
			}

			{
				auto result = std::modulus<>{}(7, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result == 1);
			}
		}

		// std::negate
		{
			{
				auto result = std::negate<>{}(42);
				EA_UNUSED(result);
				EATEST_VERIFY(result == -42);
			}

			{
				auto result = std::negate<>{}(42.0);
				EA_UNUSED(result);
				EATEST_VERIFY(result == -42.0);
			}
		}

		// std::equal_to
		{
			{
				auto result = std::equal_to<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}

			{
				auto result = std::equal_to<>{}(40, 40);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}
		}

		// std::not_equal_to
		{
			{
				auto result = std::not_equal_to<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}

			{
				auto result = std::not_equal_to<>{}(40, 40);
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}
		}

		// std::greater<void>
		{
			{
				auto result = std::greater<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}

			{
				auto result = std::greater<>{}(1, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}

			{
				auto result = std::greater<>{}(std::string("4"), "2");
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}
		}

		// std::less<void>
		{
			{
				auto result = std::less<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}

			{
				auto result = std::less<>{}(1, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}

			{
				auto result = std::less<>{}(std::string("4"), "2");
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}
		}

		// std::greater_equal<void>
		{
			{
				auto result = std::greater_equal<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}

			{
				auto result = std::greater_equal<>{}(40, 40);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}

			{
				auto result = std::greater_equal<>{}(40, 43);
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}
		}

		// std::less_equal<void>
		{
			{
				auto result = std::less_equal<>{}(40, 2);
				EA_UNUSED(result);
				EATEST_VERIFY(!result);
			}

			{
				auto result = std::less_equal<>{}(40, 40);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}

			{
				auto result = std::less_equal<>{}(40, 43);
				EA_UNUSED(result);
				EATEST_VERIFY(result);
			}
		}

		// std::logical_and
		{
			auto result = std::logical_and<>{}(true, true);
			EATEST_VERIFY(result);
			result = std::logical_and<>{}(true, false);
			EATEST_VERIFY(!result);
			result = std::logical_and<>{}(false, true);
			EATEST_VERIFY(!result);
			result = std::logical_and<>{}(false, false);
			EATEST_VERIFY(!result);

			bool b = false;
			result = std::logical_and<>{}(b, false);
			EATEST_VERIFY(!result);
		}

		// std::logical_or
		{
			auto result = std::logical_or<>{}(true, true);
			EATEST_VERIFY(result);
			result = std::logical_or<>{}(true, false);
			EATEST_VERIFY(result);
			result = std::logical_or<>{}(false, true);
			EATEST_VERIFY(result);
			result = std::logical_or<>{}(false, false);
			EATEST_VERIFY(!result);

			bool b = false;
			result = std::logical_or<>{}(b, false);
			EATEST_VERIFY(!result);
			result = std::logical_or<>{}(b, true);
			EATEST_VERIFY(result);
		}

		// std::logical_not
		{
			auto result = std::logical_not<>{}(true);
			EATEST_VERIFY(!result);
			result = std::logical_not<>{}(result);
			EATEST_VERIFY(result);
			result = std::logical_not<>{}(false);
			EATEST_VERIFY(result);
		}
	}
	#endif

	// not_fn
	{
		{
			auto ft = std::not_fn([] { return true; });
			auto ff = std::not_fn([] { return false; });

			EATEST_VERIFY(ft() == false);
			EATEST_VERIFY(ff() == true);
		}
	}

	// reference_wrapper
	{
		// operator T&
		{
			int i = 0;
			std::reference_wrapper<int> r(i);
			int &j = r;
			j = 42;

			EATEST_VERIFY(i == 42);
		}

		// get
		{
			int i = 0;
			std::reference_wrapper<int> r(i);
			r.get() = 42;

			EATEST_VERIFY(i == 42);
		}

		// copy constructor
		{
			int i = 0;
			std::reference_wrapper<int> r(i);
			std::reference_wrapper<int> copy(r);
			copy.get() = 42;

			EATEST_VERIFY(i == 42);
		}

		// assignment
		{
			int i = 0;
			int j = 0;

			std::reference_wrapper<int> r1(i);
			std::reference_wrapper<int> r2(j);

			r2 = r1; // rebind r2 to refer to i
			r2.get() = 42;

			EATEST_VERIFY(i == 42);
			EATEST_VERIFY(j == 0);
		}

		// invoke
		{
			struct Functor
			{
				bool called = false;
				void operator()() {called = true;}
			};

			Functor f;
			std::reference_wrapper<Functor> r(f);
			r();

			EATEST_VERIFY(f.called == true);
		}

		// ref/cref
		{
			{
				int i = 0;
				std::reference_wrapper<int> r1 = std::ref(i);
				r1.get() = 42;

				std::reference_wrapper<int> r2 = std::ref(r1);

				EATEST_VERIFY(i == 42);
				EATEST_VERIFY(r2 == 42);
			}

			{
				int i = 1337;
				std::reference_wrapper<const int> r1 = std::cref(i);
				EATEST_VERIFY(r1 == 1337);

				std::reference_wrapper<const int> r2 = std::cref(r1);
				EATEST_VERIFY(r2 == 1337);
			}
		}
	}

	return nErrorCount;
}

// Test that we can instantiate invoke_result with incorrect argument types.
// This should be instantiable, but should not have a `type` typedef.
struct TestInvokeResult
{
	int f(int i) {return i;}
};

template struct std::invoke_result<decltype(&TestInvokeResult::f), TestInvokeResult, void>;
static_assert(!std::is_invocable<decltype(&TestInvokeResult::f), TestInvokeResult, void>::value, "incorrect value for is_invocable");
static_assert(std::is_invocable<decltype(&TestInvokeResult::f), TestInvokeResult, int>::value, "incorrect value for is_invocable");
