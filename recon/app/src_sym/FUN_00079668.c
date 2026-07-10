/* Reconstructed FUN_00079668 @ 0x79668  (parity: 300/300 trials, PROVEN) */

extern int cc_mbedtls_ctr_drbg_random_with_add(int*, int, int, int, int);

int FUN_00079668(int *param_1, int param_2, int param_3, int *param_4)
{
  int iVar1;
  if (param_1 == (int*)0) param_1 = (int*)0x2000cc30UL;
  if (*(volatile int*)param_1 == 0x5ac9bca5) {
    iVar1 = cc_mbedtls_ctr_drbg_random_with_add(param_1 + 0x47, param_2, param_3, 0, 0);
    if (iVar1 != 0) param_3 = 0;
    *param_4 = param_3;
  } else {
    iVar1 = (int)0xffff8fe8;
  }
  return iVar1;
}

