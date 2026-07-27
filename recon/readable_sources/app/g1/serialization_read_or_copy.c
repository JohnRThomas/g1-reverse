
/* Reconstructed FUN_0007c670 @ 0x7c670  (parity: 300/300 trials, PROVEN)
 *
 * P4 iteration 40 -- TWO DROPPED ARGUMENTS.  The shipped tail passes THREE
 * live registers to the indirect `+8` iterator op:
 *     0007c672  mov  r3, r2              ; r2 itself is never rewritten
 *     0007c674  mov  r4, r1              ; r1 itself is never rewritten
 *     0007c67c  strd r5, r5, [r1]
 *     0007c680  ldr  r5, [r0, #0x14]
 *     0007c684  ldr  r6, [r5, #8]
 *     0007c688  mov  r0, r5
 *     0007c68a  blx  r6                  ; r0=descriptor r1=out view r2=flag
 * The previous body wrote `fp(iVar1)`.  Measured in the shipped-in build
 * /private/tmp/g1-i39c-app/zephyr/zephyr.elf that compiled to
 *     78c4c  ldr r1,[r3,#8] ; 78c5c mov r0,r3 ; 78c5e ldr r2,[r3,#8] ; blx r2
 * so BOTH r1 and r2 arrived holding the op pointer itself.  FUN_00024a40 /
 * FUN_00024ad8 write their two-word result through r1, so the callee would
 * have stored into a flash code address, and their rewind flag (r2) would have
 * been permanently non-zero, pinning the payload cursor at 0.  `cfg_verify` is
 * blind to it for the same reason as FUN_0007c408: dropped register arguments
 * to an order-keyed oracle.
 */

extern unsigned int serialization_copy_fields_0c_10(int, unsigned int*);

int serialization_read_or_copy(int param_1, int *param_2, int param_3)
{
    if (param_1 != 0) {
        if (param_2 == (int*)0) {
            param_1 = 0;
        } else {
            param_2[0] = 0;
            param_2[1] = 0;
            int iVar1 = *(volatile int*)((char*)param_1 + 0x14);
            if ((iVar1 == 0) || (*(volatile int*)((char*)iVar1 + 8) == 0)) {
                if (param_3 != 0) {
                    serialization_copy_fields_0c_10(param_1, param_2);
                }
            } else {
                void (*fp)(int, int *, int) =
                    (void(*)(int, int *, int))*(volatile unsigned int*)((char*)iVar1 + 8);
                fp(iVar1, param_2, param_3);
            }
            param_1 = *param_2;
        }
    }
    return param_1;
}
