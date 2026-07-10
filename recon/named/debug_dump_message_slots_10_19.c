/* named: debug_dump_message_slots_10_19 */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x20008eb4  g_message_table_mirror       
*/
/* Reconstructed debug_dump_message_slots_10_19 @ 0x33b4c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t,uint32_t,uint32_t,uint32_t);
extern void debug_print(uint32_t,uint32_t);

void debug_dump_message_slots_10_19(void)
{
  uint32_t format_string = 0xa7d55UL;
  volatile int32_t *piVar1 = (volatile int32_t*)0x20007554UL;
  int32_t iVar2 = 10;
  volatile uint32_t *puVar3 = (volatile uint32_t*)0x20008eb4UL;
  do {
    if (*piVar1 == 0) {
      DEBUG_PRINT(format_string, (uint32_t)iVar2, puVar3[2], puVar3[0]);
    } else {
      debug_print(format_string, (uint32_t)iVar2);
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x6d;
  } while (iVar2 != 0x14);
}

