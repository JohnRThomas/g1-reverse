#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_settings_nvs_backend_cfg__param_0526   [param_0526; library]
 * Raw function identity: 0x0007f344.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007f344 @ 0x0007f344
 * public-name: settings_nvs_backend_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_mount                                <= FUN_0004c548 @ 0x0004c548
 *   settings_nvs_read_latest                 <= FUN_0007e9dc @ 0x0007e9dc
 *   settings_nvs_backend_init                <= FUN_0007f344 @ 0x0007f344
 */
/* Reconstructed FUN_0007f344 @ 0x7f344  (parity: 300/300 trials, PROVEN) */

extern int nvs_mount(void*);
extern int settings_nvs_read_latest(void*, unsigned int, unsigned short*, unsigned int);

int settings_nvs_backend_init(char *param_1, unsigned int param_2)
{
  int iVar1;
  *(int*)(param_1+0x30) = *(int*)(param_1+0x3c);
  if (*(int*)(param_1+0x3c) == 0) {
    iVar1 = -0x13;
  } else {
    union { unsigned int w; unsigned short h[2]; } uStack;
    uStack.w = param_2;
    iVar1 = nvs_mount(param_1+8);
    if (iVar1 == 0) {
      int iVar2 = settings_nvs_read_latest(param_1+8, 0x8000, &uStack.h[1], 2);
      if (iVar2 < 0) {
        uStack.h[1] = 0x8000;
      }
      *(unsigned short*)(param_1+0x38) = uStack.h[1];
    }
  }
  return iVar1;
}
