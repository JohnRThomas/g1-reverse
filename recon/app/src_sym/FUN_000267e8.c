/* Reconstructed FUN_000267e8 @ 0x267e8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007cab4(void);
float FUN_000267e8(int param_1)
{
  if (*(volatile char *)(param_1 + 0x28) == 0) {
    FUN_0007cab4();
  }
  float a = *(volatile float *)(param_1 + 0x2c);
  union { unsigned int u; float f; } c;
  c.u = 0x42652e14u;
  return a * c.f;
}

