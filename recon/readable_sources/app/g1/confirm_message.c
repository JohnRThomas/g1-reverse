#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x000347a0       => struct g1_layout_confirm_message_state__global_0972     [global_0972; G1-original]
 * Raw function identity: 0x00034524.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00034524 @ 0x00034524
 * public-name: confirm_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   msg_queue_debug_dump                     <= FUN_00033b0c @ 0x00033b0c
 *   debug_dump_message_slots_10_19           <= FUN_00033b4c @ 0x00033b4c
 *   get_active_message_count                 <= FUN_00033cb0 @ 0x00033cb0
 *   msg_content_used_count                   <= FUN_00033cdc @ 0x00033cdc
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   message_table_contains_id                <= FUN_00033f24 @ 0x00033f24
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 *   confirm_message                          <= FUN_00034524 @ 0x00034524
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a8174                             @ 0x000a8174   [INLINED -- G6 literal batch]
 *   rodata_a8255                             @ 0x000a8255   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_message_table_mirror                   @ 0x20008eb4
 *   g_msg_queue_busy                         @ 0x20018d8e
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 *   g_message_pending_state                  @ 0x2001a229
 *   g_message_table_slot_count               @ 0x2001a22b
 */
/* Reconstructed FUN_00034524 @ 0x34524  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint;
extern int get_device_info(int,...);
extern int check_pending_messages_flag(int,...); extern int msg_queue_debug_dump(int,...); extern int debug_dump_message_slots_10_19(int,...);
extern int get_active_message_count(int,...); extern int msg_content_used_count(int,...); extern int msg_content_recalc_unread(int,...);
extern int clear_timeout_message(int,...); extern int message_table_contains_id(int,...); extern int is_msg_expiration(int,...);
extern int get_timestamp(int,...); extern int memcpy(int,...); extern int memset_bytes(int,...);

void confirm_message(int param_1)
{
  char cVar1; int bVar2; byte *pbVar3; volatile byte *puVar4; byte uVar5;
  char *pcVar6; int iVar7; uint uVar8; int iVar9; int iVar10; int iVar13; int iVar14;
  uint uVar12; byte bVar15;
  iVar10 = 0x20008dac;
  if ((*(volatile char*)(iVar10 + 0x118) != 0) &&
      (iVar13 = *(volatile int*)(iVar10 + 0x110), iVar13 == param_1) &&
      (*(volatile char*)(iVar10 + 0x115) == 4)) {
    cVar1 = *(volatile char*)(iVar10 + 0x2b8);
    pcVar6 = (char*)get_device_info(0);
    if ((*pcVar6 == 1) && (cVar1 == 0) && (iVar7 = message_table_contains_id(10,iVar13), iVar7 != 0)) {
      if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) log_message(((unsigned long)"%s(): add found same message, uidtail %d\n") /*=0xa8174*/,((unsigned long)"confirm_message") /*=0xa8255*/,iVar13);
        else debug_print(0);
      }
      memset_bytes(((unsigned long)g_message_table_mirror) /*=0x20008eb4*/,0,0x1b4);
      return;
    }
    puVar4 = (volatile byte*)((unsigned long)&g_msg_queue_busy) /*=0x20018d8e*/;
    *puVar4 = 1;
    iVar13 = get_device_info(0);
    if (*(char*)(iVar13 + 0xd5) != 4) clear_timeout_message(0);
    uVar8 = msg_content_used_count(0);
    iVar13 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
    iVar7 = *(volatile int*)(iVar10 + 0x2b8);
    if (iVar7 == 0) {
      if (uVar8 == 10) {
        iVar7 = 0; iVar14 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
        do {
          iVar9 = memcpy(iVar14,iVar14 + 0x1b4,0x1b4);
          *(char*)(iVar9 + 0xc) = (char)iVar7;
          iVar7 = iVar7 + 1; iVar14 = iVar14 + 0x1b4;
        } while (iVar7 != 9);
        uVar8 = 9;
      }
      iVar14 = uVar8 * 0x1b4;
      iVar10 = memcpy(iVar13 + iVar14, iVar10 + 0x108);
      iVar7 = *(int*)(iVar13 + iVar14);
      *(char*)(iVar10 + 0xc) = (char)uVar8;
      if (iVar7 == 0) { *(undefined4*)(iVar13 + iVar14) = get_timestamp(0); }
      iVar10 = uVar8 * 0x1b4 + iVar13;
      *(char*)(iVar10 + 0xe) = 1;
      if (*(int*)(iVar10 + 4) != 0) { *(undefined4*)(iVar10 + 4) = get_timestamp(0); }
    } else if (iVar7 == 2) {
      if (uVar8 != 0) {
        bVar2 = 0; bVar15 = 0; iVar7 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
        do {
          if ((*(int*)(iVar7 + 8) == *(int*)(iVar10 + 0x110)) || bVar2) {
            iVar14 = memcpy(iVar7, iVar7 + 0x1b4, 0x1b4);
            bVar2 = 1; *(byte*)(iVar14 + 0xc) = bVar15;
          }
          bVar15 = bVar15 + 1; iVar7 = iVar7 + 0x1b4;
        } while (bVar15 < uVar8);
        if (bVar2) memset_bytes((uVar8 - 1) * 0x1b4 + iVar13, 0);
      }
    } else if ((iVar7 == 1) && (uVar8 != 0)) {
      uVar12 = 0; iVar7 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
      do {
        if (*(int*)(iVar7 + 8) == *(int*)(iVar10 + 0x110)) {
          memcpy(uVar12 * 0x1b4 + ((unsigned long)g_message_pool) /*=0x20007dac*/, iVar10 + 0x108); break;
        }
        uVar12 = uVar12 + 1; iVar7 = iVar7 + 0x1b4;
      } while ((uVar12 & 0xff) < uVar8);
    }
    memset_bytes(((unsigned long)g_message_table_mirror) /*=0x20008eb4*/, 0, 0x1b4);
    pbVar3 = (byte*)((unsigned long)&g_message_table_slot_count) /*=0x2001a22b*/;
    uVar8 = 10;
    while (1) {
      bVar15 = *pbVar3;
      if (bVar15 <= uVar8) break;
      if (*(char*)(uVar8 * 0x1b4 + iVar13 + 0x1c4) == 0) goto control_label_34640;
      iVar10 = memcpy(iVar13 + uVar8 * 0x1b4, uVar8 * 0x1b4 + 0x1b4 + iVar13, 0x1b4);
      *(char*)(iVar10 + 0xc) = (char)uVar8;
      *(char*)(iVar10 + 0xd) = 0;
      uVar8 = uVar8 + 1 & 0xff;
    }
    if (10 < bVar15) { control_label_34640: *pbVar3 = bVar15 - 1; }
    memset_bytes((uint)*pbVar3 * 0x1b4 + iVar13, 0);
    iVar10 = get_device_info(0);
    if (*(char*)(iVar10 + 0xd5) == 4) {
      iVar10 = get_device_info(0);
      uVar5 = msg_content_recalc_unread(0);
      *(char*)(iVar10 + 0xdd) = uVar5;
    } else clear_timeout_message(0);
    if (cVar1 == 0) {
      iVar10 = get_active_message_count(0);
      iVar13 = get_device_info(0);
      if (*(char*)(iVar13 + 0xd5) == 4) {
        if (iVar10 != 0xff) check_pending_messages_flag(0);
      } else {
        iVar10 = get_device_info(0);
        if (((*(char*)(iVar10 + 0xd5) == 0) ||
             ((iVar10 = get_device_info(0), *(char*)(iVar10 + 0x108f) != 0 &&
               (iVar10 = get_device_info(0), *(char*)(iVar10 + 0xd5) == 6)))) &&
            (iVar10 = is_msg_expiration(0), iVar10 != 1)) {
          *(volatile byte*)((unsigned long)&g_message_pending_state) /*=0x2001a229*/ = 1;
        }
      }
    }
    if (*(volatile char*)((unsigned long)&g_esb_notify_slave_role_guard) /*=0x20018d9f*/ == 0) { msg_queue_debug_dump(0); debug_dump_message_slots_10_19(0); }
    *puVar4 = 0;
  }
  return;
}
