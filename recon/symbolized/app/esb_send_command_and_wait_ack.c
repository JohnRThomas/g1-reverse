#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00027448 @ 0x00027448
 * public-name: esb_send_command_and_wait_ack
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   k_msleep_ticks32768_a                    <= FUN_0007cb8e @ 0x0007cb8e
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_esb_seg_tx_frame_opcode                @ 0x20018c6f
 *   g_esb_seg_tx_frame_payload               @ 0x20018c71
 *   g_esb_seg_ack_echo_buf                   @ 0x20018d6b
 *   g_esb_seg_tx_lock_flag                   @ 0x20018d8c
 */
/* Reconstructed FUN_00027448 @ 0x27448  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern int32_t is_battery_critical(void);
extern void k_msleep_ticks32768_a(int32_t);
extern int32_t FUN_00086be4(void *a, void *b, uint32_t n);
extern void memcpy(void *dst, void *src, uint32_t n);
extern void FUN_00086c1e(void *a, void *b, uint32_t c, uint32_t d);
extern void memset_bytes(void *dst, int32_t val, uint32_t n);

typedef void (*fp774_t)(void *, uint32_t);

uint32_t esb_send_command_and_wait_ack(char *param_1, uint32_t param_2, uint32_t *param_3, uint32_t param_4)
{
  volatile uint8_t *pcVar1;
  int32_t iVar2;
  uint32_t uVar3;
  uint32_t *puVar4;
  uint32_t *puVar5;
  uint32_t *puVar6;
  fp774_t pcVar7;
  uint32_t *puVar8;
  uint32_t uVar9;
  uint32_t *puVar10;

  iVar2 = is_battery_critical();
  pcVar1 = (volatile uint8_t *)((unsigned long)&g_esb_seg_tx_lock_flag) /*=0x20018d8c*/;
  uVar9 = 0;
  if (iVar2 != 1) {
    while (*pcVar1 != 0) {
      uVar9 = uVar9 + 1;
      if (uVar9 == 2000) goto LAB_000275de;
      k_msleep_ticks32768_a(1);
    }
    *pcVar1 = 1;
    uVar9 = uVar9 & 0xffff;
    *(char *)(param_1 + 0x6e1) = *(char *)(param_1 + 0x6e1) + '\x01';
    *(uint8_t *)(param_1 + 0x6cc) = ((uint8_t)param_2 & 0x3f) | 0x80;
    puVar10 = (uint32_t *)(param_1 + 0x6cc);
    *(uint8_t *)(param_1 + 0x6cd) = *(uint8_t *)(param_1 + 0xfcf);
    *(uint8_t *)(param_1 + 0x6ce) = *(uint8_t *)(param_1 + 0xfd0);
    *(uint8_t *)(param_1 + 0x6cf) = *(uint8_t *)(param_1 + 0xfd1);
    *(uint32_t *)(param_1 + 0x6d8) = *(uint32_t *)(param_1 + 0xfe0);
    *(uint16_t *)(param_1 + 0x6dc) = *(uint16_t *)(param_1 + 0xfe4);
    *(uint8_t *)(param_1 + 0x6d0) = *(uint8_t *)(param_1 + 0xfc0);
    if (param_2 - 0xbU < 2) {
      puVar6 = (uint32_t *)(((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/ + 1);
      *(volatile uint8_t *)((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/ = 4;
      puVar5 = puVar10;
      do {
        puVar4 = puVar5 + 1;
        puVar8 = puVar6 + 1;
        *(volatile uint32_t *)puVar6 = *puVar5;
        puVar5 = puVar4;
        puVar6 = puVar8;
      } while (puVar4 != (uint32_t *)(param_1 + 0x6e0));
      *(volatile uint16_t *)puVar8 = *(uint16_t *)puVar4;
      FUN_00086c1e((void *)((unsigned long)&g_esb_seg_tx_frame_payload) /*=0x20018c71*/, param_3, param_4, 0xfa);
      uVar3 = 0xdc;
      *(uint8_t *)(param_1 + 0x105a) = 1;
      pcVar7 = *(fp774_t *)(param_1 + 0x774);
    }
    else {
      if ((param_3 != 0) && (param_4 != 0)) {
        if (1 < param_4) {
          param_4 = 2;
        }
        memcpy(param_1 + 0x6df, param_3, param_4);
      }
      puVar5 = (uint32_t *)((unsigned long)&g_esb_seg_ack_echo_buf) /*=0x20018d6b*/;
      if (param_2 == 1) {
        *(volatile uint8_t *)(((unsigned long)&g_esb_seg_ack_echo_buf) /*=0x20018d6b*/ + 0x15) = *(uint8_t *)(param_1 + 0x6e1);
        iVar2 = FUN_00086be4((void *)((unsigned long)&g_esb_seg_ack_echo_buf) /*=0x20018d6b*/, puVar10, 0x16);
        if (iVar2 == 0) goto LAB_000275de;
        puVar6 = (uint32_t *)(((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/ + 1);
        *(volatile uint8_t *)((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/ = 4;
        puVar5 = puVar10;
        do {
          puVar4 = puVar5 + 1;
          puVar8 = puVar6 + 1;
          *(volatile uint32_t *)puVar6 = *puVar5;
          puVar5 = puVar4;
          puVar6 = puVar8;
        } while (puVar4 != (uint32_t *)(param_1 + 0x6e0));
      }
      else {
        puVar6 = (uint32_t *)(((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/ + 1);
        *(volatile uint8_t *)((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/ = 4;
        puVar5 = puVar10;
        do {
          puVar4 = puVar5 + 1;
          puVar8 = puVar6 + 1;
          *(volatile uint32_t *)puVar6 = *puVar5;
          puVar5 = puVar4;
          puVar6 = puVar8;
        } while (puVar4 != (uint32_t *)(param_1 + 0x6e0));
      }
      uVar3 = 0x21;
      *(volatile uint16_t *)puVar8 = *(uint16_t *)puVar4;
      *(uint8_t *)(param_1 + 0x105a) = 1;
      pcVar7 = *(fp774_t *)(param_1 + 0x774);
    }
    (*pcVar7)((void *)((unsigned long)&g_esb_seg_tx_frame_opcode) /*=0x20018c6f*/, uVar3);
    while (*(uint8_t *)(param_1 + 0x105a) != 2) {
      uVar9 = (uVar9 + 1) & 0xffff;
      if (uVar9 == 2000) {
        if (param_2 == 1) {
          memset_bytes((void *)((unsigned long)&g_esb_seg_ack_echo_buf) /*=0x20018d6b*/, 0, 0x16);
        }
        goto LAB_000275de;
      }
      k_msleep_ticks32768_a(1);
    }
    if (param_2 == 1) {
      puVar5 = (uint32_t *)((unsigned long)&g_esb_seg_ack_echo_buf) /*=0x20018d6b*/;
      do {
        puVar4 = puVar10 + 1;
        puVar6 = puVar5 + 1;
        *(volatile uint32_t *)puVar5 = *puVar10;
        puVar5 = puVar6;
        puVar10 = puVar4;
      } while (puVar4 != (uint32_t *)(param_1 + 0x6e0));
      *(volatile uint16_t *)puVar6 = *(uint16_t *)puVar4;
    }
  }
LAB_000275de:
  *pcVar1 = 0;
  return uVar9;
}
