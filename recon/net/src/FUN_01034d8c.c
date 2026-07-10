/* net-core FUN_01034d8c @ 0x1034d8c  (parity 300 trials PROVEN) */

extern void FUN_0102eb2c(int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
unsigned int FUN_01034d8c(unsigned int param_1, int param_2, int param_3)
{
  if (param_2 == 0) {
    FUN_01039bbe(0x0103d2a7, 0x0103e700, 0x34);
    FUN_01039bb0(0x0103e700, 0x34);
  }
  int *piVar1 = (int*)0x21004aec;
  unsigned int uVar2;
  if (*(char*)((char*)piVar1+4) == 0) {
    FUN_0102eb2c(0x12);
    uVar2 = 0x0bad0000;
    *(unsigned char*)((char*)piVar1+4) = 1;
    *piVar1 = param_2;
    piVar1[2] = param_3;
  } else {
    uVar2 = 0x0bad000c;
  }
  return uVar2;
}

