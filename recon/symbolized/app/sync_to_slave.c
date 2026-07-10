#include "g1_app_symbols.h"
/* named: sync_to_slave */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed sync_to_slave @ 0x26f74  (parity: 3/300 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, uint32_t b, ...);
extern uint32_t get_device_info(void);
extern int32_t get_current_work_mode(void);
extern void debug_print(void);
extern int32_t is_battery_critical(void);
extern int64_t k_uptime_get_1(void);
extern void k_msleep_ticks32768_a(int32_t);
extern void set_device_sync_timestamp(uint32_t);
extern void memcpy(void *dst, void *src, uint32_t n);
extern void memset_bytes(void *dst, int32_t val, uint32_t n);

typedef void (*fp774_t)(void *, int);

uint32_t sync_to_slave(char *param_1, uint32_t param_2, uint32_t *param_3, uint32_t param_4)
{
  char cVar1;
  uint8_t bVar2;
  uint8_t bVar3;
  char cVar4;
  volatile uint8_t *pbVar5;
  volatile int32_t *piVar6;
  uint32_t *puVar7;
  int32_t iVar8;
  int64_t lVar21;
  uint32_t uVar10;
  uint32_t uVar11;
  char *pcVar12;
  char *pcVar13;
  uint16_t uVar14;
  uint32_t uVar15;
  uint32_t uVar16;
  uint32_t uVar17;
  uint16_t uVar18;
  uint32_t *puVar19;
  int bVar20;

  uint8_t buf120[236];
  char local_10c[232];

  buf120[0] = 0;
  memset_bytes(&buf120[0], 0, 0xf8);
  uVar15 = *(uint32_t *)(*(uint32_t *)(param_1 + 0xfec));
  iVar8 = get_current_work_mode();
  if ((((iVar8 == 1) || ((iVar8 = (int32_t)get_device_info(), *(char *)(intptr_t)(iVar8 + 1) == '\b'))) ||
       ((iVar8 = is_battery_critical(), iVar8 == 1))) || (*param_1 == '\x02')) {
    uVar16 = 0;
    goto LAB_00026fa0;
  }
  lVar21 = k_uptime_get_1();
  {
    int64_t *plVar9 = (int64_t *)(param_1 + 0x1060);
    if ((int32_t)*plVar9 == 0 && *(int32_t *)(param_1 + 0x1064) == 0) {
LAB_0002700e:
      if ((param_2 != 0xc) ||
          ((int32_t)(uint32_t)((uint32_t)(lVar21 - *plVar9) < 1000) <=
           (int32_t)((uint64_t)(lVar21 - *plVar9) >> 32))) {
        uVar17 = 500;
        goto LAB_00027008;
      }
      uVar16 = 10;
LAB_00027396:
      *(int64_t *)(param_1 + 0x1060) = lVar21;
    }
    else {
      uVar16 = (uint32_t)(lVar21 - *plVar9);
      iVar8 = (int32_t)((uint64_t)(lVar21 - *plVar9) >> 32);
      if ((int32_t)(uint32_t)(uVar16 < 0x1389) <= iVar8) goto LAB_0002700e;
      if (param_2 == 0xc) {
        if (iVar8 < (int32_t)(uint32_t)(uVar16 < 1000)) {
          uVar16 = 10;
          goto LAB_00026fa0;
        }
        uVar17 = 3000;
      }
      else {
        uVar17 = 3000;
        if (param_2 == 0) {
          uVar17 = 5000;
        }
      }
LAB_00027008: ;
      uVar18 = 0x1f5;
      while ((uVar14 = (uint16_t)(*(volatile uint8_t *)((uintptr_t)&g_persist_task_status_lock) /*=0x20018d9c*/),
              *(volatile uint8_t *)((uintptr_t)&g_persist_task_status_lock) /*=0x20018d9c*/ != 0 &&
              (uVar18 = uVar18 - 1, uVar14 = uVar18, uVar18 != 0))) {
        k_msleep_ticks32768_a(1);
      }
      while (pbVar5 = (volatile uint8_t *)((uintptr_t)&g_esb_sync_inbound_status) /*=0x2000302b*/, *(volatile uint8_t *)((uintptr_t)&g_esb_sync_tx_busy_flag) /*=0x20018d8f*/ != 0) {
        k_msleep_ticks32768_a(1);
        uVar14 = uVar14 + 1;
      }
      uVar16 = (uint32_t)*(volatile uint8_t *)((uintptr_t)&g_esb_sync_inbound_status) /*=0x2000302b*/;
      bVar3 = (uint8_t)param_2;
      if ((uVar14 == 0) || (uVar16 != param_2)) {
        if (uVar16 == 1) {
          if (param_2 == 0) {
            if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
              iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
              uVar15 = "%s(): ESB send data after suspend cmd, ignore it.\n" /*=0x9ff05*/;
LAB_000270b8:
              if (iVar8 == 0) {
                DEBUG_PRINT(uVar15, "sync_to_slave" /*=0xa1ab1*/);
              }
              else {
                debug_print();
              }
            }
          }
          else {
            if (param_1[0xd5] == '\x06') {
              if (param_2 != 1) goto LAB_00027148;
              if (499 < *(volatile uint16_t *)((uintptr_t)&g_esb_sync_last_result) /*=0x2000f6e6*/) {
                *(volatile uint8_t *)((uintptr_t)&g_esb_sync_tx_busy_flag) /*=0x20018d8f*/ = bVar3;
                goto LAB_000270da;
              }
            }
            else {
              bVar20 = param_2 == 1;
LAB_000270e0:
              if (!bVar20) goto LAB_00027148;
              if (499 < *(volatile uint16_t *)((uintptr_t)&g_esb_sync_last_result) /*=0x2000f6e6*/) goto LAB_0002709c;
            }
LAB_000270ec:
            if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
              iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
              uVar15 = "%s(): ESB send same cmd, ignore it %d.\n" /*=0x9ff6a*/;
              goto LAB_0002707a;
            }
          }
        }
        else {
          if ((param_1[0xd5] != '\x06') || (uVar16 != 2)) {
            if (param_2 == 0) goto LAB_0002709c;
            if (uVar16 == param_2) {
              if ((param_2 != 7) && (4 < param_2 - 0xc)) {
                if (*(volatile uint16_t *)((uintptr_t)&g_esb_sync_last_result) /*=0x2000f6e6*/ < 500) goto LAB_000270ec;
                goto LAB_00027148;
              }
              *(volatile uint8_t *)((uintptr_t)&g_esb_sync_tx_busy_flag) /*=0x20018d8f*/ = 1;
            }
            else {
LAB_00027148:
              *(volatile uint8_t *)((uintptr_t)&g_esb_sync_tx_busy_flag) /*=0x20018d8f*/ = 1;
              if ((int32_t)param_2 < 3) goto LAB_000270da;
            }
            goto LAB_00027156;
          }
          if (param_2 != 0) {
            bVar20 = param_2 == 2;
            goto LAB_000270e0;
          }
          if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            uVar15 = "%s(): ESB send data after resume cmd, ignore it.\n" /*=0x9ff38*/;
            goto LAB_000270b8;
          }
        }
LAB_0002708e:
        *pbVar5 = 0;
      }
      else {
        if (param_2 != 0) {
          if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            uVar15 = "%s(): ESB send same type cmd %d, exit\n" /*=0x9fede*/;
LAB_0002707a:
            if (iVar8 == 0) {
              DEBUG_PRINT(uVar15, "sync_to_slave" /*=0xa1ab1*/, param_2);
            }
            else {
              debug_print();
            }
          }
          goto LAB_0002708e;
        }
