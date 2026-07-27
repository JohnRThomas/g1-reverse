#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00050c24 @ 0x00050c24
 * public-name: mpu_region_alloc_fail_log
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   mpu_region_alloc_fail_log                <= FUN_00050c24 @ 0x00050c24
 * address symbols (name @ address):
 *   rodata_88228                             @ 0x00088228
 *   rodata_f2132                             @ 0x000f2132
 */
/* Reconstructed FUN_00050c24 @ 0x50c24  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int mpu_region_alloc_fail_log(unsigned int param_1)
{
  struct { unsigned int a; unsigned int b; unsigned int c; } local;
  local.a = 3;
  local.b = ((unsigned long)&rodata_f2132) /*=0xf2132*/;
  local.c = param_1;
  z_log_msg_runtime_create(((unsigned long)&rodata_88228) /*=0x88228*/, 0x1840, &local, 0);
  return 0xffffffea;
}
