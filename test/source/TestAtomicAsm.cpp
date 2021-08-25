/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#include "EASTLTest.h"

#include <EASTL/atomic.h>

#include <cstddef>


struct UserType128
{
	uint32_t a,b,c,d;

	friend bool operator==(const UserType128& a, const UserType128& b)
	{
		return (a.a == b.a) && (a.b == b.b) && (a.c == b.c) && (a.d == b.d);
	}
};


/**
 * There is no nice way to verify the emitted asm for each of the given operations.
 * This test file is meant to put each operation into its own function so its easy
 * to verify in a disassembler for manual inspection.
 */

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32StoreRelaxed()
{
	std::atomic<uint32_t> atomic;

	atomic.store(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU32StoreRelease()
{
	std::atomic<uint32_t> atomic;

	atomic.store(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU32StoreSeqCst()
{
	std::atomic<uint32_t> atomic;

	atomic.store(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU32Store()
{
	std::atomic<uint32_t> atomic;

	atomic.store(1);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU32StoreOrders()
{
	TestAtomicU32StoreRelaxed();

	TestAtomicU32StoreRelease();

	TestAtomicU32StoreSeqCst();

	TestAtomicU32Store();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64StoreRelaxed()
{
	std::atomic<uint64_t> atomic;

	atomic.store(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU64StoreRelease()
{
	std::atomic<uint64_t> atomic;

	atomic.store(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU64StoreSeqCst()
{
	std::atomic<uint64_t> atomic;

	atomic.store(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU64Store()
{
	std::atomic<uint64_t> atomic;

	atomic.store(1);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomicU64StoreOrders()
{
	TestAtomicU64StoreRelaxed();

	TestAtomicU64StoreRelease();

	TestAtomicU64StoreSeqCst();

	TestAtomicU64Store();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128StoreRelaxed()
{
	std::atomic<UserType128> atomic;

	atomic.store(UserType128{1, 1, 1, 1}, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomic128StoreRelease()
{
	std::atomic<UserType128> atomic;

	atomic.store(UserType128{1, 1, 1, 1}, std::memory_order_release);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomic128StoreSeqCst()
{
	std::atomic<UserType128> atomic;

	atomic.store(UserType128{1, 1, 1, 1}, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomic128Store()
{
	std::atomic<UserType128> atomic;

	atomic.store(UserType128{1, 1, 1, 1});

	std::compiler_barrier_data_dependency(atomic);
}

EA_NO_INLINE static void TestAtomic128StoreOrders()
{
	TestAtomic128StoreRelaxed();

	TestAtomic128StoreRelease();

	TestAtomic128StoreSeqCst();

	TestAtomic128Store();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32LoadRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t load = atomic.load(std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU32LoadAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t load = atomic.load(std::memory_order_acquire);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU32LoadSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t load = atomic.load(std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU32Load()
{
	std::atomic<uint32_t> atomic;

	uint32_t load = atomic.load();

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU32LoadOrders()
{
	TestAtomicU32LoadRelaxed();

	TestAtomicU32LoadAcquire();

	TestAtomicU32LoadSeqCst();

	TestAtomicU32Load();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64LoadRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t load = atomic.load(std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU64LoadAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t load = atomic.load(std::memory_order_acquire);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU64LoadSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t load = atomic.load(std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU64Load()
{
	std::atomic<uint64_t> atomic;

	uint64_t load = atomic.load();

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomicU64LoadOrders()
{
	TestAtomicU64LoadRelaxed();

	TestAtomicU64LoadAcquire();

	TestAtomicU64LoadSeqCst();

	TestAtomicU64Load();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128LoadRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 load = atomic.load(std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomic128LoadAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 load = atomic.load(std::memory_order_acquire);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomic128LoadSeqCst()
{
	std::atomic<UserType128> atomic;

	UserType128 load = atomic.load(std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomic128Load()
{
	std::atomic<UserType128> atomic;

	UserType128 load = atomic.load();

	std::compiler_barrier_data_dependency(load);
}

EA_NO_INLINE static void TestAtomic128LoadOrders()
{
	TestAtomic128LoadRelaxed();

	TestAtomic128LoadAcquire();

	TestAtomic128LoadSeqCst();

	TestAtomic128Load();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32ExchangeRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t exchange = atomic.exchange(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU32ExchangeAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t exchange = atomic.exchange(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU32ExchangeRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t exchange = atomic.exchange(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU32ExchangeAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t exchange = atomic.exchange(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU32ExchangeSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t exchange = atomic.exchange(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU32Exchange()
{
	std::atomic<uint32_t> atomic;

	uint32_t exchange = atomic.exchange(1);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU32ExchangeOrders()
{
	TestAtomicU32ExchangeRelaxed();

	TestAtomicU32ExchangeAcquire();

	TestAtomicU32ExchangeRelease();

	TestAtomicU32ExchangeAcqRel();

	TestAtomicU32ExchangeSeqCst();

	TestAtomicU32Exchange();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64ExchangeRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t exchange = atomic.exchange(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU64ExchangeAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t exchange = atomic.exchange(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU64ExchangeRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t exchange = atomic.exchange(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU64ExchangeAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t exchange = atomic.exchange(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU64ExchangeSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t exchange = atomic.exchange(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU64Exchange()
{
	std::atomic<uint64_t> atomic;

	uint64_t exchange = atomic.exchange(1);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomicU64ExchangeOrders()
{
	TestAtomicU64ExchangeRelaxed();

	TestAtomicU64ExchangeAcquire();

	TestAtomicU64ExchangeRelease();

	TestAtomicU64ExchangeAcqRel();

	TestAtomicU64ExchangeSeqCst();

	TestAtomicU64Exchange();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128ExchangeRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 exchange = atomic.exchange(UserType128{1, 1, 1, 1}, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomic128ExchangeAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 exchange = atomic.exchange(UserType128{1, 1, 1, 1}, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomic128ExchangeRelease()
{
	std::atomic<UserType128> atomic;

	UserType128 exchange = atomic.exchange(UserType128{1, 1, 1, 1}, std::memory_order_release);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomic128ExchangeAcqRel()
{
	std::atomic<UserType128> atomic;

	UserType128 exchange = atomic.exchange(UserType128{1, 1, 1, 1}, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomic128ExchangeSeqCst()
{
	std::atomic<UserType128> atomic;

	UserType128 exchange = atomic.exchange(UserType128{1, 1, 1, 1}, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomic128Exchange()
{
	std::atomic<UserType128> atomic;

	UserType128 exchange = atomic.exchange(UserType128{1, 1, 1, 1});

	std::compiler_barrier_data_dependency(exchange);
}

EA_NO_INLINE static void TestAtomic128ExchangeOrders()
{
	TestAtomic128ExchangeRelaxed();

	TestAtomic128ExchangeAcquire();

	TestAtomic128ExchangeRelease();

	TestAtomic128ExchangeAcqRel();

	TestAtomic128ExchangeSeqCst();

	TestAtomic128Exchange();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorT()
{
	std::atomic<uint32_t> atomic;

	uint32_t load = atomic;

	std::compiler_barrier_data_dependency(load);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorT()
{
	std::atomic<uint64_t> atomic;

	uint64_t load = atomic;

	std::compiler_barrier_data_dependency(load);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128OperatorT()
{
	std::atomic<UserType128> atomic;

	UserType128 load = atomic;

	std::compiler_barrier_data_dependency(load);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorEqual()
{
	std::atomic<uint32_t> atomic;

	atomic = 1;

	std::compiler_barrier_data_dependency(atomic);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorEqual()
{
	std::atomic<uint64_t> atomic;

	atomic = 1;

	std::compiler_barrier_data_dependency(atomic);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128OperatorEqual()
{
	std::atomic<UserType128> atomic;

	atomic = UserType128{1, 1, 1, 1};

	std::compiler_barrier_data_dependency(atomic);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongRelaxedRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_relaxed, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongAcquireRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acquire, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongAcquireAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acquire, std::memory_order_acquire);


	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongReleaseRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_release, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongAcqRelRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acq_rel, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongAcqRelAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acq_rel, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongSeqCstRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongSeqCstAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongSeqCstSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_release);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrong()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeStrongOrders()
{
	TestAtomicU32CompareExchangeStrongRelaxedRelaxed();

	TestAtomicU32CompareExchangeStrongAcquireRelaxed();

	TestAtomicU32CompareExchangeStrongAcquireAcquire();

	TestAtomicU32CompareExchangeStrongReleaseRelaxed();

	TestAtomicU32CompareExchangeStrongAcqRelRelaxed();

	TestAtomicU32CompareExchangeStrongAcqRelAcquire();

	TestAtomicU32CompareExchangeStrongSeqCstRelaxed();

	TestAtomicU32CompareExchangeStrongSeqCstAcquire();

	TestAtomicU32CompareExchangeStrongSeqCstSeqCst();

	TestAtomicU32CompareExchangeStrongRelaxed();

	TestAtomicU32CompareExchangeStrongAcquire();

	TestAtomicU32CompareExchangeStrongRelease();

	TestAtomicU32CompareExchangeStrongAcqRel();

	TestAtomicU32CompareExchangeStrongSeqCst();

	TestAtomicU32CompareExchangeStrong();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongRelaxedRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_relaxed, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongAcquireRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acquire, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongAcquireAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acquire, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongReleaseRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_release, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongAcqRelRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acq_rel, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongAcqRelAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acq_rel, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongSeqCstRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongSeqCstAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongSeqCstSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_release);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrong()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_strong(expected, 1);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeStrongOrders()
{
	TestAtomicU64CompareExchangeStrongRelaxedRelaxed();

	TestAtomicU64CompareExchangeStrongAcquireRelaxed();

	TestAtomicU64CompareExchangeStrongAcquireAcquire();

	TestAtomicU64CompareExchangeStrongReleaseRelaxed();

	TestAtomicU64CompareExchangeStrongAcqRelRelaxed();

	TestAtomicU64CompareExchangeStrongAcqRelAcquire();

	TestAtomicU64CompareExchangeStrongSeqCstRelaxed();

	TestAtomicU64CompareExchangeStrongSeqCstAcquire();

	TestAtomicU64CompareExchangeStrongSeqCstSeqCst();

	TestAtomicU64CompareExchangeStrongRelaxed();

	TestAtomicU64CompareExchangeStrongAcquire();

	TestAtomicU64CompareExchangeStrongRelease();

	TestAtomicU64CompareExchangeStrongAcqRel();

	TestAtomicU64CompareExchangeStrongSeqCst();

	TestAtomicU64CompareExchangeStrong();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongRelaxedRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_relaxed, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongAcquireRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_acquire, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongAcquireAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_acquire, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongReleaseRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_release, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongAcqRelRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_acq_rel, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongAcqRelAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_acq_rel, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongSeqCstRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongSeqCstAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongSeqCstSeqCst()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongRelease()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_release);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongAcqRel()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongSeqCst()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrong()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_strong(expected, UserType128{1, 1, 1, 1});

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeStrongOrders()
{
	TestAtomic128CompareExchangeStrongRelaxedRelaxed();

	TestAtomic128CompareExchangeStrongAcquireRelaxed();

	TestAtomic128CompareExchangeStrongAcquireAcquire();

	TestAtomic128CompareExchangeStrongReleaseRelaxed();

	TestAtomic128CompareExchangeStrongAcqRelRelaxed();

	TestAtomic128CompareExchangeStrongAcqRelAcquire();

	TestAtomic128CompareExchangeStrongSeqCstRelaxed();

	TestAtomic128CompareExchangeStrongSeqCstAcquire();

	TestAtomic128CompareExchangeStrongSeqCstSeqCst();

	TestAtomic128CompareExchangeStrongRelaxed();

	TestAtomic128CompareExchangeStrongAcquire();

	TestAtomic128CompareExchangeStrongRelease();

	TestAtomic128CompareExchangeStrongAcqRel();

	TestAtomic128CompareExchangeStrongSeqCst();

	TestAtomic128CompareExchangeStrong();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakRelaxedRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_relaxed, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakAcquireRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acquire, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakAcquireAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acquire, std::memory_order_acquire);


	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakReleaseRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_release, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakAcqRelRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acq_rel, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakAcqRelAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acq_rel, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakSeqCstRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakSeqCstAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakSeqCstSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_release);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeak()
{
	std::atomic<uint32_t> atomic;

	uint32_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU32CompareExchangeWeakOrders()
{
	TestAtomicU32CompareExchangeWeakRelaxedRelaxed();

	TestAtomicU32CompareExchangeWeakAcquireRelaxed();

	TestAtomicU32CompareExchangeWeakAcquireAcquire();

	TestAtomicU32CompareExchangeWeakReleaseRelaxed();

	TestAtomicU32CompareExchangeWeakAcqRelRelaxed();

	TestAtomicU32CompareExchangeWeakAcqRelAcquire();

	TestAtomicU32CompareExchangeWeakSeqCstRelaxed();

	TestAtomicU32CompareExchangeWeakSeqCstAcquire();

	TestAtomicU32CompareExchangeWeakSeqCstSeqCst();

	TestAtomicU32CompareExchangeWeakRelaxed();

	TestAtomicU32CompareExchangeWeakAcquire();

	TestAtomicU32CompareExchangeWeakRelease();

	TestAtomicU32CompareExchangeWeakAcqRel();

	TestAtomicU32CompareExchangeWeakSeqCst();

	TestAtomicU32CompareExchangeWeak();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakRelaxedRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_relaxed, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakAcquireRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acquire, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakAcquireAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acquire, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakReleaseRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_release, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakAcqRelRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acq_rel, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakAcqRelAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acq_rel, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakSeqCstRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakSeqCstAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakSeqCstSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_release);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeak()
{
	std::atomic<uint64_t> atomic;

	uint64_t expected = 0;
	bool ret = atomic.compare_exchange_weak(expected, 1);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomicU64CompareExchangeWeakOrders()
{
	TestAtomicU64CompareExchangeWeakRelaxedRelaxed();

	TestAtomicU64CompareExchangeWeakAcquireRelaxed();

	TestAtomicU64CompareExchangeWeakAcquireAcquire();

	TestAtomicU64CompareExchangeWeakReleaseRelaxed();

	TestAtomicU64CompareExchangeWeakAcqRelRelaxed();

	TestAtomicU64CompareExchangeWeakAcqRelAcquire();

	TestAtomicU64CompareExchangeWeakSeqCstRelaxed();

	TestAtomicU64CompareExchangeWeakSeqCstAcquire();

	TestAtomicU64CompareExchangeWeakSeqCstSeqCst();

	TestAtomicU64CompareExchangeWeakRelaxed();

	TestAtomicU64CompareExchangeWeakAcquire();

	TestAtomicU64CompareExchangeWeakRelease();

	TestAtomicU64CompareExchangeWeakAcqRel();

	TestAtomicU64CompareExchangeWeakSeqCst();

	TestAtomicU64CompareExchangeWeak();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakRelaxedRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_relaxed, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakAcquireRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_acquire, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakAcquireAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_acquire, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakReleaseRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_release, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakAcqRelRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_acq_rel, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakAcqRelAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_acq_rel, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakSeqCstRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakSeqCstAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakSeqCstSeqCst()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakRelaxed()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakAcquire()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakRelease()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_release);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakAcqRel()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakSeqCst()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1}, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeak()
{
	std::atomic<UserType128> atomic;

	UserType128 expected = UserType128{0, 0, 0, 0};
	bool ret = atomic.compare_exchange_weak(expected, UserType128{1, 1, 1, 1});

	std::compiler_barrier_data_dependency(ret);
}

EA_NO_INLINE static void TestAtomic128CompareExchangeWeakOrders()
{
	TestAtomic128CompareExchangeWeakRelaxedRelaxed();

	TestAtomic128CompareExchangeWeakAcquireRelaxed();

	TestAtomic128CompareExchangeWeakAcquireAcquire();

	TestAtomic128CompareExchangeWeakReleaseRelaxed();

	TestAtomic128CompareExchangeWeakAcqRelRelaxed();

	TestAtomic128CompareExchangeWeakAcqRelAcquire();

	TestAtomic128CompareExchangeWeakSeqCstRelaxed();

	TestAtomic128CompareExchangeWeakSeqCstAcquire();

	TestAtomic128CompareExchangeWeakSeqCstSeqCst();

	TestAtomic128CompareExchangeWeakRelaxed();

	TestAtomic128CompareExchangeWeakAcquire();

	TestAtomic128CompareExchangeWeakRelease();

	TestAtomic128CompareExchangeWeakAcqRel();

	TestAtomic128CompareExchangeWeakSeqCst();

	TestAtomic128CompareExchangeWeak();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32FetchAddRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_add(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAddAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_add(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAddRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_add(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAddAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_add(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAddSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_add(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAdd()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_add(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAddOrders()
{
	TestAtomicU32FetchAddRelaxed();

	TestAtomicU32FetchAddAcquire();

	TestAtomicU32FetchAddRelease();

	TestAtomicU32FetchAddAcqRel();

	TestAtomicU32FetchAddSeqCst();

	TestAtomicU32FetchAdd();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64FetchAddRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAddAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAddRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAddAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAddSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAdd()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAddOrders()
{
	TestAtomicU64FetchAddRelaxed();

	TestAtomicU64FetchAddAcquire();

	TestAtomicU64FetchAddRelease();

	TestAtomicU64FetchAddAcqRel();

	TestAtomicU64FetchAddSeqCst();

	TestAtomicU64FetchAdd();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128FetchAddRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_add(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAddAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_add(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAddRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_add(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAddAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_add(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAddSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_add(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAdd()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_add(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAddOrders()
{
	TestAtomic128FetchAddRelaxed();

	TestAtomic128FetchAddAcquire();

	TestAtomic128FetchAddRelease();

	TestAtomic128FetchAddAcqRel();

	TestAtomic128FetchAddSeqCst();

	TestAtomic128FetchAdd();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32AddFetchRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.add_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AddFetchAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.add_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AddFetchRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.add_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AddFetchAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.add_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AddFetchSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.add_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AddFetch()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.add_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AddFetchOrders()
{
	TestAtomicU32AddFetchRelaxed();

	TestAtomicU32AddFetchAcquire();

	TestAtomicU32AddFetchRelease();

	TestAtomicU32AddFetchAcqRel();

	TestAtomicU32AddFetchSeqCst();

	TestAtomicU32AddFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64AddFetchRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.add_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AddFetchAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.add_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AddFetchRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.add_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AddFetchAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.add_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AddFetchSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.add_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AddFetch()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.add_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AddFetchOrders()
{
	TestAtomicU64AddFetchRelaxed();

	TestAtomicU64AddFetchAcquire();

	TestAtomicU64AddFetchRelease();

	TestAtomicU64AddFetchAcqRel();

	TestAtomicU64AddFetchSeqCst();

	TestAtomicU64AddFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128AddFetchRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.add_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AddFetchAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.add_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AddFetchRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.add_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AddFetchAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.add_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AddFetchSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.add_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AddFetch()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.add_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AddFetchOrders()
{
	TestAtomic128AddFetchRelaxed();

	TestAtomic128AddFetchAcquire();

	TestAtomic128AddFetchRelease();

	TestAtomic128AddFetchAcqRel();

	TestAtomic128AddFetchSeqCst();

	TestAtomic128AddFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32FetchSubRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_sub(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchSubAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_sub(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchSubRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_sub(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchSubAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_sub(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchSubSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_sub(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchSub()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_sub(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchSubOrders()
{
	TestAtomicU32FetchSubRelaxed();

	TestAtomicU32FetchSubAcquire();

	TestAtomicU32FetchSubRelease();

	TestAtomicU32FetchSubAcqRel();

	TestAtomicU32FetchSubSeqCst();

	TestAtomicU32FetchSub();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64FetchSubRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_sub(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchSubAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_sub(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchSubRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_sub(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchSubAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_sub(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchSubSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_sub(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchSub()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_sub(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchSubOrders()
{
	TestAtomicU64FetchSubRelaxed();

	TestAtomicU64FetchSubAcquire();

	TestAtomicU64FetchSubRelease();

	TestAtomicU64FetchSubAcqRel();

	TestAtomicU64FetchSubSeqCst();

	TestAtomicU64FetchSub();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128FetchSubRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_sub(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchSubAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_sub(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchSubRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_sub(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchSubAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_sub(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchSubSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_sub(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchSub()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_sub(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchSubOrders()
{
	TestAtomic128FetchSubRelaxed();

	TestAtomic128FetchSubAcquire();

	TestAtomic128FetchSubRelease();

	TestAtomic128FetchSubAcqRel();

	TestAtomic128FetchSubSeqCst();

	TestAtomic128FetchSub();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32SubFetchRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.sub_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32SubFetchAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.sub_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32SubFetchRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.sub_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32SubFetchAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.sub_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32SubFetchSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.sub_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32SubFetch()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.sub_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32SubFetchOrders()
{
	TestAtomicU32SubFetchRelaxed();

	TestAtomicU32SubFetchAcquire();

	TestAtomicU32SubFetchRelease();

	TestAtomicU32SubFetchAcqRel();

	TestAtomicU32SubFetchSeqCst();

	TestAtomicU32SubFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64SubFetchRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.sub_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64SubFetchAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.sub_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64SubFetchRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.sub_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64SubFetchAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.sub_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64SubFetchSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.sub_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64SubFetch()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.sub_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64SubFetchOrders()
{
	TestAtomicU64SubFetchRelaxed();

	TestAtomicU64SubFetchAcquire();

	TestAtomicU64SubFetchRelease();

	TestAtomicU64SubFetchAcqRel();

	TestAtomicU64SubFetchSeqCst();

	TestAtomicU64SubFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128SubFetchRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.sub_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128SubFetchAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.sub_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128SubFetchRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.sub_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128SubFetchAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.sub_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128SubFetchSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.sub_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128SubFetch()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.sub_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128SubFetchOrders()
{
	TestAtomic128SubFetchRelaxed();

	TestAtomic128SubFetchAcquire();

	TestAtomic128SubFetchRelease();

	TestAtomic128SubFetchAcqRel();

	TestAtomic128SubFetchSeqCst();

	TestAtomic128SubFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32FetchAndRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_and(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAndAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_and(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAndRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_and(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAndAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_and(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAndSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_and(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAnd()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_and(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchAndOrders()
{
	TestAtomicU32FetchAndRelaxed();

	TestAtomicU32FetchAndAcquire();

	TestAtomicU32FetchAndRelease();

	TestAtomicU32FetchAndAcqRel();

	TestAtomicU32FetchAndSeqCst();

	TestAtomicU32FetchAnd();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64FetchAndRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_and(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAndAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_and(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAndRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_and(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAndAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_and(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAndSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_and(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAnd()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_and(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchAndOrders()
{
	TestAtomicU64FetchAndRelaxed();

	TestAtomicU64FetchAndAcquire();

	TestAtomicU64FetchAndRelease();

	TestAtomicU64FetchAndAcqRel();

	TestAtomicU64FetchAndSeqCst();

	TestAtomicU64FetchAnd();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128FetchAndRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_and(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAndAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_and(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAndRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_and(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAndAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_and(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAndSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_and(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAnd()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_and(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchAndOrders()
{
	TestAtomic128FetchAndRelaxed();

	TestAtomic128FetchAndAcquire();

	TestAtomic128FetchAndRelease();

	TestAtomic128FetchAndAcqRel();

	TestAtomic128FetchAndSeqCst();

	TestAtomic128FetchAnd();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32AndFetchRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.and_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AndFetchAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.and_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AndFetchRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.and_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AndFetchAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.and_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AndFetchSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.and_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AndFetch()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.and_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32AndFetchOrders()
{
	TestAtomicU32AndFetchRelaxed();

	TestAtomicU32AndFetchAcquire();

	TestAtomicU32AndFetchRelease();

	TestAtomicU32AndFetchAcqRel();

	TestAtomicU32AndFetchSeqCst();

	TestAtomicU32AndFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64AndFetchRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.and_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AndFetchAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.and_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AndFetchRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.and_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AndFetchAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.and_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AndFetchSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.and_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AndFetch()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.and_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64AndFetchOrders()
{
	TestAtomicU64AndFetchRelaxed();

	TestAtomicU64AndFetchAcquire();

	TestAtomicU64AndFetchRelease();

	TestAtomicU64AndFetchAcqRel();

	TestAtomicU64AndFetchSeqCst();

	TestAtomicU64AndFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128AndFetchRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.and_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AndFetchAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.and_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AndFetchRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.and_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AndFetchAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.and_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AndFetchSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.and_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AndFetch()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.and_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128AndFetchOrders()
{
	TestAtomic128AndFetchRelaxed();

	TestAtomic128AndFetchAcquire();

	TestAtomic128AndFetchRelease();

	TestAtomic128AndFetchAcqRel();

	TestAtomic128AndFetchSeqCst();

	TestAtomic128AndFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OrFetchRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.or_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32OrFetchAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.or_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32OrFetchRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.or_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32OrFetchAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.or_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32OrFetchSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.or_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32OrFetch()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.or_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32OrFetchOrders()
{
	TestAtomicU32OrFetchRelaxed();

	TestAtomicU32OrFetchAcquire();

	TestAtomicU32OrFetchRelease();

	TestAtomicU32OrFetchAcqRel();

	TestAtomicU32OrFetchSeqCst();

	TestAtomicU32OrFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OrFetchRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.or_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64OrFetchAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.or_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64OrFetchRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.or_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64OrFetchAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.or_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64OrFetchSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.or_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64OrFetch()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.or_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64OrFetchOrders()
{
	TestAtomicU64OrFetchRelaxed();

	TestAtomicU64OrFetchAcquire();

	TestAtomicU64OrFetchRelease();

	TestAtomicU64OrFetchAcqRel();

	TestAtomicU64OrFetchSeqCst();

	TestAtomicU64OrFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OrFetchRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.or_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128OrFetchAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.or_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128OrFetchRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.or_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128OrFetchAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.or_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128OrFetchSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.or_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128OrFetch()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.or_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128OrFetchOrders()
{
	TestAtomic128OrFetchRelaxed();

	TestAtomic128OrFetchAcquire();

	TestAtomic128OrFetchRelease();

	TestAtomic128OrFetchAcqRel();

	TestAtomic128OrFetchSeqCst();

	TestAtomic128OrFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32FetchOrRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_or(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchOrAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_or(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchOrRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_or(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchOrAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_or(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchOrSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_or(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchOr()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_or(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchOrOrders()
{
	TestAtomicU32FetchOrRelaxed();

	TestAtomicU32FetchOrAcquire();

	TestAtomicU32FetchOrRelease();

	TestAtomicU32FetchOrAcqRel();

	TestAtomicU32FetchOrSeqCst();

	TestAtomicU32FetchOr();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64FetchOrRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_or(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchOrAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_or(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchOrRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_or(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchOrAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_or(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchOrSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_or(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchOr()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_or(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchOrOrders()
{
	TestAtomicU64FetchOrRelaxed();

	TestAtomicU64FetchOrAcquire();

	TestAtomicU64FetchOrRelease();

	TestAtomicU64FetchOrAcqRel();

	TestAtomicU64FetchOrSeqCst();

	TestAtomicU64FetchOr();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128FetchOrRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_or(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchOrAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_or(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchOrRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_or(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchOrAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_or(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchOrSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_or(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchOr()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_or(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchOrOrders()
{
	TestAtomic128FetchOrRelaxed();

	TestAtomic128FetchOrAcquire();

	TestAtomic128FetchOrRelease();

	TestAtomic128FetchOrAcqRel();

	TestAtomic128FetchOrSeqCst();

	TestAtomic128FetchOr();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32FetchXorRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_xor(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchXorAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_xor(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchXorRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_xor(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchXorAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_xor(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchXorSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_xor(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchXor()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.fetch_xor(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32FetchXorOrders()
{
	TestAtomicU32FetchXorRelaxed();

	TestAtomicU32FetchXorAcquire();

	TestAtomicU32FetchXorRelease();

	TestAtomicU32FetchXorAcqRel();

	TestAtomicU32FetchXorSeqCst();

	TestAtomicU32FetchXor();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64FetchXorRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_xor(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchXorAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_xor(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchXorRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_xor(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchXorAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_xor(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchXorSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_add(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchXor()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.fetch_xor(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64FetchXorOrders()
{
	TestAtomicU64FetchXorRelaxed();

	TestAtomicU64FetchXorAcquire();

	TestAtomicU64FetchXorRelease();

	TestAtomicU64FetchXorAcqRel();

	TestAtomicU64FetchXorSeqCst();

	TestAtomicU64FetchXor();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128FetchXorRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_xor(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchXorAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_xor(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchXorRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_xor(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchXorAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_xor(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchXorSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_xor(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchXor()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.fetch_xor(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128FetchXorOrders()
{
	TestAtomic128FetchXorRelaxed();

	TestAtomic128FetchXorAcquire();

	TestAtomic128FetchXorRelease();

	TestAtomic128FetchXorAcqRel();

	TestAtomic128FetchXorSeqCst();

	TestAtomic128FetchXor();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32XorFetchRelaxed()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.xor_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32XorFetchAcquire()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.xor_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32XorFetchRelease()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.xor_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32XorFetchAcqRel()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.xor_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32XorFetchSeqCst()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.xor_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32XorFetch()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic.xor_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU32XorFetchOrders()
{
	TestAtomicU32XorFetchRelaxed();

	TestAtomicU32XorFetchAcquire();

	TestAtomicU32XorFetchRelease();

	TestAtomicU32XorFetchAcqRel();

	TestAtomicU32XorFetchSeqCst();

	TestAtomicU32XorFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64XorFetchRelaxed()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.xor_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64XorFetchAcquire()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.xor_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64XorFetchRelease()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.xor_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64XorFetchAcqRel()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.xor_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64XorFetchSeqCst()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.xor_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64XorFetch()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic.xor_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomicU64XorFetchOrders()
{
	TestAtomicU64XorFetchRelaxed();

	TestAtomicU64XorFetchAcquire();

	TestAtomicU64XorFetchRelease();

	TestAtomicU64XorFetchAcqRel();

	TestAtomicU64XorFetchSeqCst();

	TestAtomicU64XorFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128XorFetchRelaxed()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.xor_fetch(1, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128XorFetchAcquire()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.xor_fetch(1, std::memory_order_acquire);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128XorFetchRelease()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.xor_fetch(1, std::memory_order_release);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128XorFetchAcqRel()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.xor_fetch(1, std::memory_order_acq_rel);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128XorFetchSeqCst()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.xor_fetch(1, std::memory_order_seq_cst);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128XorFetch()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic.xor_fetch(1);

	std::compiler_barrier_data_dependency(val);
}

EA_NO_INLINE static void TestAtomic128XorFetchOrders()
{
	TestAtomic128XorFetchRelaxed();

	TestAtomic128XorFetchAcquire();

	TestAtomic128XorFetchRelease();

	TestAtomic128XorFetchAcqRel();

	TestAtomic128XorFetchSeqCst();

	TestAtomic128XorFetch();
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorPlusPlus()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic++;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorPlusPlus()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic++;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorPlusPlus()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic++;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32PlusPlusOperator()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = ++atomic;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64PlusPlusOperator()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = ++atomic;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128PlusPlusOperator()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = ++atomic;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorMinusMinus()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic--;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorMinusMinus()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic--;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorMinusMinus()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic--;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32MinusMinusOperator()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = --atomic;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64MinusMinusOperator()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = --atomic;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128MinusMinusOperator()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = --atomic;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorPlusAssignment()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic += 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorPlusAssignment()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic += 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorPlusAssignment()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic += 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorMinusAssignment()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic -= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorMinusAssignment()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic -= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorMinusAssignment()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic -= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorAndAssignment()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic &= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorAndAssignment()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic &= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorAndAssignment()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic &= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorOrAssignment()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic |= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorOrAssignment()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic |= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorOrAssignment()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic |= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomicU32OperatorXorAssignment()
{
	std::atomic<uint32_t> atomic;

	uint32_t val = atomic ^= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_64BIT)

EA_NO_INLINE static void TestAtomicU64OperatorXorAssignment()
{
	std::atomic<uint64_t> atomic;

	uint64_t val = atomic ^= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))

EA_NO_INLINE static void TestAtomic128OperatorXorAssignment()
{
	std::atomic<__uint128_t> atomic;

	__uint128_t val = atomic ^= 1;

	std::compiler_barrier_data_dependency(val);
}

#endif

EA_NO_INLINE static void TestAtomicSignalFenceRelaxed()
{
	std::atomic_signal_fence(std::memory_order_relaxed);
}

EA_NO_INLINE static void TestAtomicSignalFenceAcquire()
{
	std::atomic_signal_fence(std::memory_order_acquire);
}

EA_NO_INLINE static void TestAtomicSignalFenceRelease()
{
	std::atomic_signal_fence(std::memory_order_release);
}

EA_NO_INLINE static void TestAtomicSignalFenceAcqRel()
{
	std::atomic_signal_fence(std::memory_order_acq_rel);
}

EA_NO_INLINE static void TestAtomicSignalFenceSeqCst()
{
	std::atomic_signal_fence(std::memory_order_seq_cst);
}

EA_NO_INLINE static void TestAtomicThreadFenceRelaxed()
{
	std::atomic_thread_fence(std::memory_order_relaxed);
}

EA_NO_INLINE static void TestAtomicThreadFenceAcquire()
{
	std::atomic_thread_fence(std::memory_order_acquire);
}

EA_NO_INLINE static void TestAtomicThreadFenceRelease()
{
	std::atomic_thread_fence(std::memory_order_release);
}

EA_NO_INLINE static void TestAtomicThreadFenceAcqRel()
{
	std::atomic_thread_fence(std::memory_order_acq_rel);
}

EA_NO_INLINE static void TestAtomicThreadFenceSeqCst()
{
	std::atomic_thread_fence(std::memory_order_seq_cst);
}

EA_NO_INLINE static void TestAtomicPointerReadDepends()
{
	std::atomic<void*> atomic;

	void* p = atomic.load(std::memory_order_read_depends);

	std::compiler_barrier_data_dependency(p);
}

struct ReadDependsStruct
{
	int a;
	int b;
};

std::atomic<ReadDependsStruct*> gAtomicPtr;

EA_NO_INLINE int TestAtomicReadDependsStruct()
{
	ReadDependsStruct* p = gAtomicPtr.load(std::memory_order_read_depends);

	int a = p->a;
	int b = p->b;

	return a + b;
}

EA_NO_INLINE static void TestCompilerBarrierDataDependency()
{
	{
		UserType128 t{4, 5, 7, 8};

		std::compiler_barrier_data_dependency(t);
	}

	{
		void* p = (void*)0xdeadbeef;

		std::compiler_barrier_data_dependency(p);
	}

	{
		bool b = false;

		std::compiler_barrier_data_dependency(b);
	}
}

struct ReadDependsIntrusive
{
	int a;
	int b;
	struct ReadDependsIntrusive* next;
	int c;
	int d;
};

std::atomic<ReadDependsIntrusive**> gListHead;

EA_NO_INLINE static int TestAtomicReadDependsIntrusive()
{
	ReadDependsIntrusive** intrusivePtr = gListHead.load(std::memory_order_read_depends);
	ReadDependsIntrusive* ptr = ((ReadDependsIntrusive*)(((char*)intrusivePtr) - offsetof(ReadDependsIntrusive, next)));

	int a = ptr->a;
	int b = ptr->b;
	int c = ptr->c;
	int d = ptr->d;

	return a + b + c + d;
}

#if defined(EASTL_ATOMIC_HAS_32BIT)

EA_NO_INLINE static void TestAtomic32LoadStoreSameAddressSeqCst()
{
	std::atomic<uint32_t> atomic{0};

	uint32_t ret1 = atomic.load(std::memory_order_relaxed);

	atomic.store(4, std::memory_order_relaxed);

	uint32_t ret2 = atomic.load(std::memory_order_relaxed);

	uint32_t ret3 = atomic.load(std::memory_order_relaxed);

	atomic.store(5, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret1);
	std::compiler_barrier_data_dependency(ret2);
	std::compiler_barrier_data_dependency(ret3);
}

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

EA_NO_INLINE static void TestAtomic128LoadStoreSameAddressSeqCst()
{
	std::atomic<UserType128> atomic{UserType128{0, 0, 0, 0}};

	UserType128 ret1 = atomic.load(std::memory_order_relaxed);

	atomic.store(UserType128{1, 0, 2, 4}, std::memory_order_relaxed);

	UserType128 ret2 = atomic.load(std::memory_order_relaxed);

	UserType128 ret3 = atomic.load(std::memory_order_relaxed);

	atomic.store(UserType128{1, 1, 2, 4}, std::memory_order_relaxed);

	std::compiler_barrier_data_dependency(ret1);
	std::compiler_barrier_data_dependency(ret2);
	std::compiler_barrier_data_dependency(ret3);
}

#endif

int TestAtomicAsm()
{
	int nErrorCount = 0;

	// Stores
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32StoreOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64StoreOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128StoreOrders();
	#endif
	}

	// Loads
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32LoadOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64LoadOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128LoadOrders();
	#endif
	}

	// exchange
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32ExchangeOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64ExchangeOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128ExchangeOrders();
	#endif
	}

	// operator T
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorT();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorT();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128OperatorT();
	#endif
	}

	// operator=
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorEqual();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorEqual();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128OperatorEqual();
	#endif
	}

	// compare_exchange_weak
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32CompareExchangeWeakOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64CompareExchangeWeakOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128CompareExchangeWeakOrders();
	#endif
	}

	// compare_exchange_strong
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32CompareExchangeStrongOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64CompareExchangeStrongOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT)
		TestAtomic128CompareExchangeStrongOrders();
	#endif
	}

	// fetch_add
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32FetchAddOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64FetchAddOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128FetchAddOrders();
	#endif
	}

	// add_fetch
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32AddFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64AddFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128AddFetchOrders();
	#endif
	}

	// fetch_sub
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32FetchSubOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64FetchSubOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128FetchSubOrders();
	#endif
	}

	// sub_fetch
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32SubFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64SubFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128SubFetchOrders();
	#endif
	}

	// fetch_and
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32FetchAndOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64FetchAndOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128FetchAndOrders();
	#endif
	}

	// and_fetch
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32AndFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64AndFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128AndFetchOrders();
	#endif
	}

	// fetch_or
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32FetchOrOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64FetchOrOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
			TestAtomic128FetchOrOrders();
	#endif
	}

	// or_fetch
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OrFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OrFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OrFetchOrders();
	#endif
	}

	// fetch_xor
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32FetchXorOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64FetchXorOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128FetchXorOrders();
	#endif
	}

	// xor_fetch
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32XorFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64XorFetchOrders();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128XorFetchOrders();
	#endif
	}

	// operator++/++operator
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorPlusPlus();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorPlusPlus();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorPlusPlus();
	#endif

	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32PlusPlusOperator();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64PlusPlusOperator();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128PlusPlusOperator();
	#endif
	}

	// operator--/--operator
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorMinusMinus();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorMinusMinus();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorMinusMinus();
	#endif

	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32MinusMinusOperator();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64MinusMinusOperator();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128MinusMinusOperator();
	#endif
	}

	// operator+=
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorPlusAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorPlusAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorPlusAssignment();
	#endif
	}

	// operator-=
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorMinusAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorMinusAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorMinusAssignment();
	#endif
	}

	// operator&=
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorAndAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorAndAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorAndAssignment();
	#endif
	}

	// operator|=
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorOrAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorOrAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorOrAssignment();
	#endif
	}

	// operator^=
	{
	#if defined(EASTL_ATOMIC_HAS_32BIT)
		TestAtomicU32OperatorXorAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_64BIT)
		TestAtomicU64OperatorXorAssignment();
	#endif

	#if defined(EASTL_ATOMIC_HAS_128BIT) && (defined(EA_COMPILER_GNUC) || defined(EA_COMPILER_CLANG))
		TestAtomic128OperatorXorAssignment();
	#endif
	}

	// atomic_signal_fence
	{
		TestAtomicSignalFenceRelaxed();

		TestAtomicSignalFenceAcquire();

		TestAtomicSignalFenceRelease();

		TestAtomicSignalFenceAcqRel();

		TestAtomicSignalFenceSeqCst();
	}

	// atomic_thread_fence
	{
		TestAtomicThreadFenceRelaxed();

		TestAtomicThreadFenceAcquire();

		TestAtomicThreadFenceRelease();

		TestAtomicThreadFenceAcqRel();

		TestAtomicThreadFenceSeqCst();
	}

	// atomic pointer read depends
	{
		TestAtomicPointerReadDepends();
	}

	// atomic pointer read depends
	{
		ReadDependsStruct rds {3, 2};

		gAtomicPtr.store(&rds, std::memory_order_release);

		int ret = TestAtomicReadDependsStruct();
		std::compiler_barrier_data_dependency(ret);
	}

	{
		ReadDependsIntrusive rdi {3, 2, &rdi, 1, 0};

		gListHead.store(&(rdi.next), std::memory_order_release);

		int ret = TestAtomicReadDependsIntrusive();
		std::compiler_barrier_data_dependency(ret);
	}

	{
		TestCompilerBarrierDataDependency();
	}

#if defined(EASTL_ATOMIC_HAS_32BIT)

	TestAtomic32LoadStoreSameAddressSeqCst();

#endif

#if defined(EASTL_ATOMIC_HAS_128BIT)

	TestAtomic128LoadStoreSameAddressSeqCst();

#endif

	return nErrorCount;
}
