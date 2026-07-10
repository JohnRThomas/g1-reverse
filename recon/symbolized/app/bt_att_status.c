#include "g1_app_symbols.h"
/* named: bt_att_status */
/* Reconstructed bt_att_status @ 0x8206c  (parity: 300/300 trials, PROVEN) */

extern void* sys_slist_get(int);
extern int FUN_00058b78(int, void*);

void bt_att_status(char *param_1, int *param_2)
{
  if ((*param_2 & 1) != 0) {
    int base = *(int*)(param_1 - 8);
    if (base != 0) {
      if (*(int*)(param_1 + 0x11c) == 0) {
        unsigned int *puVar1 = (unsigned int*)sys_slist_get(base + 4);
        if (puVar1 != 0) {
          int iVar2 = FUN_00058b78((int)(param_1-8), puVar1);
          if (iVar2 < 0) {
            int iVar2b = *(int*)(param_1 - 8);
            *puVar1 = *(unsigned int*)(iVar2b + 4);
            *(unsigned int**)(iVar2b + 4) = puVar1;
            if (*(int*)(iVar2b + 8) == 0) {
              *(unsigned int**)(iVar2b + 8) = puVar1;
            }
          }
        }
      }
    }
  }
}

