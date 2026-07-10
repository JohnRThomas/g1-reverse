#include "g1_app_symbols.h"
/* named: FUN_0001793c */
/* globals referenced:
//   0x20006a00  g_touch_key_irq_pending      
//   0x20007bcc  g_pt_nfc_link_ready          
*/
/* Reconstructed FUN_0001793c @ 0x1793c  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void FUN_00017858(int, int);
extern void FUN_00072880(int);

void FUN_0001793c(int param_1, int param_2, int param_3)
{
  int iVar1;
  FUN_00017858(((uintptr_t)&tbl_889d0) /*=0x889d0*/, 0x200000);
  if ((param_3 == 0x200) && (*(volatile int*)((uintptr_t)&g_pt_nfc_link_ready) /*=0x20007bcc*/ != 0)) {
    *(volatile int*)((uintptr_t)&g_touch_key_irq_pending) /*=0x20006a00*/ = 1;
    iVar1 = get_device_info();
    FUN_00072880(iVar1 + 0xb0);
  }
  FUN_00017858(((uintptr_t)&tbl_889d0) /*=0x889d0*/, 0x5c00000);
}

