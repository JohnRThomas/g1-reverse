/* Reconstructed FUN_0002201c @ 0x2201c  (parity: 300/300 trials, PROVEN) */

/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int FUN_00071eac(int,int,int,int,int,int,int,int,int,unsigned long long);
extern void FUN_000864c2(int);
extern void FUN_00086726(int,int,int);

int FUN_0002201c(int param_1)
{
    FUN_000864c2(0x20007574);
    FUN_00086726(0x20003d28, 0x00019ff1, 0);
    FUN_00071eac(0x20003d60, 0x2001e968, 0x3000, 0x21da9, param_1, 0, 0, (int)0xfffffff1, 0, 0ULL);
    return 0;
}

