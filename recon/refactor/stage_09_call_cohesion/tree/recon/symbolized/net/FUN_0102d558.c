#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102d558 @ 0x0102d558
 * public-name: FUN_0102d558
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102d558 @ 0x102d558  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01039e52(void);

/* DEFECT FIX (iteration 6) — the indirect callee takes `instance` in r0.
 * The ORIGINAL tail-calls with r0 untouched since entry:
 *   0102d57a: ldr r3,[r0,#8]   ; backend = instance->api
 *   0102d598: ldr r3,[r3,#0]   ; backend->open_instance
 *   0102d59c: add sp,#28 / ldr.w lr,[sp],#4
 *   0102d5a2: bx  r3           ; <-- r0 STILL = instance
 * The `(*fnptr_t)(void)` form let GCC leave the FUNCTION POINTER in r0, so
 * the static-vrings backend open() ran with instance = itself (0x01030ee5),
 * read conf = 0x05468123 and optimal_num_desc() spun on available = -4
 * (Renode hook @0x1030eee: instance=0x01030ee5 cfg=0x05468123 lr=0x0102ea7f).
 * Same family as iteration 5 3(b); tools/parity models callees as
 * order-keyed oracles that ignore arguments, so it cannot see this. */
typedef int32_t (*fnptr_t)(int32_t instance);

int32_t FUN_0102d558(int32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    int32_t r3;

    if (param_1 == 0) {
        FUN_01039e52();
        return (int32_t)0xffffffea;
    }
    if (*(volatile int32_t **)(param_1 + 8) == 0) {
        FUN_01039e52();
        return (int32_t)0xfffffffb;
    }
    r3 = **(volatile int32_t **)(param_1 + 8);
    if (r3 != 0) {
        fnptr_t f = (fnptr_t)r3;
        return f(param_1);
    }
    return 0;
}
