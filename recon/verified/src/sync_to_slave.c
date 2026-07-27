/* sync_to_slave @ 0x26f74 / FUN_00026f74 (CFG parity: 7/7 cases, PROVEN) */
#include <stdint.h>

extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern uint8_t *get_device_info(void);
extern int32_t get_current_work_mode(void);
extern int32_t is_battery_critical(void);
extern unsigned long long k_uptime_get_1(void);
extern void FUN_0007cb8e(int32_t);
extern void FUN_0007d230(uint32_t);
extern void FUN_00086c04(void *dst, void *src, uint32_t n);
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
  uint32_t previous_value;
  uint32_t log_format;
  uint32_t uVar16;
  uint32_t uVar17;
  uint16_t uVar18;
  uint32_t *puVar19;
  int bVar20;

  uint8_t packet[252];

  *(uint32_t *)packet = 0;
  memset_bytes(packet + 4, 0, sizeof(packet) - 4);
  previous_value = *(uint32_t *)(*(uint32_t *)(param_1 + 0xfec));
  iVar8 = get_current_work_mode();
  if ((((iVar8 == 1) || (*(get_device_info() + 1) == 8)) ||
       (is_battery_critical() == 1)) || (*param_1 == 2)) {
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
      while ((uVar14 = (uint16_t)(*(volatile uint8_t *)0x20018d9cUL),
              *(volatile uint8_t *)0x20018d9cUL != 0 &&
              (uVar18 = uVar18 - 1, uVar14 = uVar18, uVar18 != 0))) {
        FUN_0007cb8e(1);
      }
      while (pbVar5 = (volatile uint8_t *)0x2000302bUL, *(volatile uint8_t *)0x20018d8fUL != 0) {
        FUN_0007cb8e(1);
        uVar14 = uVar14 + 1;
      }
      uVar16 = (uint32_t)*(volatile uint8_t *)0x2000302bUL;
      bVar3 = (uint8_t)param_2;
      if ((uVar14 == 0) || (uVar16 != param_2)) {
        if (uVar16 == 1) {
          if (param_2 == 0) {
            if (0 < *(volatile int32_t *)0x2000230cUL) {
              iVar8 = *(volatile int32_t *)0x20007554UL;
              log_format = 0x9ff05;
LAB_000270b8:
              if (iVar8 == 0) {
                log_message(log_format, 0xa1ab1);
              }
              else {
                debug_print(log_format, 0xa1ab1);
              }
            }
          }
          else {
            if (param_1[0xd5] == '\x06') {
              if (param_2 != 1) goto LAB_00027148;
              if (499 < *(volatile uint16_t *)0x2000f6e6UL) {
                *(volatile uint8_t *)0x20018d8fUL = bVar3;
                goto LAB_000270da;
              }
            }
            else {
              bVar20 = param_2 == 1;
LAB_000270e0:
              if (!bVar20) goto LAB_00027148;
              if (499 < *(volatile uint16_t *)0x2000f6e6UL) goto LAB_0002709c;
            }
LAB_000270ec:
            if (0 < *(volatile int32_t *)0x2000230cUL) {
              iVar8 = *(volatile int32_t *)0x20007554UL;
              log_format = 0x9ff6a;
              goto LAB_0002707a;
            }
          }
        }
        else {
          if ((param_1[0xd5] != '\x06') || (uVar16 != 2)) {
            if (param_2 == 0) goto LAB_0002709c;
            if (uVar16 == param_2) {
              if ((param_2 != 7) && (4 < param_2 - 0xc)) {
                if (*(volatile uint16_t *)0x2000f6e6UL < 500) goto LAB_000270ec;
                goto LAB_00027148;
              }
              *(volatile uint8_t *)0x20018d8fUL = 1;
            }
            else {
LAB_00027148:
              *(volatile uint8_t *)0x20018d8fUL = 1;
              if ((int32_t)param_2 < 3) goto LAB_000270da;
            }
            goto LAB_00027156;
          }
          if (param_2 != 0) {
            bVar20 = param_2 == 2;
            goto LAB_000270e0;
          }
          if (0 < *(volatile int32_t *)0x2000230cUL) {
            iVar8 = *(volatile int32_t *)0x20007554UL;
            log_format = 0x9ff38;
            goto LAB_000270b8;
          }
        }
LAB_0002708e:
        *pbVar5 = 0;
      }
      else {
        if (param_2 != 0) {
          if (0 < *(volatile int32_t *)0x2000230cUL) {
            iVar8 = *(volatile int32_t *)0x20007554UL;
            log_format = 0x9fede;
LAB_0002707a:
            if (iVar8 == 0) {
              log_message(log_format, 0xa1ab1, param_2);
            }
            else {
              debug_print(log_format, 0xa1ab1, param_2);
            }
          }
          goto LAB_0002708e;
        }
LAB_0002709c:
        *(volatile uint8_t *)0x20018d8fUL = 1;
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
        packet[0] = 2;
        uVar10 = *(uint32_t *)(param_1 + 0xd0);
        *(uint32_t *)(param_1 + 0xd0) = previous_value;
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
          FUN_00086c04(param_1 + 0xe5, param_3, param_4);
        }
        *(uint32_t *)(packet + 1) = *(uint32_t *)(param_1 + 0xc9);
        *(uint32_t *)(packet + 5) = *(uint32_t *)(param_1 + 0xcd);
        *(uint16_t *)(packet + 9) = *(uint16_t *)(param_1 + 0xd1);
        packet[11] = param_1[0xd3];
        pcVar13 = param_1 + 0xd4;
        puVar7 = (uint32_t *)(packet + 12);
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
        piVar6 = (volatile int32_t *)0x2000230cUL;
        bVar3 = param_1[0xec];
        if (((bVar3 == 6) || (bVar3 == 0)) || (param_2 != 0)) {
LAB_00027372:
          ((fp774_t)(*(uint32_t *)(param_1 + 0x774)))(packet, 0x21);
          uVar16 = 0;
          while (param_1[0x105a] != '\x02') {
            uVar16 = (uVar16 + 1) & 0xffff;
            if (uVar16 == uVar17) {
              uVar16 = uVar17;
              if (0 < *piVar6) {
                if (*(volatile int32_t *)0x20007554UL == 0) {
                  log_message(0xa00d0, 0xa1ab1, uVar17);
                }
                else {
                  debug_print(0xa00d0, 0xa1ab1, uVar17);
                }
                if (param_1[0x105a] == '\x02') break;
              }
              FUN_0007d230(uVar10);
              goto LAB_00027390;
            }
            FUN_0007cb8e(1);
          }
          FUN_0007d230(previous_value);
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
            if (0 < *(volatile int32_t *)0x2000230cUL) {
              iVar8 = *(volatile int32_t *)0x20007554UL;
              log_format = 0xa002c;
              goto LAB_00027298;
            }
          }
          else if (param_1[0xeb] == '\x02') {
            if (param_1[0xcc] == param_1[0xe9]) {
              if (param_1[0xce] == '\0') goto LAB_000273f0;
              param_1[0xda] = cVar1;
              if (0 < *(volatile int32_t *)0x2000230cUL) {
                iVar8 = *(volatile int32_t *)0x20007554UL;
                log_format = 0xa0066;
                goto LAB_00027298;
              }
            }
            else {
              param_1[0xda] = cVar1;
              if (0 < *(volatile int32_t *)0x2000230cUL) {
                iVar8 = *(volatile int32_t *)0x20007554UL;
                log_format = 0xa0032;
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
                if (0 < *(volatile int32_t *)0x2000230cUL) {
                  iVar8 = *(volatile int32_t *)0x20007554UL;
                  log_format = 0xa009a;
                  goto LAB_00027298;
                }
              }
              else {
                param_1[0xda] = cVar1;
                if (0 < *(volatile int32_t *)0x2000230cUL) {
                  iVar8 = *(volatile int32_t *)0x20007554UL;
                  log_format = 0xa0000;
                  goto LAB_00027298;
                }
              }
            }
            else {
LAB_000273f0:
              if (((bVar3 == (uint8_t)param_1[0xd5]) || ((uint8_t)param_1[0xd5] < 7)) || (bVar3 < 7))
                goto LAB_00027372;
              param_1[0xda] = cVar1;
              if (0 < *(volatile int32_t *)0x2000230cUL) {
                iVar8 = *(volatile int32_t *)0x20007554UL;
                log_format = 0xa0102;
LAB_00027298:
                if (iVar8 == 0) {
                  log_message(log_format, 0xa1ab1);
                }
                else {
                  debug_print(log_format, 0xa1ab1);
                }
              }
            }
          }
        }
        else {
          param_1[0xda] = cVar1;
          if (0 < *(volatile int32_t *)0x2000230cUL) {
            iVar8 = *(volatile int32_t *)0x20007554UL;
            log_format = 0x9ff92;
            goto LAB_00027298;
          }
        }
      }
      uVar16 = 5000;
    }
  }
LAB_00026fa0:
  *(volatile uint16_t *)0x2000f6e6UL = (uint16_t)uVar16;
  *(volatile uint8_t *)0x20018d8fUL = 0;
  return uVar16;
}
