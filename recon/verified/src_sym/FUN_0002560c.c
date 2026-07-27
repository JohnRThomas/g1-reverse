/* Reconstructed FUN_0002560c @ 0x2560c  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_000330a8(unsigned int);
extern int process_pt_data(void);
extern void DEBUG_PRINT(unsigned long, ...);

int FUN_0002560c(void)
{
  int iVar1;
  iVar1 = FUN_000330a8(*(volatile unsigned int*)0x20007a44UL /* device_info.gap_1030+24 */);
  if (iVar1 == 0) {
    iVar1 = process_pt_data();
    if (iVar1 != 0) { iVar1 = -2; }
  } else {
    DEBUG_PRINT(0x0009f196);
    iVar1 = -1;
  }
  return iVar1;
}

