/* net-core FUN_010128bc @ 0x10128bc  (parity 300 trials PROVEN) */
#define C_0101295c 0x01011869
#define C_01012958 0x01011add

extern void FUN_0100ef88(void *, int, int, int, unsigned int);
extern int FUN_0101f888(void);

void FUN_010128bc(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned short uVar1;
  int uVar2;
  int iVar3;
  unsigned char cVar4;
  unsigned int uVar5;

  uVar5 = *(unsigned short *)(param_1 + 2);
  if ((int)(uVar5 << 0x1c) < 0) {
    *(volatile unsigned char *)(param_1 + 0x85) = 0x3c;
    uVar1 = **(unsigned short **)(param_1 + 0x1c);
    *(volatile unsigned char *)(param_1 + 0xa3) = 0xff;
    *(volatile unsigned short *)(param_1 + 0x86) = uVar1;
    *(volatile unsigned short *)(param_1 + 0xa4) = 0xffff;
    FUN_0100ef88(param_1 + 0x7c, C_0101295c, 2, 0xffff, param_4);
    uVar5 = *(unsigned short *)(param_1 + 2);
  }
  if ((int)(uVar5 << 0x1f) < 0) {
    uVar1 = **(unsigned short **)(param_1 + 0x1c);
    iVar3 = FUN_0101f888();
    if (iVar3 != 0) goto LAB_end;
    cVar4 = param_1[0xd];
    *(volatile unsigned short *)(param_1 + 0xb1) = uVar1;
    *(volatile unsigned char *)(param_1 + 0xb0) = *param_1;
    *(volatile unsigned char *)(param_1 + 0xaf) = 0x3c;
    uVar2 = C_01012958;
  } else {
    iVar3 = FUN_0101f888();
    if (iVar3 != 0) goto LAB_end;
    cVar4 = param_1[0xd];
    *(volatile unsigned char *)(param_1 + 0xb0) = *param_1;
    *(volatile unsigned char *)(param_1 + 0xb1) = 0xff;
    *(volatile unsigned char *)(param_1 + 0xb2) = 0xff;
    *(volatile unsigned char *)(param_1 + 0xaf) = 0x3c;
    uVar2 = C_01012958;
  }
  if (cVar4 != 0) {
    cVar4 = param_1[0x40];
  }
  *(volatile unsigned char *)(param_1 + 0xb3) = cVar4;
  FUN_0100ef88(param_1 + 0xa6, uVar2, 2, cVar4, param_4);
LAB_end:
  *(volatile unsigned char *)(param_1 + 0x79) = 1;
  return;
}

