/* Reconstructed FUN_0007c408 @ 0x7c408  (parity: 300/300 trials, PROVEN)
 *
 * P4 iteration 40 -- DROPPED ARGUMENT.  The indirect `value_len` op is invoked
 * by the shipped function with the DESCRIPTOR in r0, not the outer node:
 *     0007c408  mov  r3, r0
 *     0007c40a  cbz  r0, #0x7c41a
 *     0007c40c  ldr  r0, [r0, #0x14]     ; <<< r0 = the descriptor
 *     0007c40e  cbz  r0, #0x7c416
 *     0007c410  ldr  r2, [r0, #4]
 *     0007c412  cbz  r2, #0x7c416
 *     0007c414  bx   r2                  ; tail call, r0 = the descriptor
 *     0007c416  ldr  r0, [r3, #0x10]
 * The previous body wrote `fn()` with NO argument.  Measured in the shipped-in
 * build /private/tmp/g1-i39c-app/zephyr/zephyr.elf, that compiled to
 *     78a1e  ldr r3,[r0,#20] ; 78a22 ldr r3,[r3,#4] ; 78a26 bx r3
 * i.e. r0 still held the OUTER node.  Harmless while every op pointer was an
 * unrelocated original-image address, fatal as soon as FUN_0007c38a /
 * FUN_0007c39c became real code: they read `*r0` expecting the record type
 * byte 7 / 8 and would have seen the option-node header instead, answering a
 * payload length of 0.  `cfg_verify` cannot see this -- the target is an
 * order-keyed oracle whose arguments are not compared.
 */

#include <stdint.h>
typedef unsigned int (*fnptr_t)(int *);

unsigned int FUN_0007c408(int param_1)
{
    if (param_1 == 0) return 0;
    int *p14 = *(int **)(param_1 + 0x14);
    if (p14 != 0) {
        fnptr_t fn = *(fnptr_t *)((char *)p14 + 4);
        if (fn != 0) {
            return fn(p14);
        }
    }
    return *(unsigned int *)(param_1 + 0x10);
}
