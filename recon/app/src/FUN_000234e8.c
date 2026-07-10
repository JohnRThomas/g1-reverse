/* Reconstructed FUN_000234e8 @ 0x234e8  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086448(void *, int, int);
extern void DEBUG_PRINT(unsigned int);

int FUN_000234e8(void)
{
  int iVar1;
  unsigned int format_string;

  iVar1 = FUN_00086448((void*)0x200079a0UL,0xc9,0x1e);
  format_string = 0x0009e810UL;
  if (iVar1 != 0) {
    format_string = 0x0009e7fdUL;
  }
  DEBUG_PRINT(format_string);
  return iVar1;
}

