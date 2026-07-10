#include "g1_app_symbols.h"
/* named: settings_nvs_backend_init */
/* Reconstructed settings_nvs_backend_init @ 0x7f344  (parity: 300/300 trials, PROVEN) */

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

