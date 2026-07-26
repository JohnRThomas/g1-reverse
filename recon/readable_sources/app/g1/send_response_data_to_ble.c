#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00047ba8 @ 0x00047ba8
 * public-name: send_response_data_to_ble
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef736                             @ 0x000ef736   [INLINED -- G6 literal batch]
 *   g_dashboard_response_msgq                @ 0x2000392c
 */
/* Reconstructed FUN_00047ba8 @ 0x47ba8  (parity: 300/300 trials, PROVEN) */

extern char* get_device_info(void);
extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);

unsigned int send_response_data_to_ble(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int local_20 = param_1;
  unsigned int uStack_1c = param_2;
  unsigned int uStack_18 = param_3;
  unsigned int uStack_14 = param_4;
  (void)uStack_1c; (void)uStack_18; (void)uStack_14;
  char *pcVar1 = get_device_info();
  if (*pcVar1 != 2) {
    memset_bytes((char*)&local_20 + 1, 0, 0x17);
    local_20 = (local_20 & 0xffffff00) | 1;
    int iVar2 = k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, &local_20, 0, 0);
    if (iVar2 != 0) {
      log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"send_response_data_to_ble") /*=0xef736*/);
      return 0xffffffff;
    }
  }
  return 0;
}
