/* Reconstructed FUN_000779bc @ 0x779bc  (parity: 300/300 trials, PROVEN) */

extern int strlen(void);
extern void FUN_00078f88(unsigned int a, void* b, unsigned int c, void* d);

void FUN_000779bc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int local_80;
  int local_7c;
  unsigned short local_74;
  unsigned short local_72;
  unsigned int local_70;
  unsigned int local_6c;
  unsigned int local_5c;
  unsigned int local_4c;
  unsigned int local_38;
  unsigned int uStack_8;
  unsigned int uStack_4;

  local_74 = 0x204;
  local_80 = param_1;
  local_70 = param_1;
  uStack_8 = param_3;
  uStack_4 = param_4;
  local_7c = strlen();
  local_5c = 0x86f57;
  local_4c = 0;
  local_38 = 0;
  local_72 = 0xffff;
  local_6c = local_7c;
  FUN_00078f88(*(volatile unsigned int *)0x20002d20UL, &local_80, param_2, &uStack_8);
}

