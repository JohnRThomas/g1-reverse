#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003b800 @ 0x0003b800
 * public-name: consume_pending_event_and_refresh_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   stopAudioStreamRecord                    <= FUN_0002f80c @ 0x0002f80c
 *   consume_pending_event_and_refresh_flag   <= FUN_0003b800 @ 0x0003b800
 * address symbols (name @ address):
 *   g_pending_event_word                     @ 0x20007b78
 */
/* Reconstructed FUN_0003b800 @ 0x3b800  (parity: 300/300 trials, PROVEN) */

extern void stopAudioStreamRecord(unsigned int, unsigned int);
extern void mark_master_or_low_battery_flag(void);

void consume_pending_event_and_refresh_flag(void)
{
  unsigned int uVar1;

  uVar1 = __atomic_exchange_n((unsigned int*)((unsigned long)&g_pending_event_word) /*=0x20007b78*/, 0,
                              __ATOMIC_SEQ_CST);
  stopAudioStreamRecord(0,uVar1);
  mark_master_or_low_battery_flag();
  return;
}
