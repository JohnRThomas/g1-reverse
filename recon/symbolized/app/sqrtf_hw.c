#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000869c6 @ 0x000869c6
 * public-name: sqrtf_hw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sqrtf_hw                                 <= FUN_000869c6 @ 0x000869c6
 */
/* Full reconstruction FUN_000869c6 @ 0x869c6 (exact 6-byte extent). */
/* The shipped body is exactly six bytes at 0x869c6:
 *     eeb1 0ac0    vsqrt.f32 s0, s0
 *     4770         bx lr
 * `__builtin_sqrtf` cannot express that here: with GCC's default
 * -fmath-errno the built-in is lowered to a CALL to `sqrtf`, and our `sqrtf`
 * (0x75dc8) calls `sqrtf_hw` -- so the emitted pair was an infinite mutual
 * recursion.  MEASURED in iteration 15 (build g1-i15a, 2.0 s run): each cycle
 * pushed 16 bytes at pc 0x47b68/0x47b6c (`push {r3,lr}` + `vpush {d8}`,
 * lr = 0x47b77) until SP walked below 0x20000000, after which the exception
 * return unstacked PC = 0 -> z_arm_usage_fault -> z_fatal_error ->
 * sys_arch_reboot.  The inline VSQRT below is the original instruction and
 * removes the call entirely.  `__asm__` (not bare `asm`) keeps this valid
 * under the application build's -std=c99. */
float sqrtf_hw(float value)
{
    float result;

    __asm__("vsqrt.f32 %0, %1" : "=t"(result) : "t"(value));
    return result;
}