LAB_0002709c:
        *(volatile uint8_t *)((uintptr_t)&g_esb_sync_tx_busy_flag) /*=0x20018d8f*/ = 1;
LAB_000270da:
        *pbVar5 = bVar3;
LAB_00027156:
        cVar1 = param_1[0xda];
        if (param_1[0xd5] == '\n') {
          bVar2 = *(uint8_t *)(*(int32_t *)(param_1 + 0x1000) + 7);
        }
        else {
          bVar2 = param_1[0xee4];
        }
        param_1[0xda] = cVar1 + '\x01';
        param_1[0xd4] = (bVar3 & 0x3f) | (uint8_t)((bVar2 & 3) << 6);
        param_1[0xc9] = (param_1[0xc9] & 0x3f) | 0x40;
        *(uint16_t *)(param_1 + 0xd6) = *(uint16_t *)(param_1 + 0x1072);
        *(int16_t *)(param_1 + 0xd8) =
            (int16_t)(*(uint32_t *)(param_1 + 0xeb8)) + *(int16_t *)(param_1 + 0x1074);
        buf120[4] = 2;
        uVar10 = *(uint32_t *)(param_1 + 0xd0);
        *(uint32_t *)(param_1 + 0xd0) = uVar15;
        if ((param_3 == (uint32_t *)0x0) || (param_4 == 0)) {
          uVar11 = 0;
LAB_000271d0:
          *(uint32_t *)(param_1 + 0xe5) = uVar11;
        }
        else {
          if (4 < param_4) {
            uVar11 = *param_3;
            goto LAB_000271d0;
          }
          memcpy(param_1 + 0xe5, param_3, param_4);
        }
        *(uint32_t *)(buf120 + 1) = *(uint32_t *)(param_1 + 0xc9);
        *(uint32_t *)(buf120 + 8) = *(uint32_t *)(param_1 + 0xcd);
        *(uint16_t *)(buf120 + 12) = *(uint16_t *)(param_1 + 0xd1);
        buf120[14] = param_1[0xd3];
        pcVar13 = param_1 + 0xd4;
        puVar7 = (uint32_t *)(buf120 + 16);
        do {
          puVar19 = puVar7;
          pcVar12 = pcVar13;
          uVar11 = *(uint32_t *)(pcVar12 + 4);
          pcVar13 = pcVar12 + 8;
          *puVar19 = *(uint32_t *)pcVar12;
          puVar19[1] = uVar11;
          puVar7 = puVar19 + 2;
        } while (pcVar13 != param_1 + 0xe4);
        puVar19[2] = *(uint32_t *)pcVar13;
        *(char *)(puVar19 + 3) = pcVar12[0xc];
        param_1[0x105a] = '\x01';
        piVar6 = (volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        bVar3 = param_1[0xec];
        if (((bVar3 == 6) || (bVar3 == 0)) || (param_2 != 0)) {
LAB_00027372:
          ((fp774_t)(*(uint32_t *)(param_1 + 0x774)))(&buf120[0], 0x21);
          uVar16 = 0;
          while (param_1[0x105a] != '\x02') {
            uVar16 = (uVar16 + 1) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
            if (uVar16 == uVar17) {
              uVar16 = uVar17;
              if (0 < *piVar6) {
                if (*(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                  DEBUG_PRINT("%s(): ESB send package id is changed, ignore it.\n" /*=0xa00d0*/, "sync_to_slave" /*=0xa1ab1*/, uVar17);
                }
                else {
                  debug_print();
                }
                if (param_1[0x105a] == '\x02') break;
              }
              set_device_sync_timestamp(uVar10);
              goto LAB_00027390;
            }
            k_msleep_ticks32768_a(1);
          }
          set_device_sync_timestamp(uVar15);
LAB_00027390:
          if (uVar17 <= uVar16) goto LAB_00026fa0;
          goto LAB_00027396;
        }
        cVar4 = param_1[0xee4];
        if (param_1[0xeb] == cVar4) {
          if (param_1[0xd5] == '\x10') {
            if ((param_1[0xe9] == param_1[0xcc]) && (param_1[0xce] == '\0')) {
              if (cVar4 != '\x02') goto LAB_00027304;
              goto LAB_000273f0;
            }
            param_1[0xda] = cVar1;
            if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
              iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
              uVar15 = " it.\n" /*=0xa002c*/;
              goto LAB_00027298;
            }
          }
          else if (param_1[0xeb] == '\x02') {
            if (param_1[0xcc] == param_1[0xe9]) {
              if (param_1[0xce] == '\0') goto LAB_000273f0;
              param_1[0xda] = cVar1;
              if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                uVar15 = "%s(): ESB send up package is receiving, ignore it.\n" /*=0xa0066*/;
                goto LAB_00027298;
              }
            }
            else {
              param_1[0xda] = cVar1;
              if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                uVar15 = "%s(): ESB send down package is changed, ignore it.\n" /*=0xa0032*/;
                goto LAB_00027298;
              }
            }
          }
          else {
LAB_00027304:
            if (cVar4 == '\x01') {
              if (param_1[0xea] == param_1[0xcd]) {
                if (param_1[0xcf] == '\0') goto LAB_000273f0;
                param_1[0xda] = cVar1;
                if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                  iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                  uVar15 = "%s(): ESB send down package is receiving, ignore it.\n" /*=0xa009a*/;
                  goto LAB_00027298;
                }
              }
              else {
                param_1[0xda] = cVar1;
                if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                  iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                  uVar15 = "%s(): ESB send up package is changed, ignore it.\n" /*=0xa0000*/;
                  goto LAB_00027298;
                }
              }
            }
            else {
LAB_000273f0:
              if (((bVar3 == (uint8_t)param_1[0xd5]) || ((uint8_t)param_1[0xd5] < 7)) || (bVar3 < 7))
                goto LAB_00027372;
              param_1[0xda] = cVar1;
              if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                uVar15 = "%s(): sync to slave failed!!!!!! wait_count %d\n" /*=0xa0102*/;
LAB_00027298:
                if (iVar8 == 0) {
                  DEBUG_PRINT(uVar15, "sync_to_slave" /*=0xa1ab1*/);
                }
                else {
                  debug_print();
                }
              }
            }
          }
        }
        else {
          param_1[0xda] = cVar1;
          if (0 < *(volatile int32_t *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            iVar8 = *(volatile int32_t *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            uVar15 = "%s(): ESB send imu status is changed, ignore it.\n" /*=0x9ff92*/;
            goto LAB_00027298;
          }
        }
      }
      uVar16 = 5000;
    }
  }
LAB_00026fa0:
  *(volatile uint16_t *)((uintptr_t)&g_esb_sync_last_result) /*=0x2000f6e6*/ = (uint16_t)uVar16;
  *(volatile uint8_t *)((uintptr_t)&g_esb_sync_tx_busy_flag) /*=0x20018d8f*/ = 0;
  return uVar16;
}

