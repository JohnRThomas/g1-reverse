/* Reconstructed FUN_00056ea8 @ 0x56ea8  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_lookup_addr_le(void);
extern void FUN_000813ca(unsigned int a, unsigned int b, void* c);
extern void FUN_000566a4(int a);

int FUN_00056ea8(void)
{
  int iVar1;
  unsigned int local_20;
  unsigned int local_1c;
  unsigned int uStack_18;
  unsigned short local_14;

  iVar1 = bt_conn_lookup_addr_le();
  if (iVar1 != 0) {
    unsigned char b = *(volatile unsigned char *)(iVar1 + 0xd);
    if (b < 9) {
      uStack_18 = *(volatile unsigned int *)(0x8b220UL + (unsigned int)b * 4);
    } else {
      uStack_18 = 0xf3c2d;
    }
    local_1c = 0xf3dc4;
    local_14 = 0x200;
    local_20 = 0x1000003;
    FUN_000813ca(0x88108, 0x1c80, &local_20);
    FUN_000566a4(iVar1);
    iVar1 = 1;
  }
  return iVar1;
}

