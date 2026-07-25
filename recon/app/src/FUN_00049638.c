/* Reconstructed FUN_00049638 @ 0x49638  (parity: 300/300 trials, PROVEN) */

/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern unsigned int FUN_00071eac(unsigned int, unsigned int, int, unsigned int, unsigned int, int, int, int, int, unsigned long long);

unsigned int FUN_00049638(unsigned int param_1)
{
    unsigned int uVar1 = FUN_00071eac(0x20004d18UL, 0x20028e68UL, 0x1400, 0x49091UL, param_1, 0, 0, 0xfffffff2, 0, 0ULL);
    *(volatile unsigned int*)0x2000a09cUL = uVar1;
    return 0;
}

