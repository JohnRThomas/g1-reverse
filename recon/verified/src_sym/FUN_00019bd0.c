/* Reconstructed FUN_00019bd0 @ 0x19bd0  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(void *, int, int);
extern void DEBUG_PRINT(unsigned long, ...);

int FUN_00019bd0(void)
{
  int iVar1;
  unsigned int format_string;

  iVar1 = z_impl_k_msgq_alloc_init((void*)0x2000751cUL,200,0x14);
  format_string = 0x0009b345UL;
  if (iVar1 != 0) {
    format_string = 0x0009b331UL;
  }
  DEBUG_PRINT(format_string);
  return iVar1;
}

