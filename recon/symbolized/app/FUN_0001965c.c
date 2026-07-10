#include "g1_app_symbols.h"
/* named: FUN_0001965c */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed FUN_0001965c @ 0x1965c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, void*);
extern int dequeue_ancs(void*);
extern void debug_print(void);
extern void ble_process_req_dispatch(uint32_t, void*, void*);
extern void send_data_in_ble_chunks(void*);
extern int is_on_whitelist_by_identifier(void*);
extern void log_notification_fields_debug(uint32_t, void*);
extern int format_log_timestamp_mmdd_hhmm(void*);
extern int get_timestamp(void);
extern void memset_bytes(void*, int, int);
extern void strncpy_zero_pad(void*, uint32_t, int);

void FUN_0001965c(uint32_t param_1){
  uint32_t *puVar1;
  int iVar2;
  uint8_t uVar3;
  uint32_t local_1c8;
  int local_1c4[2];
  uint32_t local_1bc;
  char local_1b4[384];
  uint8_t auStack_34[32];
  volatile uint32_t local_14;
  local_1c8 = 0x4b;
  memset_bytes(local_1c4, 0, 0x1b4);
  iVar2 = dequeue_ancs(local_1c4);
  if (iVar2 == 0 && (1 < local_14 || local_1b4[0] != 0)){
    local_1c4[0] = get_timestamp();
    puVar1 = (uint32_t*)((uintptr_t)&g_ancs_notif_evt_id_latest) /*=0x20006aac*/;
    if (local_1c4[0] == 0) local_1c4[0] = 1;
    local_1bc = *(volatile uint32_t*)((uintptr_t)&g_ancs_notif_evt_id_latest) /*=0x20006aac*/;
    log_notification_fields_debug("FROM:ancs" /*=0x9ad7c*/, local_1c4);
    if (local_14 < 2 && (iVar2 = is_on_whitelist_by_identifier(local_1b4), iVar2 != 2)){
      if (iVar2 != 3){
        if (iVar2 != 1) return;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
          DEBUG_PRINT("blocked! app(%s) not in whitelist \n" /*=0x9ad86*/, local_1b4);
        } else {
          debug_print();
        }
        send_data_in_ble_chunks(local_1c4);
        return;
      }
      uVar3 = 4;
    } else {
      uVar3 = 2;
    }
    *((uint8_t*)&local_1c8 + 1) = uVar3;
    if (*((char*)puVar1 + 6) == 2){
      strncpy_zero_pad(local_1b4, "com.apple.mobilephone_missed" /*=0x9adaa*/, 0x20);
    }
    format_log_timestamp_mmdd_hhmm(auStack_34);
    ble_process_req_dispatch(param_1, &local_1c8, local_1c4);
  }
}

