#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025474 @ 0x00025474
 * public-name: update_box_field_debounce
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   is_box_field_timer_expired               <= FUN_00025458 @ 0x00025458
 *   update_box_field_debounce                <= FUN_00025474 @ 0x00025474
 * address symbols (name @ address):
 *   g_box_last_seen_uptime                   @ 0x20007a10
 */
/* Reconstructed FUN_00025474 @ 0x25474  (parity: 300/300 trials, PROVEN) */

extern unsigned int is_box_field_timer_expired(void);
extern int thunk_FUN_00074f68(void);

unsigned int update_box_field_debounce(void)
{
  volatile int *piVar1 = (volatile int *)((unsigned long)&g_box_last_seen_uptime) /*=0x20007a10*/;
  int iVar2 = is_box_field_timer_expired();
  unsigned int uVar3;
  if (iVar2 == 0) {
    iVar2 = thunk_FUN_00074f68();
    if (iVar2 - *piVar1 < 0) {
      thunk_FUN_00074f68();
    }
    uVar3 = 0;
  } else {
    iVar2 = thunk_FUN_00074f68();
    *piVar1 = iVar2;
    uVar3 = 1;
  }
  return uVar3;
}
