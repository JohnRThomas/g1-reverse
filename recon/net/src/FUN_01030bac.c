/* net-core FUN_01030bac @ 0x1030bac  (parity 300 trials PROVEN) */

extern void FUN_01034d8c(unsigned int, unsigned int);
extern void FUN_0102eb8c(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b62e(void *, unsigned int, unsigned int);
extern void FUN_0102e284(unsigned int, unsigned int, void *, unsigned int);
extern void FUN_01034dd8(void *);

unsigned int FUN_01030bac(int param_1)
{
  volatile int *outer = (volatile int *)(*(volatile int *)(param_1 + 0x10) + 0x80);
  *outer = param_1;

  FUN_01034d8c(0, 0x1031555);
  FUN_0102eb8c(0x12, 1, 0);

  volatile unsigned int *puVar4 = *(volatile unsigned int **)(param_1 + 4);

  int local_buf[40];
  FUN_0103b62e(local_buf, 0, 0x84);

  if (puVar4[1] > 0xffff) {
    unsigned int tmp[2]; tmp[0] = 2; tmp[1] = 0x0103e004;
    FUN_0102e284(0x0103c094, 0x1080, tmp, 0);
  }
  if (puVar4[0] > 0xffff) {
    unsigned int tmp[2]; tmp[0] = 2; tmp[1] = 0x0103e030;
    FUN_0102e284(0x0103c094, 0x1080, tmp, 0);
  }

  FUN_01034dd8(local_buf);
  return 0;
}

