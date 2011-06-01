#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "exec-all.h"
#include "gdbstub.h"
#include "def-helper.h"
#include "helper-android.h"
#include "qemu-common.h"

#ifdef CONFIG_TRACE
#include "android-trace.h"

void  HELPER(traceTicks)(uint32_t  ticks)
{
    sim_time += ticks;
}

void  HELPER(traceInsn)(void)
{
    trace_insn_helper();
}

#if HOST_LONG_BITS == 32
void HELPER(traceBB32)(uint64_t  bb_num, uint32_t  tb)
{
    trace_bb_helper(bb_num, (void*)tb);
}
#endif

#if HOST_LONG_BITS == 64
void HELPER(traceBB64)(uint64_t  bb_num, uint64_t  tb)
{
    trace_bb_helper(bb_num, (void*)tb);
}
#endif

#endif /* CONFIG_TRACE */

#ifdef CONFIG_MEMCHECK
#include "memcheck/memcheck_api.h"

void HELPER(on_call)(target_ulong pc, target_ulong ret) {
    memcheck_on_call(pc, ret);
}

void HELPER(on_ret)(target_ulong ret) {
    memcheck_on_ret(ret);
}
#endif  // CONFIG_MEMCHECK
