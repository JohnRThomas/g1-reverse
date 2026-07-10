/* named: orientation_filter_update_dt */
/* Reconstructed orientation_filter_update_dt @ 0x267ac  (parity: 300/300 trials, PROVEN) */

extern long long thunk_FUN_00074f68(void);

float orientation_filter_update_dt(int param_1)
{
  unsigned long long lVar2;
  unsigned long long P;
  unsigned int uVar1;
  unsigned int diff;
  float result;

  lVar2 = (unsigned long long)thunk_FUN_00074f68();
  P = lVar2 * 1000ULL;
  uVar1 = (unsigned int)(P >> 15);
  diff = uVar1 - *(volatile unsigned int *)(long)(param_1 + 0x3c);
  result = (float)diff / 1000.0f;
  *(volatile float *)(long)(param_1 + 0x40) = result;
  *(volatile unsigned int *)(long)(param_1 + 0x38) = uVar1;
  *(volatile unsigned int *)(long)(param_1 + 0x3c) = uVar1;
  return result;
}

