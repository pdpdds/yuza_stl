/////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////


#include <EASTL/atomic.h>


namespace std
{

namespace internal
{


static void EastlCompilerBarrierDataDependencyFunc(void*)
{
}

volatile CompilerBarrierDataDependencyFuncPtr gCompilerBarrierDataDependencyFunc = &EastlCompilerBarrierDataDependencyFunc;


} // namespace internal

} // namespace std
