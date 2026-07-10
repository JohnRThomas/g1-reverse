/* net-core FUN_0102e974 @ 0x102e974  (parity 300 trials PROVEN) */

extern unsigned int FUN_0102eb70(void);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

void FUN_0102e974(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int iVar1 = 0x2100076cu;
  unsigned int iVar2;

  iVar2 = FUN_0102eb70();
  if (iVar2 != 0) {
    FUN_01039bbe(0x0103d2a7u, 0x0103d7fbu, 0x55);
    FUN_01039bb0(0x0103d7fbu, 0x55);
  }
  *(volatile unsigned int *)(iVar1 + param_1 * 8) = param_3;
  *(volatile unsigned int *)(iVar1 + param_1 * 8 + 4) = param_2;
  return;
}

