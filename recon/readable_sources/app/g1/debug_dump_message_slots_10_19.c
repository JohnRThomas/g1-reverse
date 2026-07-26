#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033b4c @ 0x00033b4c
 * public-name: debug_dump_message_slots_10_19
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   debug_dump_message_slots_10_19           <= FUN_00033b4c @ 0x00033b4c
 * address symbols (name @ address):
 *   rodata_a7d55                             @ 0x000a7d55   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_table_mirror                   @ 0x20008eb4
 */
/* Reconstructed FUN_00033b4c @ 0x33b4c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"

void debug_dump_message_slots_10_19(void)
{
  uint32_t format_string = ((unsigned long)"PUSH: g_arrMsgContent[%d].uidTail is %d push %d \n") /*=0xa7d55*/;
  volatile int32_t *piVar1 = (volatile int32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int32_t iVar2 = 10;
  volatile uint32_t *puVar3 = (volatile uint32_t*)((unsigned long)g_message_table_mirror) /*=0x20008eb4*/;
  do {
    if (*piVar1 == 0) {
      log_message(format_string, (uint32_t)iVar2, puVar3[2], puVar3[0]);
    } else {
      debug_print(format_string, (uint32_t)iVar2, puVar3[2], puVar3[0]);
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x6d;
  } while (iVar2 != 0x14);
}
