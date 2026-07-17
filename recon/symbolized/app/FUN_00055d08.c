#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055d08 @ 0x00055d08
 * public-name: FUN_00055d08
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_88120                             @ 0x00088120
 *   rodata_f398f                             @ 0x000f398f
 *   rodata_f39ae                             @ 0x000f39ae
 *   rodata_f39ca                             @ 0x000f39ca
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 *   g_bt_pub_key_cb_slist                    @ 0x2000ac74
 */
/* Reconstructed FUN_00055d08 @ 0x55d08  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0004d944(unsigned,unsigned,void*,int);
extern int FUN_00053d70(unsigned,int,int);
int FUN_00055d08(int param_1)
{
  volatile int *piVar1; int *piVar3, iVar4; unsigned *puVar2; unsigned uVar5;
  unsigned local_20, local_1c;
  piVar1 = (volatile int*)((unsigned long)&g_bt_pub_key_cb_slist) /*=0x2000ac74*/;
  if ((*(unsigned char*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 0xa2) & 6) == 6) {
    if (param_1 == 0) iVar4 = -0x16;
    else {
      for (piVar3 = (int*)*(int*)((unsigned long)&g_bt_pub_key_cb_slist) /*=0x2000ac74*/; piVar3 != 0; piVar3 = (int*)*piVar3) {
        if (piVar3 + -1 == (int*)param_1) {
          local_1c = ((unsigned long)&rodata_f39ae) /*=0xf39ae*/; local_20 = 2;
          FUN_0004d944(((unsigned long)&rodata_88120) /*=0x88120*/, 0x1080, &local_20, 0);
          return -0x78;
        }
      }
      *(volatile int*)(param_1 + 4) = *(int*)((unsigned long)&g_bt_pub_key_cb_slist) /*=0x2000ac74*/;
      *piVar1 = param_1 + 4;
      if (piVar1[1] == 0) piVar1[1] = param_1 + 4;
      puVar2 = (unsigned*)((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/;
      uVar5 = __atomic_fetch_or(puVar2, 0x20, __ATOMIC_SEQ_CST);
      if ((uVar5 & 0x20) == 0) {
        (void)__atomic_fetch_and(puVar2, 0xffffffef, __ATOMIC_SEQ_CST);
        iVar4 = FUN_00053d70(0x2025, 0, 0);
        if (iVar4 != 0) {
          local_1c = ((unsigned long)&rodata_f39ca) /*=0xf39ca*/; local_20 = 2;
          FUN_0004d944(((unsigned long)&rodata_88120) /*=0x88120*/, 0x1040, &local_20, 0);
          (void)__atomic_fetch_and(puVar2, 0xffffffdf, __ATOMIC_SEQ_CST);
          for (piVar3 = (int*)*piVar1; piVar3 != 0; piVar3 = (int*)*piVar3) {
            if ((void*)piVar3[-1] != 0) (*(void(*)(int))piVar3[-1])(0);
          }
          *piVar1 = 0; piVar1[1] = 0;
          return iVar4;
        }
      }
      iVar4 = 0;
    }
  } else {
    local_1c = ((unsigned long)&rodata_f398f) /*=0xf398f*/; local_20 = 2; iVar4 = -0x86;
    FUN_0004d944(((unsigned long)&rodata_88120) /*=0x88120*/, 0x1080, &local_20, 0);
  }
  return iVar4;
}
