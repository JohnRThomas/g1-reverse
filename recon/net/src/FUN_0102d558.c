/* net-core FUN_0102d558 @ 0x102d558  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01039e52(void);

/* DEFECT FIX (iteration 6) — the indirect callee takes `instance` in r0.
 * The ORIGINAL performs a TAIL CALL with r0 untouched since entry:
 *   0102d57a: ldr r3,[r0,#8]      ; backend = instance->api
 *   0102d598: ldr r3,[r3,#0]      ; backend->open_instance
 *   0102d59a: cbz r3, 0102d5a4
 *   0102d59c: add sp,#28 / ldr.w lr,[sp],#4
 *   0102d5a2: bx  r3              ; <-- r0 STILL = instance
 * The previous `(*fnptr_t)(void)` form let GCC leave r0 holding whatever it
 * liked; in the cohesive build it left the FUNCTION POINTER there, so the
 * static-vrings backend's open() ran with instance = 0x01030ee5 (itself),
 * read conf = *(u32*)(0x01030ee5+4) = 0x05468123, and optimal_num_desc()
 * spun on available = 0-4 = 0xFFFFFFFC (measured with a Renode hook at
 * 0x1030eee: "NET_OPEN_A instance=0x01030ee5 cfg=0x05468123 lr=0x0102ea7f").
 * Same family as iteration 5 §3(b) (arguments dropped at an indirect call);
 * tools/parity cannot see it because callees are modelled as order-keyed
 * oracles that ignore their arguments. */
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

