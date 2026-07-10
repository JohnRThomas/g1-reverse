#include "g1_app_symbols.h"
/* named: mpu_region_alloc_fail_log */
/* Reconstructed mpu_region_alloc_fail_log @ 0x50c24  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004d944(unsigned int a, unsigned int b, void *c, unsigned int d);

unsigned int mpu_region_alloc_fail_log(unsigned int param_1)
{
  struct { unsigned int a; unsigned int b; unsigned int c; } local;
  local.a = 3;
  local.b = "Failed to allocate new MPU region %u\n" /*=0xf2132*/;
  local.c = param_1;
  FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88228*/, 0x1840, &local, 0);
  return 0xffffffea;
}

