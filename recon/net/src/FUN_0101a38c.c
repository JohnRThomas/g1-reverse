/* net-core controller_timing_snapshot_build @ 0x0101a38c
 * Back-map: FUN_0101a38c, exact executable extent 0x794 bytes.
 * Builds the controller's 24-byte current timing snapshot, including BLE PHY
 * airtime selection, schedule advancement, ticker request/list maintenance,
 * optional drift correction, and finite/deferred timeout handling.
 * Helper back-map: controller_radio_state_get=FUN_01019204,
 * controller_time_now=thunk_FUN_01025034, radio_slot_margin_get=FUN_0101a130,
 * radio_transition_overhead_get=FUN_0101a0e8,
 * radio_phy_airtime_base_get=FUN_010209f0,
 * controller_timing_request_submit=FUN_01022f3c,
 * controller_timing_request_schedule=FUN_0100d4d0,
 * signed_drift_clamp=FUN_0100f69c, sdc_assertion_fail=FUN_01008d00,
 * schedule_node_list_lock/tail_get/insert_after/find_at_or_after/is_locked/
 * phase_offset_get/unlock = FUN_0101deac/FUN_0101dda8/FUN_0101dd48/
 * FUN_0101ddc0/FUN_0101dec4/FUN_0101de10/FUN_0101deb8.
 */
#include <stdint.h>
typedef uint8_t byte; typedef union { uint64_t all; struct { uint32_t _0_4_, _4_4_; }; } u64parts;
struct controller_timing_request {
  uint8_t status;
  uint8_t reserved_01[3];
  uint32_t interval;
  uint16_t radio_overhead;
  uint8_t request_kind;
  uint8_t enabled;
  uint8_t reserved_0c[4];
  u64parts target_time;
};
#define CARRY4(a,b) ((uint32_t)(a) > UINT32_MAX - (uint32_t)(b))
#define CONCAT44(hi,lo) ((((uint64_t)(uint32_t)(hi))<<32)|(uint32_t)(lo))
extern int controller_radio_state_get(); extern int64_t controller_time_now(); extern int radio_slot_margin_get();
extern int radio_transition_overhead_get(int,...); extern int radio_phy_airtime_base_get(int); extern int controller_timing_request_submit(void *,...);
extern int controller_timing_request_schedule(void *,...); extern int signed_drift_clamp(int,...); extern int sdc_assertion_fail(int,...);
extern void schedule_node_list_lock(void); extern uint32_t *schedule_node_tail_get(void); extern void schedule_node_insert_after(uintptr_t,...);
extern uint32_t *schedule_node_find_at_or_after(uint32_t,...); extern int schedule_node_list_is_locked(void); extern uint32_t schedule_phase_offset_get(uint32_t,...); extern void schedule_node_list_unlock(void);

int controller_timing_snapshot_build(uint8_t *snapshot,int refresh_requested,int schedule_active,uint32_t timeout_units)

