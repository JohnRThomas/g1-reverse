/* readable reconstruction; identity: FUN_0002c714 @ 0x0002c714
 * public-name: process_for_message_show
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   update_temp_task_status                  <= FUN_0002bffc @ 0x0002bffc
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   get_message_type_param                   <= FUN_0002c30c @ 0x0002c30c
 *   process_for_message_show                 <= FUN_0002c714 @ 0x0002c714
 *   message_pool_read_byte_0xd               <= FUN_00033c04 @ 0x00033c04
 *   get_message_pending_state                <= FUN_00034410 @ 0x00034410
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 * address symbols (name @ address):
 *   rodata_a28ee                             @ 0x000a28ee   [INLINED -- G6 literal batch]
 *   rodata_a291d                             @ 0x000a291d
 *   rodata_a294a                             @ 0x000a294a
 *   rodata_a2977                             @ 0x000a2977   [INLINED -- G6 literal batch]
 *   rodata_a29be                             @ 0x000a29be   [INLINED -- G6 literal batch]
 *   rodata_a3311                             @ 0x000a3311
 *   rodata_a39d6                             @ 0x000a39d6   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002c714 @ 0x2c714  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
typedef unsigned char byte; typedef unsigned char undefined1; typedef uint32_t undefined4; typedef unsigned int uint;
extern int get_device_info(void);
extern unsigned int update_temp_task_status(int, unsigned int, unsigned int);
extern int update_persist_task_status_to_idle(int);
extern unsigned int get_message_type_param(int, unsigned int);
extern unsigned char message_pool_read_byte_0xd(int);
extern unsigned long get_message_pending_state(void);
extern void set_message_pending_state(int);
extern int is_msg_expiration(void);
extern int sync_to_slave(void*,...);
extern void wait_for_event(unsigned long, unsigned long);

static inline __attribute__((always_inline)) uint32_t load_u32_le(const void *address)
{
  const uint8_t *p = (const uint8_t *)address;
  return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
         ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

undefined4 process_for_message_show(char *param_1,int param_2,byte *param_3,undefined4 *param_4)
{
  byte bVar1; volatile int *piVar2; undefined1 uVar3; int iVar4=0; char *pcVar5;
  undefined4 uVar6; byte bVar7; short sVar8; uint uVar9; int bVar10;
  int state_raw;
  sVar8 = 1000;
  do {
    iVar4 = get_device_info();
    if (*(char *)(iVar4 + 0xdd) == '\0') break;
    iVar4 = get_device_info();
    iVar4 = message_pool_read_byte_0xd(*(byte *)(iVar4 + 0xdd) - 1);
    if (iVar4 == 4) break;
    sVar8 = sVar8 + -1;
    wait_for_event(0x21,0);
  } while (sVar8 != 0);
  uVar9 = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  set_message_pending_state(4);
  state_raw = get_message_type_param(param_1[0xfea],0xf);
  uVar3 = (undefined1)state_raw;
  piVar2 = (volatile int*)0x2000230c;
  *(undefined1 *)(param_2 + 7) = uVar3;
  do {
    while( 1 ) {
      if (param_1[0x108f] == '\0') { bVar10 = *param_3 == 1; }
      else { iVar4 = is_msg_expiration(); bVar10 = iVar4 == 2; }
      if (((bVar10) || (*(char *)(param_2 + 7) == '\0')) && (param_1[0xfea] == '\n')) break;
      if (((param_1[1] == '\x01') || (iVar4 = get_device_info(), *(char *)(iVar4 + 1) == '\b')) ||
         (iVar4 = get_device_info(), *(char *)(iVar4 + 0xfea) == '\f')) {
        if (2 < *(volatile int*)0x2000230c) {
          if (*(volatile int*)0x20007554 == 0) {
            log_message(0xa294a,((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1));
          } else { debug_print(0xa294a,((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1)); }
        }
        update_persist_task_status_to_idle(param_1);
        *param_4 = 0xa3311;
        set_message_pending_state(5);
        return 10;
      }
      if (*(char *)(param_2 + 1) != '\x04') {
        if (2 < *(volatile int*)0x2000230c) {
          if (*(volatile int*)0x20007554 == 0) {
            log_message(((unsigned long)"%s(): #3 %d: screen_id is changed, I will go to next screen, goodbye!\n"),((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1));
          } else { debug_print(((unsigned long)"%s(): #3 %d: screen_id is changed, I will go to next screen, goodbye!\n"),((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1)); }
        }
        if (*(char *)(param_2 + 1) != '\0') { return 0xb; }
        goto LAB_0002c884;
      }
      uVar9 = uVar9 + 1;
      if (((uVar9 & 0xf) == 0) && (2 < *piVar2)) {
        if (*(volatile int*)0x20007554 == 0) {
          log_message(((unsigned long)"%s(): [message]\347\255\211\345\276\205\351\200\200\345\207\272:%d, expect_ts: %d, imu:%d, unread_msg_num:%d, persist_task:%d/%d - %d\n"),((unsigned long)"process_for_message_show"),uVar9,
                      load_u32_le((const void *)(uintptr_t)load_u32_le(param_1 + 0xff0)),
                      (uint)*param_3,(uint)*(byte *)(param_2 + 9),(uint)*(byte *)(param_2 + 0xf),
                      load_u32_le((const void *)(uintptr_t)(param_2 + 0xb)),
                      (uint)*(byte *)(param_2 + 8));
        } else {
          debug_print(((unsigned long)"%s(): [message]\347\255\211\345\276\205\351\200\200\345\207\272:%d, expect_ts: %d, imu:%d, unread_msg_num:%d, persist_task:%d/%d - %d\n"),((unsigned long)"process_for_message_show"),uVar9,
                      load_u32_le((const void *)(uintptr_t)load_u32_le(param_1 + 0xff0)),
                      (uint)*param_3,(uint)*(byte *)(param_2 + 9),(uint)*(byte *)(param_2 + 0xf),
                      load_u32_le((const void *)(uintptr_t)(param_2 + 0xb)),
                      (uint)*(byte *)(param_2 + 8));
        }
      }
      if (((param_1[0x108f] != '\0') && (*param_1 == '\x01')) &&
         (((uVar9 * 0xcccccccdU >> 2 | uVar9 * 0x40000000) ) <= 0x0ccccccc)) {
        bVar1 = *(byte *)(param_2 + 7);
        bVar7 = bVar1;
        if (bVar1 < 0x14) { bVar7 = bVar1 - 1; }
        if (bVar1 < 0x14) { *(byte *)(param_2 + 7) = bVar7; }
      }
LAB_0002c894:
      wait_for_event(0x667,0);
    }
    if ((*(char *)(param_2 + 1) == '\x06') ||
       ((*(char *)(param_2 + 1) != '\x06' && (*param_3 == 2)))) {
      iVar4 = get_device_info();
      if ((*(char *)(iVar4 + 0x108f) != '\0') &&
         (pcVar5 = (char *)get_device_info(), *pcVar5 == '\x01')) {
        iVar4 = get_device_info();
        uVar9 = *(uint *)(iVar4 + 0x1060);
        *(uint *)(iVar4 + 0x1060) = uVar9 - 1000;
        *(uint *)(iVar4 + 0x1064) = *(int *)(iVar4 + 0x1064) + -1 + (uint)(999 < uVar9);
      }
      sync_to_slave(param_1,0xc,0,0);
      uVar6 = get_device_info();
      update_temp_task_status(uVar6,6,2);
      if (2 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) {
          log_message(((unsigned long)"%s(): #0 %d: I will go to dashboard, goodbye!\n"),((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1));
        } else { debug_print(((unsigned long)"%s(): #0 %d: I will go to dashboard, goodbye!\n"),((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1)); }
      }
      return 0xb;
    }
    sync_to_slave(param_1,8,0,0);
    if (*param_1 == '\x01') { update_persist_task_status_to_idle(param_1); }
    else if (*(char *)(param_2 + 1) == '\x04') goto LAB_0002c894;
    set_message_pending_state(5);
    if (*param_1 == '\x01') { wait_for_event(0x4000,0); }
    iVar4 = get_message_pending_state();
  } while (iVar4 == 4);
  if (2 < *(volatile int*)0x2000230c) {
    if (*(volatile int*)0x20007554 == 0) {
      log_message(0xa291d,((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1));
    } else { debug_print(0xa291d,((unsigned long)"process_for_message_show"),(uint)*(byte *)(param_2 + 1)); }
  }
LAB_0002c884:
  *param_4 = 0xa3311;
  return 10;
}
