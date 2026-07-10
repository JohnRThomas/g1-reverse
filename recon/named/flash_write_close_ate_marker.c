/* named: flash_write_close_ate_marker */
/* Reconstructed flash_write_close_ate_marker @ 0x84e58  (parity: 300/300 trials, PROVEN) */

extern void flash_write_padded_entry(int a, unsigned int b, void *c, int d, int e);
void flash_write_close_ate_marker(int param_1)
{
  unsigned int uVar1;
  unsigned char local_c[8];
  uVar1 = (*(volatile int *)(param_1 + 8) - 0x18) & 0xfffffff8;
  *(unsigned int *)local_c = (((uVar1 >> 8) & 0xffffffU) << 8) | 1;
  *(unsigned int *)(local_c + 4) = 1;
  flash_write_padded_entry(param_1, uVar1, local_c, 1, param_1);
}

