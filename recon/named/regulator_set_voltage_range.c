/* named: regulator_set_voltage_range */
/* Reconstructed regulator_set_voltage_range @ 0x84300  (parity: 300/300 trials, PROVEN) */

extern int FUN_00062070(unsigned int, unsigned int, void*);
extern int dev_write_reg3(unsigned int, int, int, int);
extern void dev_reg_modify_bits(unsigned int, int, int, unsigned int, unsigned int);

void regulator_set_voltage_range(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char stk[0x14];
  int iVar1;
  unsigned int uVar2;

  iVar1 = FUN_00062070(param_3, param_4, stk+0xe);
  if (iVar1 != -0x16) {
    iVar1 = dev_write_reg3(*(unsigned int*)(param_1+0x1c), 4, ((param_2+4)*2) & 0xfe, stk[0xe]);
    if (iVar1 >= 0) {
      uVar2 = (1u << (param_2 & 0xff)) & 0xff;
      dev_reg_modify_bits(*(unsigned int*)(param_1+0x1c), 4, 0xf, uVar2, uVar2);
    }
  }
  return;
}

