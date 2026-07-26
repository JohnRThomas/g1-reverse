/* Reconstructed FUN_0002ea28 @ 0x2ea28  (parity: 300/300 trials, PROVEN)
 *
 * ITERATION 39 DEFECT FIX — the request record handed to FUN_0000e2b4 is FOUR
 * words, not three.  Shipped prologue:
 *
 *   0002ea2c  ldr  r3, [pc, #0x40]   ; literal @0x2ea70 = 0x00088a50
 *   0002ea30  str  r3, [sp, #0x14]   ; <<< request[3] = the battery curve table
 *   0002ea3a  strd r4, r4, [sp, #8]  ; request[0] = request[1] = 0
 *   0002ea3e  str  r4, [sp, #0x10]   ; request[2] = 0
 *   0002ea40  bl   #0x2e988          ; read v/i/t into sp+8 / sp+0xc / sp+0x10
 *   0002ea54  add  r0, sp, #8        ; r0 = request
 *   0002ea56  bl   #0xe2b4
 *
 * FUN_0000e2b4 NULL-checks word 3 (`ldr r3,[r0,#0xc]` / `cbz r3` -> -EINVAL)
 * and forwards it in r1 to FUN_0000e53c, which memcpy's 0x1600 bytes out of it
 * into the estimator workspace.  Omitting the store left a stale stack word
 * there (measured 0x0009d5ba), which is non-NULL, so the guard passed and 5632
 * bytes of unrelated .rodata became the battery curve: the EKF covariance went
 * to NaN and device_info[0xfc0] stuck at 0 for the whole run.
 *
 * The four words must be ONE object, so they are declared as one record here
 * rather than as separate locals.
 */

extern int FUN_0000e2b4(void*, int);
extern int FUN_0002e988(int, void*, void*, void*);
extern unsigned long long k_uptime_get_3(void);
extern void FUN_0007cef6(int, int, void*);

int FUN_0002ea28(int param_1)
{
    struct {
        unsigned char auStack_28[8];
        int local_20;
        int uStack_1c;
        int local_18;
        const void *pStack_14;
    } frame;
    int iVar1;

    frame.pStack_14 = (const void *)0x00088a50u;
    frame.local_20 = 0;
    frame.uStack_1c = 0;
    frame.local_18 = 0;
    iVar1 = FUN_0002e988(param_1, &frame.local_20, &frame.uStack_1c, &frame.local_18);
    if (iVar1 >= 0) {
        FUN_0007cef6(param_1, 0x39, frame.auStack_28);
        iVar1 = FUN_0000e2b4(&frame.local_20, 0);
        if (iVar1 >= 0) {
            unsigned long long uVar2 = k_uptime_get_3();
            *(volatile unsigned long long*)0x20004790UL = uVar2;
            iVar1 = 0;
        }
    }
    return iVar1;
}
