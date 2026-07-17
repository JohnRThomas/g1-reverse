#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023c88 @ 0x00023c88
 * public-name: cleanDashBoardStartUpModeInfo
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9e903                             @ 0x0009e903
 *   rodata_9e968                             @ 0x0009e968
 *   rodata_9ed4a                             @ 0x0009ed4a
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed cleanDashBoardStartUpModeInfo @ 0x23c88 */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t, uint32_t);
extern void debug_print(uint32_t, uint32_t);
extern int k_msgq_put(uint32_t, const void *, uint32_t, uint32_t);
extern void k_sem_give(uint32_t);

struct startup_request {
  uint8_t opcode;
  uint8_t reserved[5];
};

int cleanDashBoardStartUpModeInfo(void)
{
  const struct startup_request request = { .opcode = 4 };
  if (k_msgq_put(((unsigned long)&g_flash_store_cmd_msgq) /*=0x20003994*/, &request, 0, 0) != 0) {
    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
      if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT(((unsigned long)&rodata_9e903) /*=0x9e903*/, ((unsigned long)&rodata_9ed4a) /*=0x9ed4a*/);
      } else {
        debug_print(((unsigned long)&rodata_9e903) /*=0x9e903*/, ((unsigned long)&rodata_9ed4a) /*=0x9ed4a*/);
      }
    }
    return -1;
  }

  if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
    if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT(((unsigned long)&rodata_9e968) /*=0x9e968*/, ((unsigned long)&rodata_9ed4a) /*=0x9ed4a*/);
    } else {
      debug_print(((unsigned long)&rodata_9e968) /*=0x9e968*/, ((unsigned long)&rodata_9ed4a) /*=0x9ed4a*/);
    }
  }
  k_sem_give(((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
  return 0;
}
