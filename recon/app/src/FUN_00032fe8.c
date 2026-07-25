/* Reconstructed FUN_00032fe8 @ 0x32fe8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void*, void*, unsigned int);
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int FUN_00071eac(void*, void*, unsigned int, void*, int, int, int, unsigned int, int, unsigned long long);

void FUN_00032fe8(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20019ef1UL;
  int iVar2;

  if (*pcVar1 != 0) {
    DEBUG_PRINT((void*)0xa757fUL, (void*)0xa75c2UL, 0xab8);
    return;
  }
  iVar2 = FUN_00071eac((void*)0x20004870UL, (void*)0x20027a68UL, 0xc00, (void*)0x32421UL, 0,0,0,0xfffffff4,0,0ULL);
  if (iVar2 == 0) {
    *pcVar1 = 1;
  }
  return;
}

