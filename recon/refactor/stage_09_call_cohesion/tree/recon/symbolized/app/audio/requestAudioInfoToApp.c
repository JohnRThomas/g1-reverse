#include "g1_app_symbols.h"
#include <zephyr/sys_clock.h>
#include "../../../headers/g1_log.h"
#include "../../../headers/g1_dedupe.h"
/* readable reconstruction; identity: FUN_00048840 @ 0x00048840
 * public-name: requestAudioInfoToApp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef4d9                             @ 0x000ef4d9   [INLINED -- G6 literal batch]
 *   rodata_ef707                             @ 0x000ef707   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed requestAudioInfoToApp @ 0x48840  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_put(struct k_msgq *, const void *, k_timeout_t);
extern void memset_bytes(void*, int, int);

int requestAudioInfoToApp(unsigned char param_1)
{
  int iVar1;
  int uVar2;
  unsigned char buf[24];

  memset_bytes(&buf[1], 0, 0x17);
  buf[0] = 3;
  *(unsigned short*)&buf[2] = 1;
  buf[4] = param_1;
  iVar1 = k_msgq_put((void*)((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, buf, (k_timeout_t){ .ticks = 0LL });
  if (iVar1 == 0) {
    uVar2 = 0;
    if (*(int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
      G1_LOG_ROUTE(*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0, ((unsigned long)"%s(): requestAudioInfoToApp ...\n") /*=0xef4d9*/, ((unsigned long)"requestAudioInfoToApp") /*=0xef707*/);
    }
  } else {
    log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"requestAudioInfoToApp") /*=0xef707*/);
    uVar2 = -1;
  }
  return uVar2;
}
