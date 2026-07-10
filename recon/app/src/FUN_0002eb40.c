/* Reconstructed FUN_0002eb40 @ 0x2eb40  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_00019c70(void);

unsigned int FUN_0002eb40(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  (void)param_1; (void)param_2;
  volatile unsigned char *p68 = (volatile unsigned char*)0x20018da6UL;
  volatile unsigned char *p6c = (volatile unsigned char*)0x20018da5UL;
  unsigned char bVar1 = *p68;
  unsigned int uVar3 = bVar1;
  if (*p6c != uVar3) {
    if (*(volatile unsigned int*)0x20007554UL == 0) {
      DEBUG_PRINT(0xa3e80, uVar3, param_3, 0, param_4);
    } else {
      FUN_00019c70();
    }
  }
  *p6c = bVar1;
  return uVar3;
}

