#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00048ad4 @ 0x00048ad4
 * public-name: SlaveDoubleClickEventInject
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef644                             @ 0x000ef644   [INLINED -- G6 literal batch]
 *   rodata_ef694                             @ 0x000ef694   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed SlaveDoubleClickEventInject @ 0x48ad4 */
#include <stdint.h>

extern void *memset_bytes(void *, int, uint32_t);
extern int k_msgq_put(uint32_t, const void *, uint32_t, uint32_t);
extern void log_message(uint32_t, uint32_t);
extern void debug_print(uint32_t, uint32_t);

int SlaveDoubleClickEventInject(void)
{
  uint8_t event[24];
  memset_bytes(event + 1, 0, 23);
  event[0] = 7;

  if (k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, event, 0, 0) != 0) {
    log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"SlaveDoubleClickEventInject") /*=0xef694*/);
    return -1;
  }
  if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
    if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      log_message(((unsigned long)"%s(): received slave send double click event ,boot or close dashboard function\n") /*=0xef644*/, ((unsigned long)"SlaveDoubleClickEventInject") /*=0xef694*/);
    } else {
      debug_print(((unsigned long)"%s(): received slave send double click event ,boot or close dashboard function\n") /*=0xef644*/, ((unsigned long)"SlaveDoubleClickEventInject") /*=0xef694*/);
    }
  }
  return 0;
}
