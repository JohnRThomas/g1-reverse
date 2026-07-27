#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_1c4        => struct g1_layout_ancs_notify_frame__stack_0841          [stack_0841; G1-original]
 *   local_1b4        => struct g1_layout_ancs_notify_buf__stack_0842            [stack_0842; G1-original]
 * Raw function identity: 0x0001965c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0001965c @ 0x0001965c
 * public-name: ancs_notification_forward
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dequeue_ancs                             <= FUN_00018d94 @ 0x00018d94
 *   ancs_notification_forward                <= FUN_0001965c @ 0x0001965c
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ble_process_req_dispatch                 <= FUN_00021460 @ 0x00021460
 *   send_data_in_ble_chunks                  <= FUN_0003384c @ 0x0003384c
 *   is_on_whitelist_by_identifier            <= FUN_00034bd4 @ 0x00034bd4
 *   log_notification_fields_debug            <= FUN_0004a3d0 @ 0x0004a3d0
 *   format_log_timestamp_mmdd_hhmm           <= FUN_0007ca80 @ 0x0007ca80
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_9ad7c                             @ 0x0009ad7c   [INLINED -- G6 literal batch]
 *   rodata_9ad86                             @ 0x0009ad86   [INLINED -- G6 literal batch]
 *   rodata_9adaa                             @ 0x0009adaa
 *   g_ancs_notif_evt_id_latest               @ 0x20006aac
 *   g_20006ab2                               @ 0x20006ab2
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0001965c @ 0x1965c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int dequeue_ancs(void*);
extern unsigned int ble_process_req_dispatch(unsigned char*, unsigned char*, unsigned char*);
extern void send_data_in_ble_chunks(const unsigned char *);
extern int is_on_whitelist_by_identifier(int);
extern void log_notification_fields_debug(uint32_t, void*);
extern int format_log_timestamp_mmdd_hhmm(unsigned char *);
extern int get_timestamp(void);
extern void memset_bytes(void*, int, int);
extern void strncpy_zero_pad(void*, uint32_t, int);

struct ancs_record {
  uint32_t uid[2];
  uint32_t device_state;
  uint32_t reserved;
  char text[384];
  uint8_t work[32];
  uint32_t status;
};

struct command_record {
  uint32_t opcode;
  struct ancs_record notification;
};

_Static_assert(sizeof(struct ancs_record) == 0x1b4, "ANCS record layout");
_Static_assert(sizeof(struct command_record) == 0x1b8, "command record layout");

void ancs_notification_forward(uint32_t channel)
{
  struct command_record local;
  int kind;
  uint8_t mode;

  local.opcode = 0x4b;
  memset_bytes(&local.notification, 0, sizeof(local.notification));
  if (dequeue_ancs(&local.notification) != 0 ||
      (local.notification.status <= 1 && local.notification.text[0] == 0)) {
    return;
  }

  local.notification.uid[0] = (uint32_t)get_timestamp();
  if (local.notification.uid[0] == 0) {
    local.notification.uid[0] = 1;
  }
  local.notification.device_state = *(volatile uint32_t*)((unsigned long)&g_ancs_notif_evt_id_latest) /*=0x20006aac*/;
  log_notification_fields_debug(((unsigned long)"FROM:ancs") /*=0x9ad7c*/, &local.notification);

  if (local.notification.status < 2) {
    kind = is_on_whitelist_by_identifier(local.notification.text);
    if (kind != 2) {
      if (kind == 3) {
        mode = 4;
      } else {
        if (kind != 1) {
          return;
        }
        if (*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
          log_message(((unsigned long)"blocked! app(%s) not in whitelist \n") /*=0x9ad86*/, local.notification.text);
        } else {
          debug_print(((unsigned long)"blocked! app(%s) not in whitelist \n") /*=0x9ad86*/, local.notification.text);
        }
        send_data_in_ble_chunks(&local.notification);
        return;
      }
    } else {
      mode = 2;
    }
  } else {
    mode = 2;
  }

  ((uint8_t*)&local.opcode)[1] = mode;
  if (*(volatile uint8_t*)((unsigned long)&g_20006ab2) /*=0x20006ab2*/ == 2) {
    strncpy_zero_pad(local.notification.text, ((unsigned long)&rodata_9adaa) /*=0x9adaa*/, 0x20);
  }
  format_log_timestamp_mmdd_hhmm(local.notification.work);
  ble_process_req_dispatch(channel, &local.opcode, &local.notification);
}
