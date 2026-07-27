struct k_sem;
/* readable reconstruction; identity: FUN_00023c88 @ 0x00023c88
 * public-name: cleanDashBoardStartUpModeInfo
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9e903                             @ 0x0009e903   [INLINED -- G6 literal batch]
 *   rodata_9e968                             @ 0x0009e968   [INLINED -- G6 literal batch]
 *   rodata_9ed4a                             @ 0x0009ed4a   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed cleanDashBoardStartUpModeInfo @ 0x23c88 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(struct k_sem *);

struct startup_request {
  uint8_t opcode;
  uint8_t reserved[5];
};

int cleanDashBoardStartUpModeInfo(void)
{
  const struct startup_request request = { .opcode = 4 };
  if (k_msgq_put(0x20003994, &request, 0, 0) != 0) {
    if (*(volatile int32_t *)0x2000230c > 0) {
      if (*(volatile uint32_t *)0x20007554 == 0) {
        log_message(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n"), ((unsigned long)"cleanDashBoardStartUpModeInfo"));
      } else {
        debug_print(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n"), ((unsigned long)"cleanDashBoardStartUpModeInfo"));
      }
    }
    return -1;
  }

  if (*(volatile int32_t *)0x2000230c > 2) {
    if (*(volatile uint32_t *)0x20007554 == 0) {
      log_message(((unsigned long)"%s(): SEND APP Language Command...\n"), ((unsigned long)"cleanDashBoardStartUpModeInfo"));
    } else {
      debug_print(((unsigned long)"%s(): SEND APP Language Command...\n"), ((unsigned long)"cleanDashBoardStartUpModeInfo"));
    }
  }
  k_sem_give(0x200079e4);
  return 0;
}
