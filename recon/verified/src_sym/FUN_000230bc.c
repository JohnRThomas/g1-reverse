/* Reconstructed FUN_000230bc @ 0x230bc  (parity: 300/300 trials, PROVEN) */

extern unsigned int memset_bytes(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void flash_settings_write_and_verify(unsigned int, unsigned int, unsigned int);

unsigned int FUN_000230bc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;

  uVar1 = memset_bytes(param_1 + 0x10c6,0xff,0xc0,param_1 + 0x10c6,param_4);
  flash_settings_write_and_verify(0x00135000UL,uVar1,0xc0);
  return 0;
}

