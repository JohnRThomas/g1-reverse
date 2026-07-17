#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a570 @ 0x0005a570
 * public-name: sc_indicate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sc_indicate                              <= FUN_0005a570 @ 0x0005a570
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 * address symbols (name @ address):
 *   g_service_changed_range                  @ 0x200063f8
 *   g_bt_gatt_flags                          @ 0x20006448
 */
/* Reconstructed FUN_0005a570 @ 0x5a570  (parity: 300/300 trials, PROVEN) */

extern int atomic_or_0(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern long long FUN_0008270c(unsigned int a);
extern void FUN_0007350c(unsigned int a, int b, unsigned int c, unsigned int d);

void sc_indicate(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned short *puVar1;
  int iVar2;
  unsigned int uVar3;
  long long uVar4;

  uVar3 = atomic_or_0(((unsigned long)&g_bt_gatt_flags) /*=0x20006448*/,1,param_3,param_4,param_4);
  iVar2 = ((unsigned long)&g_service_changed_range) /*=0x200063f8*/;
  if ((uVar3 & 1) == 0) {
    *(volatile short *)(((unsigned long)&g_service_changed_range) /*=0x200063f8*/ + 0x18) = (short)param_1;
  } else {
    puVar1 = (unsigned short *)(((unsigned long)&g_service_changed_range) /*=0x200063f8*/ + 0x1a);
    if (param_1 < *(volatile unsigned short *)(((unsigned long)&g_service_changed_range) /*=0x200063f8*/ + 0x18)) {
      *(volatile short *)(((unsigned long)&g_service_changed_range) /*=0x200063f8*/ + 0x18) = (short)param_1;
      if (param_2 <= *(volatile unsigned short*)puVar1) goto LAB;
    } else if (param_2 <= *(volatile unsigned short*)puVar1) {
      return;
    }
  }
  *(volatile short *)(iVar2 + 0x1a) = (short)param_2;
LAB:
  uVar4 = FUN_0008270c(((unsigned long)&g_bt_gatt_flags) /*=0x20006448*/);
  if ((int)((int)uVar4 << 0x1e) < 0) {
    return;
  }
  FUN_0007350c(0, (int)(uVar4 >> 32), 0x148, 0);
}
