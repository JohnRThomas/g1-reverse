/* Reconstructed FUN_00019bd0 @ 0x19bd0  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086448(void *, int, int);
extern void DEBUG_PRINT(unsigned int);

int FUN_00019bd0(void)
{
  int iVar1;
  unsigned int format_string;

  iVar1 = FUN_00086448((void*)0x2000751cUL,200,0x14);
  format_string = 0x0009b345UL;
  if (iVar1 != 0) {
    format_string = 0x0009b331UL;
  }
  DEBUG_PRINT(format_string);
  return iVar1;
}

