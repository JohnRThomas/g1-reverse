/* net-core FUN_01009ea4 @ 0x1009ea4  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int);
extern void FUN_01025a84(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_01027258(unsigned int, unsigned int);

int FUN_01009ea4(unsigned int param_1, unsigned char param_2_raw, unsigned int param_3)
{
  volatile unsigned char param_2_store = param_2_raw;
  unsigned char param_2 = param_2_store;

  unsigned int local_c = 0;
  unsigned int uVar3 = param_1;
  if (param_1 == 0) {
    uVar3 = 1;
  }
  unsigned char cVar2 = (unsigned char)uVar3;
  if (param_1 != 0) {
    cVar2 = 0;
  }

  if ((param_1 & 3) != 0) {
    FUN_01008d00(0x18, 0x86);
  }

  if (param_2 != 0) {
    unsigned int iVar1 = FUN_01027258(0, param_3);
    local_c = (unsigned int)param_2 * 4 + iVar1 + 0xc;
    if (cVar2 != 1) {
      volatile unsigned int * const pp = (volatile unsigned int *)0x21000bb4;
      *pp = param_1;
      volatile unsigned char *base = (volatile unsigned char *)(*pp);
      base[8] = param_2;
      *(volatile unsigned int *)(base + 4) = param_1 + 0xc;
      unsigned int off4 = *(volatile unsigned int *)(base + 4);
      *(volatile unsigned int *)base = (unsigned int)param_2 * 4 + off4;
      unsigned int arg0 = *(volatile unsigned int *)(base + 4);
      FUN_01025a84(arg0, 0, (unsigned int)param_2 << 2);
      unsigned int base2 = *pp;
      FUN_01027258(base2, param_3);
    }
  }
  return local_c;
}

