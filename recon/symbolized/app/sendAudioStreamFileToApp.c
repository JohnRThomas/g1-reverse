#include "g1_app_symbols.h"
#include <zephyr/sys_clock.h>
/* readable reconstruction; identity: FUN_00047bf8 @ 0x00047bf8
 * public-name: sendAudioStreamFileToApp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sendAudioStreamFileToApp                 <= FUN_00047bf8 @ 0x00047bf8
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef71d                             @ 0x000ef71d   [INLINED -- G6 literal batch]
 *   g_dashboard_response_msgq                @ 0x2000392c
 */
/* Reconstructed FUN_00047bf8 @ 0x47bf8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../headers/g1_log.h"

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(struct k_msgq *, const void *, k_timeout_t);

int sendAudioStreamFileToApp(unsigned char param_1, unsigned char param_2)
{
  unsigned char message[24];
  memset_bytes(message + 1, 0, 23);
  message[0] = 2;
  message[2] = 2;
  message[3] = 0;
  message[4] = param_1;
  message[5] = param_2;

  int iVar1 = k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, message, (k_timeout_t){ .ticks = 0LL });
  if (iVar1 != 0) {
    log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"sendAudioStreamFileToApp") /*=0xef71d*/);
    iVar1 = -1;
  }
  return iVar1;
}
