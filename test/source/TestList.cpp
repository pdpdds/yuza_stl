/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "EASTLTest.h"
#include <EASTL/list.h>
#include <EASTL/sort>
#include <EASTL/fixed_allocator.h>

using namespace std;

// Template instantations.
// These tell the compiler to compile all the functions for the given class.
template class std::list<bool>;
template class std::list<int>;
template class std::list<Align64>;
template class std::list<TestObject>;
// template class std::list<std::unique_ptr<int>>;


int TestList()
{
	int nErrorCount = 0;

	// list();
	{
		std::list<int> l;
		VERIFY(l.size() == 0);
		VERIFY(l.empty());
		VERIFY(l.validate());
		VERIFY(l.begin() == l.end());
	}

	// list(const allocator_type& allocator);
	{
		MallocAllocator::reset_all();
		MallocAllocator mallocator;
		{
			std::list<int, MallocAllocator> l(mallocator);
			VERIFY(l.get_allocator() == mallocator);
			l.push_front(42);
			VERIFY(MallocAllocator::mAllocCountAll != 0);
		}
		VERIFY(MallocAllocator::mAllocCountAll == MallocAllocator::mFreeCountAll);
	}

	// explicit list(size_type n, const allocator_type& allocator = EASTL_LIST_DEFAULT_ALLOCATOR);
	{
		const int test_size = 42;
		std::list<int> l(test_size);
		VERIFY(!l.empty());
		VERIFY(l.size() == test_size);
		VERIFY(l.validate());

		VERIFY(std::all_of(l.begin(), l.end(), [](int e)
		                     { return e == 0; }));
	}

	// list(size_type n, const value_type& value, const allocator_type& allocator = EASTL_LIST_DEFAULT_ALLOCATOR);
	{
		const int test_size = 42;
		const int test_val = 435;

		std::list<int> l(42, test_val);
		VERIFY(!l.empty());
		VERIFY(l.size() == test_size);
		VERIFY(l.validate());

		VERIFY(std::all_of(l.begin(), l.end(), [=](int e)
		                     { return e == test_val; }));
	}

	// list(const this_type& x);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> b(a); 
		VERIFY(a == b);
		VERIFY(a.validate());
		VERIFY(a.size() == b.size());
		VERIFY(b.validate());
	}

	// list(const this_type& x, const allocator_type& allocator);
	{
		MallocAllocator mallocator;
		std::list<int, MallocAllocator> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int, MallocAllocator> b(a, mallocator);
		VERIFY(a == b);
		VERIFY(a.validate());
		VERIFY(a.size() == b.size());
		VERIFY(b.validate());
		VERIFY(a.get_allocator() == b.get_allocator());
	}

	// list(this_type&& x);
	// list(this_type&&, const allocator_type&);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		VERIFY(!a.empty());
		VERIFY(a.size() == 10);
		VERIFY(a.validate());

		std::list<int> b(std::move(a)); 
		VERIFY(a.empty());
		VERIFY(!b.empty());
		VERIFY(a.size() == 0);
		VERIFY(b.size() == 10);

		VERIFY(a != b);
		VERIFY(a.size() != b.size());
		VERIFY(a.validate());
		VERIFY(b.validate());
	}

	// list(std::initializer_list<value_type> ilist, const allocator_type& allocator = EASTL_LIST_DEFAULT_ALLOCATOR);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::for_each(a.begin(), a.end(), [&](int e)
		                {
			                static int inc = 0;
			                VERIFY(inc++ == e);
			            });
	}

	// list(InputIterator first, InputIterator last); 
	{
		std::list<int> ref = {3, 4, 5, 6, 7};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto start = a.begin();
		std::advance(start, 3);

		auto end = start;
		std::advance(end, 5);

		std::list<int> b(start, end); 

		VERIFY(b == ref);
		VERIFY(a.validate());
		VERIFY(b.validate());

		VERIFY(a.size() == 10);
		VERIFY(b.size() == 5);		

		VERIFY(!b.empty());
		VERIFY(!a.empty());
	}

	// this_type& operator=(const this_type& x);
	// this_type& operator=(std::initializer_list<value_type> ilist);
	// this_type& operator=(this_type&& x);
	{
		const std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> b = a;
		VERIFY(a.validate());
		VERIFY(b.validate());
		VERIFY(a.size() == 10);
		VERIFY(b.size() == 10);		
		VERIFY(!a.empty());
		VERIFY(!b.empty());
		VERIFY(b == a);

		std::list<int> c = std::move(b);
		VERIFY(b.empty());

		VERIFY(c == a);
		VERIFY(c.size() == 10);
		VERIFY(c.validate());
	}

	// void swap(this_type& x);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> b = {};

		VERIFY(a.validate());
		VERIFY(b.validate());
		VERIFY(!a.empty());
		VERIFY(b.empty());

		b.swap(a);

		VERIFY(a.validate());
		VERIFY(b.validate());
		VERIFY(a.empty());
		VERIFY(!b.empty());
	}

	// void assign(size_type n, const value_type& value);
	{
		std::list<int> ref = {42, 42, 42, 42};
		std::list<int> a = {0, 1, 2, 3};
		a.assign(4, 42);
		VERIFY(a == ref);
		VERIFY(a.validate());
		VERIFY(!a.empty());
		VERIFY(a.size() == 4);
	}

	// void assign(InputIterator first, InputIterator last);  
	{
		std::list<int> ref = std::list<int>{3, 4, 5, 6, 7};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> b;

		auto start = a.begin();
		std::advance(start, 3);

		auto end = start;
		std::advance(end, 5);

		b.assign(start, end); 

		VERIFY(b == ref);
		VERIFY(a.validate());
		VERIFY(b.validate());

		VERIFY(a.size() == 10);
		VERIFY(b.size() == 5);		

		VERIFY(!b.empty());
		VERIFY(!a.empty());
	}
																
	// void assign(std::initializer_list<value_type> ilist);
	{
		std::list<int> ref = std::list<int>{3, 4, 5, 6, 7};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> b;

		auto start = a.begin();
		std::advance(start, 3);

		auto end = start;
		std::advance(end, 5);

		b.assign(start, end); 

		VERIFY(b == ref);
		VERIFY(a.validate());
		VERIFY(b.validate());

		VERIFY(a.size() == 10);
		VERIFY(b.size() == 5);		

		VERIFY(!b.empty());
		VERIFY(!a.empty());
	}

	// iterator       begin() 
	// const_iterator begin() const 
	// const_iterator cbegin() const 
	// iterator       end() 
	// const_iterator end() const 
	// const_iterator cend() const 
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		{
			static int inc = 0;
			auto iter = a.begin();
			while(iter != a.end())
			{
				VERIFY(*iter++ == inc++);				
			}
		}

		{
			static int inc = 0;
			auto iter = a.cbegin();
			while(iter != a.cend())
			{
				VERIFY(*iter++ == inc++);
			}
		}
	}

	// reverse_iterator       rbegin()
	// const_reverse_iterator rbegin() const
	// const_reverse_iterator crbegin() const
	// reverse_iterator       rend()
	// const_reverse_iterator rend() const
	// const_reverse_iterator crend() const 
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		{
			static int inc = 9;
			auto iter = a.rbegin();
			while(iter != a.rend())
			{
				VERIFY(*iter == inc--);
				iter++;
			}
		}

		{
			static int inc = 9;
			auto iter = a.crbegin();
			while(iter != a.crend())
			{
				VERIFY(*iter == inc--);
				iter++;
			}
		}
	}

	// bool empty() const 
	{
		{
			std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			VERIFY(!a.empty());
		}

		{
			std::list<int> a = {};
			VERIFY(a.empty());
		}
	}

	// size_type size() const
	{
		{
			std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			VERIFY(a.size() == 10);
		}

		{
			std::list<int> a = {0, 1, 2, 3, 4};
			VERIFY(a.size() == 5);
		}

		{
			std::list<int> a = {0, 1};
			VERIFY(a.size() == 2);
		}

		{
			std::list<int> a = {};
			VERIFY(a.size() == 0);
		}
	}

	// void resize(size_type n, const value_type& value);
	// void resize(size_type n);
	{
		{
			std::list<int> a;
			a.resize(10);
			VERIFY(a.size() == 10);
			VERIFY(!a.empty());
			VERIFY(std::all_of(a.begin(), a.end(), [](int i)
			                     { return i == 0; }));
		}

		{
			std::list<int> a;
			a.resize(10, 42);
			VERIFY(a.size() == 10);
			VERIFY(!a.empty());
			VERIFY(std::all_of(a.begin(), a.end(), [](int i)
			                     { return i == 42; }));
		}
	}

	// reference       front();
	// const_reference front() const;
	{
		{
			std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			VERIFY(a.front() == 0);

			a.front() = 42;
			VERIFY(a.front() == 42);
		}

		{
			const std::list<int> a = {5, 6, 7, 8, 9};
			VERIFY(a.front() == 5);
		}

		{
			std::list<int> a = {9};
			VERIFY(a.front() == 9);

			a.front() = 42;
			VERIFY(a.front() == 42);
		}
	}

	// reference       back();
	// const_reference back() const;
	{
		{
			std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			VERIFY(a.back() == 9);

			a.back() = 42;
			VERIFY(a.back() == 42);
		}

		{
			const std::list<int> a = {5, 6, 7, 8, 9};
			VERIFY(a.back() == 9);
		}

		{
			std::list<int> a = {9};
			VERIFY(a.back() == 9);

			a.back() = 42;
			VERIFY(a.back() == 42);
		}
	}

	// void emplace_front(Args&&... args);
	// void emplace_front(value_type&& value);
	// void emplace_front(const value_type& value);
	{
		std::list<int> ref = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		std::list<int> a;

		for(int i = 0; i < 10; i++)
			a.emplace_front(i);

		VERIFY(a == ref);
	}

	// template <typename... Args>
	// void emplace_back(Args&&... args);
	// void emplace_back(value_type&& value);
	// void emplace_back(const value_type& value);
	{
		{
			std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			std::list<int> a;

			for(int i = 0; i < 10; i++)
				a.emplace_back(i);

			VERIFY(a == ref);
		}

		{
			struct A
			{
				A() : mValue(0) {}
				A(int in) : mValue(in) {}
				int mValue;
				bool operator==(const A& other) const { return mValue == other.mValue; }
			};

			{
				std::list<A> ref = {{1}, {2}, {3}};
				std::list<A> a;

				a.emplace_back(1);
				a.emplace_back(2);
				a.emplace_back(3);

				VERIFY(a == ref);
			}

			{
				std::list<A> ref = {{1}, {2}, {3}};
				std::list<A> a;

				a.emplace_back(A(1));
				a.emplace_back(A(2));
				a.emplace_back(A(3));

				VERIFY(a == ref);
			}


			{
				std::list<A> ref = {{1}, {2}, {3}};
				std::list<A> a;

				A a1(1);
				A a2(2);
				A a3(3);

				a.emplace_back(a1);
				a.emplace_back(a2);
				a.emplace_back(a3);

				VERIFY(a == ref);
			}
		}
	}

	// void push_front(const value_type& value);
	// void push_front(value_type&& x);
	// reference push_front();
	{
		{
			std::list<int> ref = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
			std::list<int> a;

			for(int i = 0; i < 10; i++)
				a.push_front(i);

			VERIFY(a == ref);

		}

		{
			std::list<int> a;
			auto& front_ref = a.push_front();
			front_ref = 42;
			VERIFY(a.front() == 42);
		}
	}

	// void* push_front_uninitialized();
	{
		std::list<int> a;
		for (unsigned i = 0; i < 100; i++)
		{
			VERIFY(a.push_front_uninitialized() != nullptr);
			VERIFY(a.size() == (i + 1));
		}
	}

	// void push_back(const value_type& value);
	// void push_back(value_type&& x);
	{
		{
			std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			std::list<int> a;

			for(int i = 0; i < 10; i++)
				a.push_back(i);

			VERIFY(a == ref);
		}

		{
			struct A { int mValue; };
			std::list<A> a;
			a.push_back(A{42});
			VERIFY(a.back().mValue == 42);
		}
	}

	// reference push_back();
	{
		std::list<int> a;
		auto& back_ref = a.push_back();
		back_ref = 42;
		VERIFY(a.back() == 42);
	}

	// void* push_back_uninitialized();
	{
		std::list<int> a;
		for (unsigned int i = 0; i < 100; i++)
		{
			VERIFY(a.push_back_uninitialized() != nullptr);
			VERIFY(a.size() == (i + 1));
		}
	}

	// void pop_front();
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for(unsigned i = 0; i < 10; i++)
		{
			VERIFY(unsigned(a.front()) == i);
			a.pop_front();
		}
	}

	// void pop_back();
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for(unsigned i = 0; i < 10; i++)
		{
			VERIFY(unsigned(a.back()) == (9 - i));
			a.pop_back();
		}
	}

	// iterator emplace(const_iterator position, Args&&... args);
	// iterator emplace(const_iterator position, value_type&& value);
	// iterator emplace(const_iterator position, const value_type& value);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 42, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto insert_pos = a.begin();
		std::advance(insert_pos, 5);

		a.emplace(insert_pos, 42);
		VERIFY(a == ref);
	}

	// iterator insert(const_iterator position);
	// iterator insert(const_iterator position, const value_type& value);
	// iterator insert(const_iterator position, value_type&& x);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 42, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto insert_pos = a.begin();
		std::advance(insert_pos, 5);

		a.insert(insert_pos, 42);
		VERIFY(a == ref);
	}

	// void insert(const_iterator position, size_type n, const value_type& value);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 42, 42, 42, 42, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto insert_pos = a.begin();
		std::advance(insert_pos, 5);

		auto result = a.insert(insert_pos, 4, 42);
		VERIFY(a == ref);
		VERIFY(*result == 42);
		VERIFY(*(--result) == 4);
	}

	// void insert(const_iterator position, InputIterator first, InputIterator last);
	{
		std::list<int> to_insert = {42, 42, 42, 42};
		std::list<int> ref = {0, 1, 2, 3, 4, 42, 42, 42, 42, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto insert_pos = a.begin();
		std::advance(insert_pos, 5);

		auto result = a.insert(insert_pos, to_insert.begin(), to_insert.end());
		VERIFY(a == ref);
		VERIFY(*result == 42);
		VERIFY(*(--result) == 4);
	}

	// iterator insert(const_iterator position, std::initializer_list<value_type> ilist);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 42, 42, 42, 42, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto insert_pos = a.begin();
		std::advance(insert_pos, 5);

		a.insert(insert_pos, {42, 42, 42, 42});
		VERIFY(a == ref);
	}

	// iterator erase(const_iterator position);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 1, 2, 3, 4, 42, 5, 6, 7, 8, 9};

		auto erase_pos = a.begin();
		std::advance(erase_pos, 5);

		auto iter_after_removed = a.erase(erase_pos);
		VERIFY(*iter_after_removed == 5);
		VERIFY(a == ref);
	}

	// iterator erase(const_iterator first, const_iterator last);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 42, 42, 42, 42, 5, 6, 7, 8, 9};
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto erase_begin = a.begin();
		std::advance(erase_begin, 5);

		auto erase_end = erase_begin;
		std::advance(erase_end, 4);

		a.erase(erase_begin, erase_end);
		VERIFY(a == ref);
	}

	// reverse_iterator erase(const_reverse_iterator position);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 42, 5, 6, 7, 8, 9};
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto erase_rbegin = a.rbegin();
		std::advance(erase_rbegin, 5);

		auto iter_after_remove = a.erase(erase_rbegin);
		VERIFY(*iter_after_remove == 4);
		VERIFY(a == ref);

	}

	// reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 42, 42, 42, 42, 5, 6, 7, 8, 9};
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto erase_crbegin = a.crbegin();
		auto erase_crend = a.crbegin();
		std::advance(erase_crbegin, 4);
		std::advance(erase_crend, 8);

		auto iter_after_removed = a.erase(erase_crbegin, erase_crend);
		VERIFY(*iter_after_removed == 4);
		VERIFY(a == ref);
	}

	// void clear()
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		a.clear();
		VERIFY(a.empty());
		VERIFY(a.size() == 0);
	}

	// void reset_lose_memory()    
	{
		typedef std::list<int, fixed_allocator> IntList;
		typedef IntList::node_type                IntListNode;
		const size_t  kBufferCount = 10;
		IntListNode   buffer1[kBufferCount];
		IntList       intList1;
		const size_t  kAlignOfIntListNode = EA_ALIGN_OF(IntListNode);
		intList1.get_allocator().init(buffer1, sizeof(buffer1), sizeof(IntListNode), kAlignOfIntListNode);

		intList1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		VERIFY(!intList1.empty());
		VERIFY(intList1.size() == 10);
		intList1.reset_lose_memory();
		VERIFY(intList1.empty());
		VERIFY(intList1.size() == 0);
	}

	// void remove(const T& x);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> ref = {0, 1, 2, 3, 5, 6, 7, 8, 9};
		a.remove(4);
		VERIFY(a == ref);
	}

	// void remove_if(Predicate);
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> ref = {0, 1, 2, 3, 5, 6, 7, 8, 9};
		a.remove_if([](int e) { return e == 4; });
		VERIFY(a == ref);
	}

	// void reverse()
	{
		std::list<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> ref = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		a.reverse();
		VERIFY(a == ref);
	}

	// void splice(const_iterator position, this_type& x);
	{
		const std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a1 = {0, 1, 2, 3, 4};
		std::list<int> a2 = {5, 6, 7, 8, 9};

		std::list<int> a;
		a.splice(a.begin(), a2);
		a.splice(a.begin(), a1);

		VERIFY(a == ref);
		VERIFY(a1.empty());
		VERIFY(a2.empty());
	}

	// void splice(const_iterator position, this_type& x, const_iterator i);
	{
		const std::list<int> ref = {0, 5};
		std::list<int> a1 = {-1, -1, 0};
		std::list<int> a2 = {-1, -1, 5};

		auto a1_begin = a1.begin();
		auto a2_begin = a2.begin();

		std::advance(a1_begin, 2);
		std::advance(a2_begin, 2);

		std::list<int> a;
		a.splice(a.begin(), a2, a2_begin);
		a.splice(a.begin(), a1, a1_begin);

		VERIFY(a == ref);
		VERIFY(!a1.empty());
		VERIFY(!a2.empty());
	}

	// void splice(const_iterator position, this_type& x, const_iterator first, const_iterator last);
	{
		const std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a1 = {-1, -1, 0, 1, 2, 3, 4, -1, -1};
		std::list<int> a2 = {-1, -1, 5, 6, 7, 8, 9, -1, -1};

		auto a1_begin = a1.begin();
		auto a2_begin = a2.begin();
		auto a1_end = a1.end();
		auto a2_end = a2.end();

		std::advance(a1_begin, 2);
		std::advance(a2_begin, 2);
		std::advance(a1_end, -2);
		std::advance(a2_end, -2);

		std::list<int> a;
		a.splice(a.begin(), a2, a2_begin, a2_end);
		a.splice(a.begin(), a1, a1_begin, a1_end);

		const std::list<int> rref = {-1, -1, -1, -1};  // post splice reference list
		VERIFY(a == ref);
		VERIFY(a1 == rref);
		VERIFY(a2 == rref);
	}

	// void splice(const_iterator position, this_type&& x);
	{
		const std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a1 = {0, 1, 2, 3, 4};
		std::list<int> a2 = {5, 6, 7, 8, 9};

		std::list<int> a;
		a.splice(a.begin(), std::move(a2));
		a.splice(a.begin(), std::move(a1));

		VERIFY(a == ref);
		VERIFY(a1.empty());
		VERIFY(a2.empty());
	}

	// void splice(const_iterator position, this_type&& x, const_iterator i);
	{
		const std::list<int> ref = {0, 5};
		std::list<int> a1 = {-1, -1, 0};
		std::list<int> a2 = {-1, -1, 5};

		auto a1_begin = a1.begin();
		auto a2_begin = a2.begin();

		std::advance(a1_begin, 2);
		std::advance(a2_begin, 2);

		std::list<int> a;
		a.splice(a.begin(), std::move(a2), a2_begin);
		a.splice(a.begin(), std::move(a1), a1_begin);

		VERIFY(a == ref);
		VERIFY(!a1.empty());
		VERIFY(!a2.empty());
	}

	// void splice(const_iterator position, this_type&& x, const_iterator first, const_iterator last);
	{
		const std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a1 = {-1, -1, 0, 1, 2, 3, 4, -1, -1};
		std::list<int> a2 = {-1, -1, 5, 6, 7, 8, 9, -1, -1};

		auto a1_begin = a1.begin();
		auto a2_begin = a2.begin();
		auto a1_end = a1.end();
		auto a2_end = a2.end();

		std::advance(a1_begin, 2);
		std::advance(a2_begin, 2);
		std::advance(a1_end, -2);
		std::advance(a2_end, -2);

		std::list<int> a;
		a.splice(a.begin(), std::move(a2), a2_begin, a2_end);
		a.splice(a.begin(), std::move(a1), a1_begin, a1_end);

		const std::list<int> rref = {-1, -1, -1, -1};  // post splice reference list
		VERIFY(a == ref);
		VERIFY(a1 == rref);
		VERIFY(a2 == rref);
	}


	// void merge(this_type& x);
	// void merge(this_type&& x);
	// void merge(this_type& x, Compare compare);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a1 = {0, 1, 2, 3, 4};
		std::list<int> a2 = {5, 6, 7, 8, 9};
		a1.merge(a2);
		VERIFY(a1 == ref);
	}

	// void merge(this_type&& x, Compare compare);
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a1 = {0, 1, 2, 3, 4};
		std::list<int> a2 = {5, 6, 7, 8, 9};
		a1.merge(a2, [](int lhs, int rhs) { return lhs < rhs; });
		VERIFY(a1 == ref);
	}

	// void unique();
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3,
		                      4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9};
		a.unique();
		VERIFY(a == ref);
	}

	// void unique(BinaryPredicate);
	{
		static bool bBreakComparison;
		struct A
		{
			int mValue;
			bool operator==(const A& other) const { return bBreakComparison ? false : mValue == other.mValue; }
		};

		std::list<A> ref = {{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};
		std::list<A> a = {{0}, {0}, {0}, {0}, {0}, {0}, {1}, {2}, {2}, {2}, {2}, {3}, {4}, {5},
		                    {5}, {5}, {5}, {5}, {6}, {7}, {7}, {7}, {7}, {8}, {9}, {9}, {9}};

		bBreakComparison = true;
		a.unique(); // noop because broken comparison operator
		VERIFY(a != ref);  

		a.unique([](const A& lhs, const A& rhs) { return lhs.mValue == rhs.mValue; });

		bBreakComparison = false;
		VERIFY(a == ref);
	}

	// void sort();
	{
		std::list<int> ref = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> a =   {9, 4, 5, 3, 1, 0, 6, 2, 7, 8};

		a.sort();
		VERIFY(a == ref);
	}

	// void sort(Compare compare);
	{
		struct A
		{
			int mValue;
			bool operator==(const A& other) const { return mValue == other.mValue; }
		};

		std::list<A> ref = {{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};
		std::list<A> a = {{1}, {0}, {2}, {9}, {4}, {5}, {6}, {7}, {3}, {8}};

		a.sort([](const A& lhs, const A& rhs) { return lhs.mValue < rhs.mValue; });
		VERIFY(a == ref);
	}

	{ // Test empty base-class optimization
		struct UnemptyDummyAllocator : std::dummy_allocator
		{
			int foo;
		};

		typedef std::list<int, std::dummy_allocator> list1;
		typedef std::list<int, UnemptyDummyAllocator> list2;

		EATEST_VERIFY(sizeof(list1) < sizeof(list2));
	}

	{ // Test erase / erase_if
		{
			std::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};

			std::erase(l, 3);
			std::erase(l, 5);
			std::erase(l, 7);

			VERIFY((l == std::list<int>{1, 2, 4, 6, 8, 9}));
		}

		{
			std::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
			std::erase_if(l, [](auto i) { return i % 2 == 0; });
			VERIFY((l == std::list<int>{1, 3, 5, 7, 9}));
		}
	}

	return nErrorCount;
}