{
  int8_t phy;
  int64_t lVar2;
  int16_t sVar3;
  int bVar4;
  uint64_t uVar5;
  uint8_t *schedule_state;
  uint16_t uVar7;
  int iVar8;
  uint32_t uVar9;
  int iVar10;
  int iVar11;
  uint32_t *puVar12;
  int iVar13;
  int iVar14;
  uint32_t uVar15;
  uint32_t *puVar16;
  uint32_t uVar17;
  uint32_t uVar18;
  uint32_t uVar19;
  uint32_t uVar20;
  int iVar21;
  uint32_t uVar22;
  uint8_t uVar23;
  uint32_t uVar24;
  uint32_t uVar25;
  uint32_t uVar26;
  uint32_t uVar27;
  int64_t scheduled_time;
  int local_54;
  volatile int local_50;
  struct controller_timing_request request;
#define local_40 ((uint8_t *)&request)
#define local_3c request.interval
#define local_38 request.radio_overhead
#define local_36 request.request_kind
#define local_35 request.enabled
#define local_30 request.target_time
  
  schedule_state = ((uint8_t *)0x210010a0);
  iVar8 = controller_radio_state_get();
  scheduled_time = controller_time_now();
  uVar5 = (uint64_t)scheduled_time >> 0x20;
  uVar9 = (uint32_t)scheduled_time;
  uVar25 = *(uint32_t *)(schedule_state + 8);
  iVar10 = radio_slot_margin_get();
  uVar18 = 0;
  uVar24 = 0;
  uVar20 = 0;
  do {
    uVar18 = uVar18 + 1;
    uVar24 = uVar24 + *(int *)(schedule_state + (uVar20 + 2) * 4) + iVar10;
    uVar20 = uVar18 & 0xff;
  } while (uVar20 <= (byte)schedule_state[0x2f]);
  uVar18 = *(uint32_t *)(schedule_state + 4);
  if ((uVar18 == uVar24) && (schedule_active != 0)) {
    if ((*schedule_state == '\0') || (*(int16_t *)(schedule_state + 0x74) == 0)) {
      if (refresh_requested != 0) {
        local_50 = 0;
        bVar4 = 1;
        goto LAB_0101a514;
      }
      phy = *(char *)((uint32_t)(byte)schedule_state[0x2e] + iVar8 + 5);
      if (phy == '\b') {
        iVar10 = 0x690;
      }
      else if (phy == '\x04') {
        iVar10 = 0x140;
LAB_0101aa3e:
        iVar10 = iVar10 + 0x17e;
      }
      else {
        if (phy == '\x02') {
          iVar10 = 0x48;
        }
        else {
          switch(phy) {
          case '\x01':
            iVar10 = 0x150;
            break;
          default:
            goto switchD_0101a5bc_caseD_2;
          case '\x04':
          case '\b':
            iVar10 = 0xa0;
            if (phy == '\x04') goto LAB_0101aa3e;
          }
          if (phy != '\x02') {
            iVar10 = iVar10 + 0x28;
            goto LAB_0101a754;
          }
        }
        iVar10 = iVar10 + 0x18;
      }
LAB_0101a754:
      iVar13 = radio_phy_airtime_base_get(phy);
      if (*(int *)(schedule_state + 0x34) == 0x7fffffff && *(int *)(schedule_state + 0x30) == -1) {
        uVar26 = 0;
        uVar27 = 0;
        local_50 = 0;
        bVar4 = 1;
        local_30.all = CONCAT44(local_30._4_4_,local_30._0_4_);
      }
      else {
        local_40[0] = 0;
        lVar2 = (uint64_t)0x10624dd3u * (uint64_t)(iVar13 + 0xa3a1);
        uVar20 = iVar10 + 0x11a + (uint32_t)((uint64_t)lVar2 >> 0x26);
        local_3c = uVar20;
        local_38 = radio_transition_overhead_get(iVar13,*(int *)(schedule_state + 0x30),(int)lVar2);
        local_35 = 1;
        iVar10 = radio_transition_overhead_get(0);
        local_30.all = scheduled_time + (uint64_t)(iVar10 + 0x135U & 0xffff);
        local_36 = 2;
        iVar10 = controller_timing_request_submit(local_40);
        if (iVar10 == 0) {
                    /* WARNING: Subroutine does not return */
          do { sdc_assertion_fail(0x21,0x537); } while (1);
        }
        if ((int)(((*(int *)(schedule_state + 0x34) - local_30._4_4_) -
                  (uint32_t)(*(uint32_t *)(schedule_state + 0x30) < local_30._0_4_)) -
                 (uint32_t)(*(uint32_t *)(schedule_state + 0x30) - local_30._0_4_ < uVar20)) < 0) {
          uVar26 = 0;
          local_50 = 0;
          bVar4 = 1;
          uVar25 = 0;
          uVar27 = uVar26;
        }
        else {
          uVar26 = 0;
          local_50 = 0;
          bVar4 = 1;
          uVar27 = 0;
        }
      }
      goto LAB_0101a59e;
    }
    if (refresh_requested != 0) goto LAB_0101a50e;
LAB_0101a5d0:
    uVar20 = *(uint32_t *)(schedule_state + 0x50);
    iVar13 = *(int *)(schedule_state + 0x54);
    uVar27 = 0;
    uVar19 = uVar18 * ((uVar9 - uVar20) / uVar18);
    uVar17 = uVar19 + uVar18 + uVar20;
    iVar10 = radio_transition_overhead_get(0);
    if ((iVar10 + 0x135U & 0xffff) <= uVar17 - uVar9) {
      local_3c = *(uint32_t *)(schedule_state + 0x3c);
      local_40[0] = 0;
      local_38 = radio_transition_overhead_get(0);
      uVar17 = *(uint32_t *)(schedule_state + 0x50);
      uVar20 = *(uint32_t *)(schedule_state + 4);
      uVar19 = uVar20 * ((*(int *)(schedule_state + 0x20) - uVar17) / uVar20);
      local_30._0_4_ = uVar19 + uVar17;
      local_30._4_4_ = *(int *)(schedule_state + 0x54) + (uint32_t)CARRY4(uVar19,uVar17);
      local_36 = 1;
      local_35 = 1;
      if (*schedule_state == '\x04') {
        if (uVar19 < uVar20 * 10) {
          local_36 = 2;
        }
        else {
          local_36 = 1;
        }
      }
      uVar27 = 0;
      uVar26 = controller_timing_request_schedule(local_40, uVar20);
      scheduled_time = CONCAT44(local_30._4_4_,local_30._0_4_);
      bVar4 = 0;
      local_50 = 1;
      local_30.all = scheduled_time;
      goto LAB_0101a59e;
    }
    uVar22 = *(uint32_t *)(schedule_state + 4);
    bVar4 = 0;
    phy = *(char *)(iVar8 + 5);
    uVar26 = (uVar17 - (uVar22 * ((uint32_t)(*(int *)(schedule_state + 0x20) - *(int *)(schedule_state + 0x50)) / uVar22
                                 ) + *(int *)(schedule_state + 0x50))) / uVar22;
    scheduled_time = CONCAT44(iVar13 + (uint32_t)CARRY4(uVar18,uVar20) + (uint32_t)CARRY4(uVar19,uVar18 + uVar20) +
                      (uint32_t)CARRY4(uVar22,uVar17),uVar22 + uVar17);
    local_50 = 1;
  }
  else {
    if (refresh_requested == 0) {
      if (schedule_active != 0) goto LAB_0101a5d0;
      uVar20 = *(uint32_t *)(schedule_state + 0x50);
      iVar21 = *(int *)(schedule_state + 0x54);
      uVar19 = uVar18 * ((uVar9 - uVar20) / uVar18);
      uVar17 = uVar19 + uVar20;
      iVar10 = controller_radio_state_get();
      iVar13 = radio_transition_overhead_get(0);
      iVar11 = radio_slot_margin_get();
      phy = schedule_state[0x2f];
      uVar26 = (uVar9 - uVar17) + (iVar13 + 0x135U & 0xffff);
      uVar25 = uVar26;
      if (*(uint32_t *)(schedule_state + 4) <= uVar26) {
        uVar25 = uVar26 - *(uint32_t *)(schedule_state + 4);
      }
      if (phy == '\0') {
        uVar27 = 0;
      }
      else {
        uVar27 = *(int *)(schedule_state + 8) + iVar11;
        uVar22 = uVar25;
        if (uVar27 <= uVar25) {
          uVar22 = uVar25 - uVar27;
        }
        uVar27 = (uint32_t)(uVar27 <= uVar25);
        uVar25 = uVar22;
        if (phy != '\x01') {
          if ((uint32_t)(*(int *)(schedule_state + 0xc) + iVar11) <= uVar22) {
            uVar27 = uVar27 + 1;
            uVar25 = uVar22 - (*(int *)(schedule_state + 0xc) + iVar11);
          }
          if ((phy != '\x02') && ((uint32_t)(*(int *)(schedule_state + 0x10) + iVar11) <= uVar25)) {
            uVar27 = uVar27 + 1;
            uVar25 = uVar25 - (*(int *)(schedule_state + 0x10) + iVar11);
          }
        }
      }
      iVar13 = uVar27 + 2;
      phy = *(char *)(iVar10 + uVar27 + 5);
      uVar22 = *(uint32_t *)(schedule_state + iVar13 * 4);
      if (phy == '\b') {
        iVar10 = 0x690;
      }
      else if (phy == '\x04') {
        iVar14 = 0x140;
LAB_0101aa14:
        iVar10 = iVar14 + 0x17e;
      }
      else {
        if (phy == '\x02') {
          iVar10 = 0x48;
        }
        else {
          switch(phy) {
          case '\x01':
            iVar10 = 0x150;
            break;
          default:
            goto switchD_0101a5bc_caseD_2;
          case '\x04':
          case '\b':
            iVar14 = 0xa0;
            iVar10 = 0xa0;
            if (phy == '\x04') goto LAB_0101aa14;
          }
          if (phy != '\x02') {
            iVar10 = iVar10 + 0x28;
            goto LAB_0101a8e8;
          }
        }
        iVar10 = iVar10 + 0x18;
      }
LAB_0101a8e8:
      iVar14 = radio_phy_airtime_base_get(phy);
      if (uVar22 < iVar10 + uVar25 + 0x11a +
                   (uint32_t)((uint64_t)0x10624dd3u * (uint64_t)(iVar14 + 0xa3a1) >> 0x26)) {
        if (uVar27 < (byte)schedule_state[0x2f]) {
          if (*(uint32_t *)(schedule_state + 4) <= uVar26) {
                    /* WARNING: Subroutine does not return */
            do { sdc_assertion_fail(0x21,0x4d7); } while (1);
          }
          uVar25 = *(uint32_t *)(schedule_state + (uVar27 + 3) * 4);
          uVar22 = iVar11 + uVar25;
          uVar27 = uVar27 + 1;
        }
        else {
          uVar22 = *(uint32_t *)(schedule_state + 4);
          if (uVar26 < uVar22) {
            uVar25 = *(uint32_t *)(schedule_state + iVar13 * 4);
          }
          else {
            uVar25 = uVar22 << 1;
            uVar22 = uVar22 << 1;
            if (uVar25 <= uVar26) {
                    /* WARNING: Subroutine does not return */
              do { sdc_assertion_fail(0x21,0x4f4); } while (1);
            }
            uVar25 = *(uint32_t *)(schedule_state + iVar13 * 4);
          }
        }
      }
      else {
        uVar25 = *(int *)(schedule_state + iVar13 * 4) - uVar25;
        uVar22 = uVar26;
      }
      if ((int)uVar25 < 0) {
                    /* WARNING: Subroutine does not return */
        do { sdc_assertion_fail(0x21,0x4fd); } while (1);
      }
      uVar15 = *(uint32_t *)(schedule_state + 0x50);
      uVar26 = *(uint32_t *)(schedule_state + 4);
      scheduled_time = CONCAT44(iVar21 + (uint32_t)CARRY4(uVar19,uVar20) + (uint32_t)CARRY4(uVar22,uVar17),
                        uVar22 + uVar17);
      uVar20 = uVar26 * ((*(int *)(schedule_state + 0x18) - uVar15) / uVar26);
      iVar10 = uVar20 + uVar15;
      *(int *)(schedule_state + 0x50) = iVar10;
      uVar26 = ((uVar22 + uVar17) - iVar10) / uVar26;
      *(uint32_t *)(schedule_state + 0x54) = *(int *)(schedule_state + 0x54) + (uint32_t)CARRY4(uVar20,uVar15);
      local_50 = 1;
      bVar4 = 0;
    }
    else {
LAB_0101a50e:
      bVar4 = 0;
      local_50 = refresh_requested;
LAB_0101a514:
      scheduled_time = scheduled_time + 2000;
      schedule_node_list_lock();
      puVar12 = (uint32_t *)schedule_node_tail_get();
      if (*schedule_state == '\x05') {
        puVar16 = (uint32_t *)schedule_node_find_at_or_after(*(uint32_t *)(*(int *)(schedule_state + 0x28) + 0x2e0),0);
        if (puVar12 == puVar16) {
          local_54 = *(int *)(schedule_state + 0x28);
          uVar20 = *(uint32_t *)(schedule_state + 0x58);
          if (*(uint32_t *)(schedule_state + 0x58) < *(uint32_t *)(local_54 + 0x2e0)) {
            uVar20 = *(uint32_t *)(local_54 + 0x2e0);
          }
          *(uint32_t *)(schedule_state + 0x58) = uVar20;
          *(int *)(schedule_state + 0x70) = local_54 + 0x2d8;
        }
        else {
          schedule_node_insert_after(*(int *)(schedule_state + 0x28) + 0x2d8);
          schedule_state[0x70] = '\0';
          schedule_state[0x71] = '\0';
          schedule_state[0x72] = '\0';
          schedule_state[0x73] = '\0';
          local_54 = *(int *)(schedule_state + 0x28);
          if (local_54 == 0) {
                    /* WARNING: Subroutine does not return */
            do { sdc_assertion_fail(0x21,0x7a2); } while (1);
          }
        }
        if (puVar16 == (uint32_t *)0x0) {
          *(uint32_t *)(local_54 + 0x2d8) = 0;
          *(uint32_t *)(local_54 + 0x2dc) = 0;
        }
        else {
          iVar10 = schedule_node_list_is_locked();
          if (iVar10 == 0) {
                    /* WARNING: Subroutine does not return */
            do { sdc_assertion_fail(0x21,0x7a8); } while (1);
          }
          uVar20 = puVar16[2];
          uVar17 = *puVar16;
          uVar19 = puVar16[1];
          *(uint32_t *)(local_54 + 0x2d8) = uVar17 + uVar20;
          *(uint32_t *)(local_54 + 0x2dc) = uVar19 + CARRY4(uVar17,uVar20);
          *(int16_t *)(local_54 + 0x2fc) = (short)puVar16[9];
        }
      }
      schedule_node_insert_after(0x210010f0u,puVar12);
      if (puVar12 != (uint32_t *)0x0) {
        uVar26 = *puVar12;
        uVar19 = puVar12[2];
        uVar17 = puVar12[1];
        uVar20 = puVar12[9];
        uVar27 = *(uint32_t *)(schedule_state + 4);
        *(int16_t *)(schedule_state + 0x74) = (short)uVar20;
        uVar20 = schedule_phase_offset_get(uVar19 + uVar26,uVar17 + CARRY4(uVar19,uVar26),uVar27,
                              (int)(short)uVar20,scheduled_time);
        if (uVar27 < uVar20) {
                    /* WARNING: Subroutine does not return */
          do { sdc_assertion_fail(0x21,0x3fc); } while (1);
        }
        scheduled_time = scheduled_time + (uint64_t)uVar20;
      }
      schedule_node_list_unlock();
      *(uint32_t *)(schedule_state + 0x50) = (uint32_t)scheduled_time - *(uint32_t *)(schedule_state + 4);
      *(uint32_t *)(schedule_state + 0x54) =
           (int)((uint64_t)scheduled_time >> 0x20) - (uint32_t)((uint32_t)scheduled_time < *(uint32_t *)(schedule_state + 4));
      if (timeout_units == 0) {
        uVar26 = 1;
        *(volatile uint32_t *)(schedule_state + 0x30) = UINT32_MAX;
        *(volatile uint32_t *)(schedule_state + 0x34) = INT32_MAX;
        uVar27 = 0;
        local_30.all = CONCAT44(local_30._4_4_,local_30._0_4_);
      }
      else {
        uVar27 = 0;
        *(uint64_t *)(schedule_state + 0x30) = (uint64_t)timeout_units * 10000 + scheduled_time;
        uVar26 = 1;
        local_30.all = CONCAT44(local_30._4_4_,local_30._0_4_);
      }
    }
LAB_0101a59e:
    phy = *(char *)(iVar8 + uVar27 + 5);
  }
  if (phy == '\b') {
    iVar8 = 0x690;
  }
  else if (phy == '\x04') {
    iVar8 = 0x2be;
  }
  else {
    if (phy == '\x02') {
      iVar8 = 0x48;
    }
    else {
      if (phy == '\x01') {
        iVar8 = 0x150;
      } else if ((phy == '\x04') || (phy == '\b')) {
        iVar8 = 0xa0;
      } else {
switchD_0101a5bc_caseD_2:
        phy = (int8_t)sdc_assertion_fail(5,0x104);
        if (phy == '\x04') {
          iVar8 = 0x140 + 0x17e;
          goto LAB_0101a666;
        }
        if (phy == '\x02') {
          iVar8 = 0x48 + 0x18;
          goto LAB_0101a666;
        }
        /* Returning through the firmware's noreturn panic island physically
           enters its final timing-maintenance loop. */
        (void)radio_phy_airtime_base_get(phy);
        *(volatile uint32_t *)(schedule_state + 0x50) = 0;
        *(volatile uint32_t *)(schedule_state + 0x54) = 0;
        for (;;) {
          (void)radio_phy_airtime_base_get(phy);
          (void)radio_transition_overhead_get(0);
          *(volatile uint32_t *)(schedule_state + 0x50) = 0;
          *(volatile uint32_t *)(schedule_state + 0x54) = 0;
        }
      }
      if (phy != '\x02') {
        iVar8 = iVar8 + 0x28;
        goto LAB_0101a666;
      }
    }
    iVar8 = iVar8 + 0x18;
  }
LAB_0101a666:
  iVar10 = radio_phy_airtime_base_get(phy);
  uVar19 = iVar8 + 0x11a + (uint32_t)((uint64_t)0x10624dd3u * (uint64_t)(iVar10 + 0xa3a1) >> 0x26);
  uVar20 = *(uint32_t *)(schedule_state + 0x30) - (uint32_t)scheduled_time;
  iVar8 = (*(int *)(schedule_state + 0x34) - (int)((uint64_t)scheduled_time >> 0x20)) -
          (uint32_t)(*(uint32_t *)(schedule_state + 0x30) < (uint32_t)scheduled_time);
  if (iVar8 < (int)(uint32_t)(uVar20 == 0)) {
    uVar25 = 0;
  }
  else if ((int)(uint32_t)(uVar25 < uVar20) <= -iVar8) {
    uVar25 = uVar20;
  }
  if (*(uint32_t *)(schedule_state + (uVar27 + 2) * 4) <= uVar25) {
    uVar25 = *(uint32_t *)(schedule_state + (uVar27 + 2) * 4);
  }
  *(uint32_t *)(schedule_state + 0x3c) = uVar25;
  if ((uVar26 != 0) && (local_50 != 0)) {
    uVar25 = signed_drift_clamp((int)*(int16_t *)(schedule_state + 0x74),(uVar26 & 0x7fff) << 1);
    iVar8 = *(int *)(schedule_state + 0x28);
    sVar3 = *(int16_t *)(schedule_state + 0x74) - (short)uVar25;
    *(int16_t *)(schedule_state + 0x74) = sVar3;
    if (iVar8 != 0) {
      *(int16_t *)(iVar8 + 0x2fc) = sVar3;
      uVar20 = *(uint32_t *)(iVar8 + 0x2d8);
      *(uint32_t *)(iVar8 + 0x2d8) = uVar20 + uVar25;
      *(uint32_t *)(iVar8 + 0x2dc) =
           *(int *)(iVar8 + 0x2dc) + ((int)uVar25 >> 0x1f) + (uint32_t)CARRY4(uVar20,uVar25);
    }
    uVar20 = *(uint32_t *)(schedule_state + 0x50);
    scheduled_time = scheduled_time + (int)uVar25;
    *(uint32_t *)(schedule_state + 0x50) = uVar20 + uVar25;
    *(uint32_t *)(schedule_state + 0x54) =
         ((int)uVar25 >> 0x1f) + *(int *)(schedule_state + 0x54) + (uint32_t)CARRY4(uVar20,uVar25);
  }
  if (refresh_requested != 0) {
    *(int64_t *)(schedule_state + 0x18) = scheduled_time;
  }
  uVar23 = 1;
  uVar25 = uVar19;
  if (uVar18 != uVar24) {
    uVar25 = *(uint32_t *)(schedule_state + 0x3c);
  }
  *(int64_t *)(schedule_state + 0x20) = scheduled_time;
  *(uint32_t *)(schedule_state + 0x38) = uVar25;
  snapshot[0xb] = 1;
  uVar7 = radio_transition_overhead_get(0);
  phy = *schedule_state;
  *(uint16_t *)(snapshot + 8) = uVar7;
  if ((phy == '\x04') &&
     ((uint32_t)((int)scheduled_time - *(int *)(schedule_state + 0x50)) < (uint32_t)(*(int *)(schedule_state + 4) * 10))) {
    uVar23 = 2;
  }
  snapshot[10] = uVar23;
  *(uint32_t *)(snapshot + 4) = *(uint32_t *)(schedule_state + 0x38);
  if (bVar4) {
    *(volatile uint8_t *)snapshot = 1;
    uVar25 = *(uint32_t *)(schedule_state + 0x30) - uVar9;
    iVar8 = (*(int *)(schedule_state + 0x34) - (int)uVar5) - (uint32_t)(*(uint32_t *)(schedule_state + 0x30) < uVar9);
    if (iVar8 < (int)(uint32_t)(uVar25 == 0)) {
      uVar25 = 0;
    }
    else if (-iVar8 < (int)(uint32_t)(0x0f424000u < uVar25)) {
      uVar25 = 0x0f424000u;
    }
    *(uint32_t *)(snapshot + 0x10) = uVar25 - uVar19;
  }
  else {
    *(volatile uint8_t *)snapshot = 0;
    *(volatile uint32_t *)(snapshot + 0x10) = (uint32_t)scheduled_time;
    *(volatile uint32_t *)(snapshot + 0x14) =
        (uint32_t)((uint64_t)scheduled_time >> 32);
  }
  return uVar19 <= *(uint32_t *)(schedule_state + 0x3c);
}
