#include "g1_net_symbols.h"
/* net-core controller_radio_transition_apply @ 0x1020d1c
 * Missing first-class radio state-transition routine recovered from the case-4
 * tail target formerly absorbed into FUN_01013650. Physical ownership extends
 * through 0x1021107 and includes embedded literal islands. All state/MMIO
 * accesses remain volatile so repeated reset writes and their order match the
 * hardware transaction stream. Raw backmap: FUN_01020d1c@0x01020d1c.
 * Authoritative CFG parity: PASS. */
#include <stdint.h>
typedef uint8_t undefined1,byte; typedef uint16_t undefined2,ushort; typedef uint32_t undefined4,uint;
extern uint32_t controller_radio_timer_capture_get(void); /* FUN_01023de8@0x01023de8 */
extern int controller_mode1_state_validate(void);         /* FUN_010218d8@0x010218d8 */
extern int controller_mode2_state_validate(void);         /* FUN_010218e4@0x010218e4 */
extern int controller_transition_pending_check(void);     /* FUN_01025cf0@0x01025cf0 */
extern int controller_radio_time_mode1_to_mode1(uint16_t,uint8_t); /* FUN_01021614@0x01021614 */
extern int controller_radio_time_mode2_to_mode1(uint16_t,uint8_t); /* FUN_010215d8@0x010215d8 */
extern int controller_radio_time_mode1_to_mode2(uint16_t,uint8_t); /* FUN_010215f4@0x010215f4 */
extern int controller_radio_time_mode2_to_mode2(uint16_t,uint8_t); /* FUN_01021634@0x01021634 */
extern int controller_radio_transition_schedule(int,uint32_t,uint8_t); /* FUN_01020a6c@0x01020a6c */
extern void sdc_assertion_fail(uint32_t,uint32_t);         /* FUN_01008d00@0x01008d00 */
extern void sdc_llcp_note_unsupported_pdu(void);           /* FUN_01020500@0x01020500 */
extern int controller_radio_work_pending(void);            /* FUN_01025be0@0x01025be0 */
#define NRF_TIMER0_NS_BASE 0x4100c000u
#define g_nrf802154_core_state 0x210015f0u
#define NRF_RADIO_NS_BASE REG_41008000 /*=0x41008000*/
#define RADIO_INTEN_PRESERVE_MASK 0xfffffee2u
#define RADIO_TIMER_COMPARE_TICKS 0x00023280u
#define TIMER_TRANSITION_SHORTS 0x8000000bu
#define NVIC_ISER_BASE 0xe000e100u
void controller_radio_transition_apply(uint32_t entry_r0, uint32_t entry_r1) {
 char cVar1,cVar6; byte bVar16; int iVar9=g_nrf802154_core_state,iVar11=NRF_TIMER0_NS_BASE,iVar12,iVar15,iVar22; uint uVar10,uVar20,uVar21,local_24;
    *(volatile undefined4 *)(NRF_TIMER0_NS_BASE + 0x4c) = 1;
    iVar22 = *(volatile int *)(iVar11 + 0x54c);
    (void)entry_r0; (void)entry_r1;
    uVar10 = controller_radio_timer_capture_get();
    *(volatile undefined4 *)(iVar9 + 0x38) = uVar10;
    *(volatile undefined4 *)(iVar9 + 0x3c) = 0;
    *(volatile int *)(iVar9 + 0x40) = iVar22;
    if (0x95 < *(volatile ushort *)(iVar9 + 0x1c)) {
      if (*(volatile char *)(iVar9 + 9) == '\x01') {
        iVar15 = controller_mode1_state_validate();
        if (1 < iVar15 + 1U) {
                    /* WARNING: Subroutine does not return */
          sdc_assertion_fail(0x3e,0x851);
        }
      }
      else if ((*(volatile char *)(iVar9 + 9) == '\x02') && (iVar15 = controller_mode2_state_validate(), 1 < iVar15 + 1U)) {
                    /* WARNING: Subroutine does not return */
        sdc_assertion_fail(0x3e,0x857);
      }
    }
    uVar21 = RADIO_INTEN_PRESERVE_MASK;
    iVar15 = NRF_RADIO_NS_BASE;
    *(volatile undefined4 *)(NRF_RADIO_NS_BASE + 0x80) = 0;
    *(volatile undefined4 *)(iVar15 + 0x84) = 0;
    *(volatile undefined4 *)(iVar15 + 0x88) = 0;
    *(volatile undefined4 *)(iVar15 + 0x80) = 0;
    *(volatile undefined4 *)(iVar15 + 0x84) = 0;
    *(volatile undefined1 *)(iVar9 + 0x35) = 0;
    cVar6 = *(volatile char *)(iVar9 + 0xc);
    *(volatile uint *)(iVar15 + 0x200) = uVar21 & *(volatile uint *)(iVar15 + 0x200);
    iVar11 = NRF_RADIO_NS_BASE;
    if (cVar6 == '\0') {
      cVar6 = *(volatile char *)(iVar9 + 9);
      iVar15 = 0;
      if (cVar6 == '\x01') goto LAB_01020e60;
LAB_01020d82:
      if (cVar6 != '\x02') {
        uVar21 = 0;
        goto LAB_01020d88;
      }
      if (*(volatile int *)(NRF_RADIO_NS_BASE + 0x10c) == 0) {
        uVar20 = 0;
        uVar21 = 4;
      }
      else {
        uVar21 = 6;
        uVar20 = 2;
      }
      if ((*(volatile uint *)(NRF_RADIO_NS_BASE + 0x400) & 1) != 0) {
        uVar21 = uVar20;
      }
      if (iVar15 != 0) {
        uVar20 = uVar21 & 0xb | 1;
        uVar21 = uVar21 | 1;
      }
      if (uVar20 == 0) goto LAB_01020d88;
    }
    else {
      iVar15 = *(volatile int *)(iVar15 + 0x4144);
      cVar6 = *(volatile char *)(iVar9 + 9);
      if (iVar15 != 0) {
        iVar15 = 1;
      }
      if (cVar6 != '\x01') goto LAB_01020d82;
LAB_01020e60:
      uVar21 = *(volatile uint *)(NRF_RADIO_NS_BASE + 0x10c);
      if (uVar21 == 0) {
LAB_01020d88:
        if (*(volatile int *)(NRF_RADIO_NS_BASE + 0x110) != 0) {
          uVar21 = uVar21 & 0xff | 0x10;
        }
      }
      else {
        uVar21 = 8;
      }
    }
    iVar15 = *(volatile int *)(NRF_RADIO_NS_BASE + 0x104);
    if (iVar15 != 0) {
      iVar15 = 1;
    }
    local_24 = (uint8_t)iVar15;
    *(volatile undefined4 *)(NRF_RADIO_NS_BASE + 0x100) = 0;
    *(volatile undefined4 *)(iVar11 + 0x10c) = 0;
    *(volatile undefined4 *)(iVar11 + 0x110) = 0;
    *(volatile undefined4 *)(iVar11 + 0x104) = 0;
    *(volatile undefined4 *)(iVar11 + 0x114) = 0;
    *(volatile undefined4 *)(iVar11 + 0x118) = 0;
    *(volatile undefined4 *)(iVar11 + 0x108) = 0;
    *(volatile undefined4 *)(iVar11 + 0x16c) = 0;
    iVar11 = controller_transition_pending_check();
    iVar15 = NRF_TIMER0_NS_BASE;
    if (iVar11 != 0) {
      uVar21 = uVar21 & 0xff | 0x10;
    }
    *(volatile undefined4 *)(NRF_TIMER0_NS_BASE + 0x144) = 0;
    if (((uVar21 & 0x18) == 0x10) && (*(volatile char *)(iVar9 + 9) == '\x01')) {
      iVar11 = *(volatile int *)(iVar15 + 0x548);
      uVar10 = *(volatile undefined4 *)(iVar15 + 0x544);
      uVar21 = uVar21 & 0xff | 0x20;
      *(volatile int *)(iVar9 + 0x24) = iVar11;
      *(volatile undefined4 *)(iVar9 + 0x20) = uVar10;
      if (*(volatile char *)(iVar9 + 0x29) != '\x02') goto LAB_01020e02;
LAB_01020ec2:
      cVar6 = *(volatile char *)(iVar9 + 0x18);
      if ((cVar6 == '\x04') || (cVar6 == '\b')) {
        if ((*(volatile uint *)(NRF_RADIO_NS_BASE + 0x414) & 6) == 0) {
          cVar6 = '\b';
        }
        else {
          cVar6 = '\x04';
        }
      }
    }
    else {
      iVar11 = *(volatile int *)(NRF_TIMER0_NS_BASE + 0x548);
      uVar10 = *(volatile undefined4 *)(NRF_TIMER0_NS_BASE + 0x544);
      *(volatile int *)(iVar9 + 0x24) = iVar11;
      *(volatile undefined4 *)(iVar9 + 0x20) = uVar10;
      if ((*(volatile char *)(iVar9 + 0x29) == '\x02') || (*(volatile char *)(iVar9 + 9) == '\x02'))
      goto LAB_01020ec2;
LAB_01020e02:
      cVar6 = *(volatile char *)(iVar9 + 0x18);
    }
    cVar1 = *(volatile char *)(iVar9 + 9);
    bVar16 = *(volatile byte *)(iVar9 + 8);
    uVar20 = (uint)bVar16;
    *(volatile char *)(iVar9 + 0x28) = cVar6;
    *(volatile char *)(iVar9 + 0x29) = cVar1;
    if (uVar20 == 0) {
      *(volatile ushort *)(iVar9 + 7) = (ushort)bVar16;
      *(volatile byte *)(iVar9 + 9) = bVar16;
      *(volatile byte *)(iVar9 + 0xc) = bVar16;
      uVar10 = 0;
    }
    else if ((uVar21 & 0x11) == 0) {
      iVar15 = uVar20 - 1;
      cVar6 = *(volatile char *)(iVar9 + 7);
      *(volatile undefined1 *)(iVar9 + 9) = 0;
      *(volatile undefined2 *)(iVar9 + 7) = 0;
      if (iVar15 != 0) {
        iVar15 = 1;
      }
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        sdc_assertion_fail(0x3e,0x804);
      }
      if (uVar20 == 1) {
        if (cVar1 == '\x01') {
          iVar12 = controller_radio_time_mode1_to_mode1(
              *(volatile undefined2 *)(iVar9 + 0x1c),
              *(volatile byte *)(iVar9 + 0x18));
          uVar20 = iVar12 + *(volatile uint *)(iVar9 + 0x24);
        }
        else {
          iVar12 = controller_radio_time_mode2_to_mode1(
              *(volatile undefined2 *)(iVar9 + 0x1c),
              *(volatile byte *)(iVar9 + 0x18));
          uVar20 = iVar12 + *(volatile uint *)(iVar9 + 0x24);
        }
      }
      else if (cVar1 == '\x01') {
        iVar12 = controller_radio_time_mode1_to_mode2(
            *(volatile undefined2 *)(iVar9 + 0x1c),
            *(volatile byte *)(iVar9 + 0x18));
        uVar20 = iVar12 + *(volatile uint *)(iVar9 + 0x24);
      }
      else {
        iVar12 = controller_radio_time_mode2_to_mode2(
            *(volatile undefined2 *)(iVar9 + 0x1c),
            *(volatile byte *)(iVar9 + 0x18));
        uVar20 = iVar12 + *(volatile uint *)(iVar9 + 0x24);
      }
      if (cVar6 == '\x01') {
        if (uVar20 < iVar22 + 0x3bU) {
          *(volatile undefined4 *)(NRF_RADIO_NS_BASE + 0x10) = 1;
          uVar10 = 1;
          goto LAB_01020ee8;
        }
        *(volatile undefined1 *)(iVar9 + 7) = 1;
      }
      iVar22 = controller_radio_transition_schedule(
          iVar15, uVar20, *(volatile byte *)(iVar9 + 0x0a));
      if (iVar22 == 0) {
                    /* WARNING: Subroutine does not return */
        sdc_assertion_fail(0x3e,0xa52);
      }
      uVar10 = 0;
    }
    else {
      sdc_llcp_note_unsupported_pdu();
      uVar10 = 0;
    }
