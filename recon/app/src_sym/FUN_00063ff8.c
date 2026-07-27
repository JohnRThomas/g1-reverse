/* Reconstructed FUN_00063ff8 @ 0x63ff8  (parity: 300/300 trials, PROVEN) */

extern void flash_area_erased_val(unsigned long);
extern int flash_area_write(int a, unsigned int b, void *c, int d);

int FUN_00063ff8(int param_1)
{
  unsigned int local_28[4];
  unsigned int iVar2 = *(volatile unsigned int*)(param_1+8);
  unsigned int i;
  volatile unsigned int *src = (volatile unsigned int*)0x0009907cUL;
  int r;
  flash_area_erased_val(param_1);
  for (i = 0; i < 4; i++) {
    local_28[i] = src[i];
  }
  r = flash_area_write(param_1, (iVar2 - 0x10) & 0xfffffff8, local_28, 0x10);
  if (r != 0) r = 1;
  return r;
}

