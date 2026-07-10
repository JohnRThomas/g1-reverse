/* net-core FUN_0102cfbc @ 0x102cfbc  (parity 300 trials PROVEN) */

typedef unsigned int undefined4;
extern void FUN_010317d4(void);
extern void FUN_0102f4ec(undefined4);
extern void FUN_01039722(undefined4);
extern void FUN_0102e9bc(void);

void FUN_0102cfbc(undefined4 param_1)
{
  unsigned int basepri_save;
  __asm__ volatile (
      "mrs %0, basepri\n"
      "movs r2, #0x40\n"
      "msr basepri_max, r2\n"
      "isb sy\n"
      : "=r"(basepri_save) :: "r2","memory");
  FUN_010317d4();
  FUN_0102f4ec(param_1);
  FUN_01039722(0x0103d42c);
  while (1) {
    FUN_0102e9bc();
  }
}

