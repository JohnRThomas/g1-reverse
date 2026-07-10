/* named: FUN_00085d36 */
/* Reconstructed FUN_00085d36 @ 0x85d36  (parity: 300/300 trials, PROVEN) */

int FUN_00085d36(unsigned int *param_1)
{
  if (*((unsigned char*)param_1 + 0x10) == 0) {
    return param_1[2] == 0;
  }
  if (param_1[0] < param_1[3]) {
    return *(unsigned char*)(param_1[0]) == 0xff;
  }
  return 0;
}