LAB_01020ee8:
    iVar22 = NRF_RADIO_NS_BASE;
    if (*(volatile char *)(iVar9 + 0x44) != '\0') {
      *(volatile undefined4 *)(NRF_RADIO_NS_BASE + 0x1ac) = 0;
      *(volatile undefined1 *)(iVar9 + 0x44) = 0;
      *(volatile uint *)(iVar22 + 0x514) = *(volatile uint *)(iVar22 + 0x514) & 0xfff0ffff;
      uVar20 = *(volatile uint *)(iVar9 + 0x14) & 0xfffffffc;
      *(volatile uint *)(iVar22 + 0x900) = uVar20;
      *(volatile uint *)(iVar9 + 0x14) = uVar20;
      *(volatile undefined4 *)(iVar22 + 0x910) = RADIO_TIMER_COMPARE_TICKS;
    }
    if ((int)(uVar21 << 0x1f) < 0) {
LAB_01020ff6:
      ((void (*)(void))(uintptr_t)*(uint32_t *)(iVar9 + 0x4c))();
      uVar21 = uVar21 & 0x10;
      if (uVar21 != 0) goto LAB_01020f2e;
LAB_01021000:
      if (*(volatile char *)(iVar9 + 9) != '\x02') {
        controller_radio_work_pending();
        return;
      }
    }
    else {
      if ((int)(uVar21 << 0x1e) < 0) {
        uVar20 = *(volatile uint *)(NRF_RADIO_NS_BASE + 0x450);
        if (((int)(uVar20 << 7) < 0) &&
           (((((uVar20 & 0xf00) == 0 || (uVar20 & 0xf0) == 0 || ((uVar20 & 0xf) == 0)) &&
             ((uVar20 << 8) >> 0x1d < 3)) && (*(volatile int *)(NRF_RADIO_NS_BASE + 0x454) != 0))))
        goto LAB_01020ff6;
        if (*(volatile byte *)(iVar9 + 0x34) < *(volatile byte *)(*(volatile int *)(iVar9 + 0x30) + 1)) {
          uVar20 = 0;
          uVar21 = uVar21 & 0xff;
        }
        else {
          uVar20 = ((uVar21 ^ 4) << 0x1d) >> 0x1f;
        }
        ((void (*)(uint32_t,uint32_t))(uintptr_t)*(uint32_t *)(iVar9 + 0x50))(uVar20,uVar10);
      }
      else if ((uVar21 & 0x28) != 0) {
        ((void (*)(uint32_t,uint32_t))(uintptr_t)*(uint32_t *)(iVar9 + 0x54))(uVar10,((uVar21 ^ 0x20) << 0x1a) >> 0x1f);
      }
      uVar21 = uVar21 & 0x10;
      if (uVar21 == 0) goto LAB_01021000;
LAB_01020f2e:
      ((void (*)(void))(uintptr_t)*(uint32_t *)(iVar9 + 0x58))();
      if (*(volatile char *)(iVar9 + 9) != '\x02') goto LAB_01020f60;
    }
    cVar6 = *(volatile char *)(iVar9 + 0xc);
    if (cVar6 != '\0') {
      if (cVar6 == '\x02') {
        *(volatile int *)(NRF_TIMER0_NS_BASE + 0x544) = *(volatile int *)(iVar9 + 0x24) + *(volatile int *)(iVar9 + 0x10);
      }
      else {
        if (cVar6 != '\x01') {
                    /* WARNING: Subroutine does not return */
        sdc_assertion_fail(0x3e,0xc15);
        }
        if (*(volatile uint *)(iVar9 + 0x10) <= *(volatile uint *)(iVar9 + 0x24)) {
                    /* WARNING: Subroutine does not return */
          sdc_assertion_fail(0x3e,0xc16);
        }
        *(volatile uint *)(NRF_TIMER0_NS_BASE + 0x544) = *(volatile uint *)(iVar9 + 0x10);
      }
      *(volatile undefined4 *)(NRF_TIMER0_NS_BASE + 0x1c4) = TIMER_TRANSITION_SHORTS;
    }
LAB_01020f60:
    cVar6 = controller_radio_work_pending();
    iVar22 = NVIC_ISER_BASE;
    if ((uVar21 != 0) && (cVar6 != '\x01')) {
      local_24 = 0;
      do {
        local_24 = local_24 + 1;
        if (local_24 == -1) {
                    /* WARNING: Subroutine does not return */
          sdc_assertion_fail(0x3e,0xc34);
        }
      } while ((*(volatile uint *)(NRF_RADIO_NS_BASE + 0x550) & 0xf7) == 4);
      *(volatile undefined4 *)(NRF_RADIO_NS_BASE + 0x110) = 0;
      *(volatile undefined4 *)(iVar22 + 0x180) = 0x100;
    }
    return;
}
