/* Reconstructed FUN_0007fe72 @ 0x7fe72  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007f97c(int, int, void*, int);
extern int FUN_0007fb20(int, int, ...);

int FUN_0007fe72(int param_1, unsigned char *param_2, int param_3, int param_4)
{
  int iVar1, iVar2;
  /* 0x7fe72 `push {r0,r1,r2,...}` puts param_2 (r1) in the sp+4 slot that
   * 0x7fe86 `add r2,sp,#4` then hands to the register read as its buffer. */
  unsigned int dummy = (unsigned int)(unsigned long)param_2;
  iVar1 = FUN_0007fb20(param_1, 1, param_3, param_4, param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_0007f97c(param_1, 0x14, &dummy, 1);
    /* 0x7fe8e ldrb.w r3,[sp,#4] ; 0x7fe94 ubfx r3,r3,#2,#1 ; 0x7fe9c strb r3,[r7]
     * -- bit 2 (MASTER_ON) of the BYTE the read stored in the stack buffer, not
     * of the out-pointer's own value.  Reading the pointer made lsm6dso_init_chip
     * see a non-zero master flag and issue a spurious sh_master_set(0). */
    *param_2 = (unsigned char)((dummy >> 2) & 1);
    iVar2 = FUN_0007fb20(param_1, 0);
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

