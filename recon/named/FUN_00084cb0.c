/* named: FUN_00084cb0 */
/* Reconstructed FUN_00084cb0 @ 0x84cb0  (parity: 300/300 trials, PROVEN) */

extern unsigned int dev_write_reg3(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);

unsigned int FUN_00084cb0(int param_1)
{
  if (**(volatile char **)(param_1 + 0x10) != 0) {
    return dev_write_reg3(**(volatile unsigned int **)(param_1 + 4), 7, 0, 1);
  }
  return 0xffffffea;
}

