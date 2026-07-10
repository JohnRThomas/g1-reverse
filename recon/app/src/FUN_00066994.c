/* Reconstructed FUN_00066994 @ 0x66994  (parity: 300/300 trials, PROVEN) */

extern int FUN_00066850(void);
extern void FUN_0007e2ec(void*, int);
extern void FUN_0007e2fa(void*, void*, void*, int, unsigned int);

int FUN_00066994(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *puVar1 = (volatile int*)0x2000b348UL;
  int iVar2;

  if (param_1 != 0) {
    iVar2 = 0x0bad0005;
    if (*(volatile unsigned char*)0x2000b378UL == 0) {
      puVar1[0] = param_2;
      puVar1[1] = param_3;
      iVar2 = FUN_00066850();
      if (iVar2 == 0x0bad0000) {
        puVar1[2] = 0;
        puVar1[3] = 0;
        *(volatile unsigned char*)0x2000b378UL = 1;
        *(volatile unsigned char*)0x2000b380UL = 0;
      }
    }
    return iVar2;
  }
  FUN_0007e2fa((void*)0x99cbdUL, (void*)0xf6c00UL, (void*)0xf6d5eUL, 0x19b, param_4);
  FUN_0007e2ec((void*)0xf6d5eUL, 0x19b);
  return 0;
}

