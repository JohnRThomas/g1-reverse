/* Reconstructed FUN_00019bd0 @ 0x19bd0  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086448(void *, int, int);
extern void DEBUG_PRINT(unsigned long, ...);

int FUN_00019bd0(void)
{
  int iVar1;

  iVar1 = FUN_00086448((void*)0x2000751cUL, 200, 0x14);
  if (iVar1 != 0) {
    DEBUG_PRINT(0x0009b331UL);
    return iVar1;
  }
  DEBUG_PRINT(0x0009b345UL);
  return iVar1;
}
