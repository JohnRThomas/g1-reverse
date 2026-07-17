#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0001793c @ 0x0001793c
 * public-name: FUN_0001793c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 * address symbols (name @ address):
 *   rodata_889d0                             @ 0x000889d0
 *   g_touch_key_irq_pending                  @ 0x20006a00
 *   g_pt_nfc_link_ready                      @ 0x20007bcc
 */
/* Reconstructed FUN_0001793c @ 0x1793c  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void FUN_00017858(int, int);
extern void FUN_00072880(int);

void FUN_0001793c(int param_1, int param_2, int param_3)
{
  int iVar1;
  FUN_00017858(((unsigned long)&rodata_889d0) /*=0x889d0*/, 0x200000);
  if ((param_3 == 0x200) && (*(volatile int*)((unsigned long)&g_pt_nfc_link_ready) /*=0x20007bcc*/ != 0)) {
    *(volatile int*)((unsigned long)&g_touch_key_irq_pending) /*=0x20006a00*/ = 1;
    iVar1 = get_device_info();
    FUN_00072880(iVar1 + 0xb0);
  }
  FUN_00017858(((unsigned long)&rodata_889d0) /*=0x889d0*/, 0x5c00000);
}
