#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005fb30 @ 0x0005fb30
 * public-name: pdm_start_and_check
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   onoff_release                            <= FUN_0004ba38 @ 0x0004ba38
 *   pdm_start_and_check                      <= FUN_0005fb30 @ 0x0005fb30
 *   nrfx_pdm_start                           <= FUN_00066214 @ 0x00066214
 *   log_forward_zero_arg                     <= FUN_000837a2 @ 0x000837a2
 * address symbols (name @ address):
 *   rodata_881a0                             @ 0x000881a0
 *   rodata_f5692                             @ 0x000f5692
 */
/* Reconstructed FUN_0005fb30 @ 0x5fb30  (parity: 300/300 trials, PROVEN) */

extern int nrfx_pdm_start(void);
extern void log_forward_zero_arg(unsigned int a, unsigned int b, void *c);
extern void onoff_release(unsigned int a);

unsigned int pdm_start_and_check(unsigned int *param_1)
{
  unsigned int uVar1;
  struct { unsigned int count, format; } error;
  int iStack_18;

  iStack_18 = nrfx_pdm_start();
  if (iStack_18 == 0x0bad0000) {
    uVar1 = 0;
  } else {
    error.format = ((unsigned long)&rodata_f5692) /*=0xf5692*/;
    error.count = 3;
    log_forward_zero_arg(((unsigned long)&rodata_881a0) /*=0x881a0*/, 0x1840, &error);
    if ((int)((unsigned int)*(volatile unsigned char *)((char*)param_1 + 0x50) << 0x1f) < 0) {
      onoff_release(*param_1);
    }
    uVar1 = 0xfffffffb;
    *(volatile unsigned char *)((char*)param_1 + 0x51) = 0;
  }
  return uVar1;
}
