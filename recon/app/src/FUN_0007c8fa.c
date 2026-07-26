/* Reconstructed FUN_0007c8fa @ 0x7c8fa  (parity: 300/300 trials, PROVEN) */

extern int FUN_000257ec(int, int, void*, int, int, int);
extern void FUN_00025850(int, int, void*, int);

void FUN_0007c8fa(int param_1, int param_2)
{
  int iVar1;
  unsigned char local;
  iVar1 = FUN_000257ec(param_1, 1, &local, 1, param_1, param_2);
  if (iVar1 == 0) {
    local = (local & ~0x1f) | (param_2 & 0x1f);
    /* 0x7c920 `movs r3,#1` / 0x7c922 `mov r0,r5` / 0x7c924 `mov r1,r3` /
     * 0x7c926 `add r2,sp,#7` / 0x7c92a `bl 0x25850` -- FOUR register arguments.
     * r3 is the I2C byte COUNT (0x25850: `mov r5,r3` ... `cbz r3`), so dropping
     * it made the length whatever r3 happened to hold: measured a 26-byte write
     * to the ST25DV system port (0x57) against the shipped 3-byte one. */
    FUN_00025850(param_1, 1, &local, 1);
  }
}

