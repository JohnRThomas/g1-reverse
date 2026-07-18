/* readable reconstruction; identity: FUN_01014b18 @ 0x01014b18
 * public-name: sdc_conn_event_process
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_conn_event_process                   <= FUN_01014b18 @ 0x01014b18
 * address symbols (name @ address):
 *   rodata_10100a1                           @ 0x010100a1
 *   g_net_link_ctx_a                         @ 0x21000f68
 */
/* net-core FUN_01014b18 @ 0x01014b18 (sdc_conn_event_process)
 * CPUNET private SoftDevice Controller connection-event processor.
 * Raw backmap: FUN_01014b18 at analysis 0x01014b18 / runtime 0x01015318.
 * Reviewed executable ownership is 0x01014b18..0x01015c9f (4488 bytes),
 * including branch-owned islands but excluding the literal words at 0x01015ca0.
 */
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint8_t undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t ulonglong;
typedef uint32_t code();

extern uint32_t FUN_010091f8();
extern uint32_t FUN_0100a17c();
extern uint32_t FUN_0100a984();
extern uint32_t FUN_0100b608();
extern uint32_t FUN_0100b614();
extern uint32_t FUN_0100b624();
extern uint32_t FUN_0100b630();
extern uint32_t FUN_0100d3c0();
extern uint32_t FUN_0100d5d0();
extern uint32_t FUN_0100e5d8();
extern uint32_t controller_packet_length_matches_type(); /* FUN_0100e610 */
extern uint32_t sdc_work_submit(); /* FUN_0100ef88 */
extern uint32_t controller_work_update_or_enqueue(); /* FUN_0100efc8 */
extern uint32_t FUN_0100f110();
extern uint32_t controller_timing_windows_clamp(); /* FUN_0100f1f8 */
extern uint32_t controller_procedure_counters_reset(); /* FUN_0100f784 */
extern uint32_t controller_procedure_reference_release(); /* FUN_0100f7b0 */
extern uint32_t FUN_0100f7d0();
extern uint32_t FUN_0100f7e0();
extern uint32_t controller_procedure_slot_reserve(); /* FUN_0100f834 */
extern uint32_t FUN_0100fae4();
extern uint32_t FUN_010108b8();
extern uint32_t FUN_01013e98();
extern uint32_t FUN_01014884();
extern uint32_t FUN_01016250();
extern uint32_t FUN_0101f934();
extern uint32_t radio_phy_airtime_tail_get(); /* FUN_010209e0 */
extern uint32_t radio_phy_airtime_base_get(); /* FUN_010209f0 */
extern uint32_t FUN_01026d16();
extern uint32_t FUN_01029882();
extern void sdc_assertion_fail(uint32_t, uint32_t); /* FUN_01008d00 */

#define DAT_01014de8 ((uintptr_t)0x21000f68u)
#define DAT_01014dec ((uint32_t)0x010109cdu)
#define DAT_01014df0 ((uint32_t)0x10624dd3u)
#define DAT_01014df4 ((volatile uint32_t *)0x210001d0u)
#define DAT_01014df8 ((volatile uint32_t *)0x21000018u)
#define DAT_010151c4 ((uint32_t)0x010100a1u)
#define DAT_010151c8 ((uintptr_t)0x21000124u)
#define DAT_010151cc ((uint32_t)0x21000f68u)
#define DAT_01015618 ((undefined4 *)0x210001dcu)
#define DAT_0101561c ((uint32_t)0x21000f68u)
#define DAT_01015620 ((uintptr_t)0x21000078u)
#define DAT_01015aa8 ((volatile uint32_t *)0x21000204u)
#define DAT_01015aac ((uint32_t)0x21000f68u)
#define DAT_01015ca0 ((uint32_t)0x21000f68u)
#define DAT_01015ca4 ((volatile uint32_t *)0x2100020cu)

static __attribute__((always_inline, noreturn)) inline void
fatal(uint32_t domain, uint32_t reason)
{
  for (;;) sdc_assertion_fail(domain, reason);
}

void sdc_conn_event_process(uint32_t param_1, uint32_t param_2)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 uVar6;
  int8_t cVar7;
  short sVar8;
  undefined2 uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  byte bVar14;
  uint uVar15;
  undefined2 *puVar16;
  code *pcVar17;
  int iVar18;
  bool bVar19;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int8_t *pcStack_28;
  uint uStack_24;

  iVar5 = DAT_01014de8;
  iVar10 = FUN_0100a17c(**(undefined2 **)(DAT_01014de8 + 4));
  if (iVar10 == 0) {
                    /* WARNING: Subroutine does not return */
    fatal(0x31,0xbc3);
  }
  uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
  iVar18 = *(int *)(iVar5 + 4);
  if ((int)(uVar15 << 0x17) < 0) {
    *(undefined2 *)(iVar18 + 0xf6) = 0;
    *(undefined1 *)(iVar18 + 0x2f4) = 0;
    if (*(int8_t *)(iVar18 + 0xcb) != '\0') goto LAB_01014b52;
LAB_01014e10:
    iVar18 = FUN_0100d3c0(iVar18 + 0xa8,6,*(undefined1 *)(iVar18 + 0xc6),1);
    uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
    if (iVar18 == 0) goto LAB_01014b8a;
    iVar18 = *(int *)(iVar5 + 4);
    if ((-1 < (int)(uVar15 << 0x14)) || (*(int8_t *)(iVar18 + 0xcb) == '\0')) goto LAB_01014b58;
LAB_01014e3a:
    *(undefined4 *)(iVar18 + 0xe8) = 0;
  }
  else {
    *(short *)(iVar18 + 0xf6) = *(short *)(iVar18 + 0xf6) + 1;
    if (*(int8_t *)(iVar18 + 0xcb) == '\0') goto LAB_01014e10;
LAB_01014b52:
    if ((int)(uVar15 << 0x14) < 0) goto LAB_01014e3a;
LAB_01014b58:
    uVar12 = *(uint *)(iVar18 + 0xec);
    uVar13 = *(int *)(iVar18 + 0xe8) + 1;
    *(uint *)(iVar18 + 0xe8) = uVar13;
    if ((uVar12 < uVar13) || (uVar12 - uVar13 <= *(ushort *)(iVar5 + 0x1a) + 5)) {
      *(undefined1 *)(iVar18 + 0xf4) = 1;
    }
    uVar4 = DAT_01014dec;
    if (uVar12 <= uVar13) {
      *(undefined4 *)(iVar18 + 0xe8) = 0;
      controller_work_update_or_enqueue(iVar18 + 0x1c5,uVar4,2);
      uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
LAB_01014b8a:
      iVar18 = *(int *)(iVar5 + 4);
    }
  }
  cVar7 = *(int8_t *)(iVar18 + 0xc9);
  if ((uVar15 & 0x300) != 0) {
    if (cVar7 == '\0') {
      *(undefined1 *)(iVar18 + 0xc9) = 1;
      FUN_01013e98(iVar18,1);
      iVar18 = *(int *)(iVar5 + 4);
      uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
      cVar7 = *(int8_t *)(iVar18 + 0xc9);
    }
    else if (cVar7 == '\x03') {
      *(undefined1 *)(iVar18 + 0xc9) = 2;
      FUN_01013e98(iVar18,1);
      iVar18 = *(int *)(iVar5 + 4);
      uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
      cVar7 = *(int8_t *)(iVar18 + 0xc9);
    }
  }
  if ((cVar7 == '\x01') && ((int)(uVar15 << 0x15) < 0)) {
    *(undefined1 *)(iVar18 + 0xc9) = 2;
  }
  if (param_1 == 0) {
    if ((int)(uVar15 << 0x19) < 0) {
      *(undefined2 *)(iVar18 + 0x308) = 0;
      puVar3 = DAT_01015618;
      uVar4 = DAT_0101561c;
    }
    else {
      *(short *)(iVar18 + 0x308) = *(short *)(iVar18 + 0x308) + 1;
      puVar3 = DAT_01015618;
      uVar4 = DAT_0101561c;
    }
    uVar12 = param_2;
    if (param_2 == 0) {
      if ((int)(uVar15 << 0x1c) < 0) {
        cVar7 = *(int8_t *)(iVar18 + 0x14e);
        if (cVar7 == '\"') {
          *(undefined1 *)(iVar18 + 0x1aa) = 0;
          if ((code *)*puVar3 != (code *)0x0) {
            (*(code *)*puVar3)(*(int *)(iVar5 + 4) + 0x158,*(int *)(iVar5 + 4) + 0x1aa);
          }
          controller_procedure_counters_reset(DAT_0101561c);
          iVar18 = *(int *)(iVar5 + 4);
          cVar7 = *(int8_t *)(iVar18 + 0x14e);
        }
        else if ((cVar7 == '*') || (cVar7 == '\x1c')) {
          *(undefined1 *)(iVar18 + 0x174) = 0;
          controller_procedure_counters_reset(uVar4);
          iVar18 = *(int *)(iVar5 + 4);
          cVar7 = *(int8_t *)(iVar18 + 0x14e);
        }
        if (cVar7 == -2) {
                    /* WARNING: Subroutine does not return */
          fatal(0x31,0x588);
        }
        cVar7 = *(int8_t *)(iVar18 + 0xc6);
        *(undefined1 *)(iVar18 + 0x14e) = 0xfe;
        uVar4 = DAT_0101561c;
        if (cVar7 == '\x1b') {
          cVar7 = '\0';
          *(undefined1 *)(iVar18 + 0x105) = 0;
          controller_procedure_reference_release(uVar4);
          iVar18 = *(int *)(iVar5 + 4);
          *(undefined1 *)(iVar18 + 0xc6) = 0;
        }
        if (*(int8_t *)(iVar18 + 0xc5) == '!') {
          iVar11 = FUN_0100d3c0(iVar18 + 0xa8,0xb,cVar7,1);
          iVar18 = *(int *)(iVar5 + 4);
          if (iVar11 == 0) {
            *(undefined1 *)(iVar18 + 0xc5) = 0x22;
          }
          else {
            *(undefined1 *)(iVar18 + 0xc5) = 0x2f;
          }
        }
        else if (*(int8_t *)(iVar18 + 0xc5) == '2') {
          *(undefined1 *)(iVar18 + 0xc5) = 0;
          *(undefined1 *)(iVar18 + 0x100) = 0;
          *(undefined1 *)(iVar18 + 0x3b5) = 1;
        }
        if (*(int8_t *)(iVar18 + 199) == '\b') {
          *(undefined1 *)(iVar5 + 0x1c) = 2;
          *(undefined1 *)(iVar18 + 0x14e) = 2;
        }
        uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
      }
      if ((int)(uVar15 << 0x1f) < 0) {
        iVar11 = *(int *)(iVar5 + 0x14);
        bVar14 = *(byte *)(iVar11 + 3);
        iVar18 = FUN_0100d3c0(iVar18 + 0xa8,5,*(undefined1 *)(iVar18 + 0xc6),1);
        if ((iVar18 != 0) &&
           ((uVar15 = bVar14 - 2 & 0xff, 9 < uVar15 || ((1 << uVar15 & 0x333U) == 0)))) {
          iVar18 = *(int *)(iVar5 + 4);
          uVar12 = 8;
          goto LAB_01014bdc;
        }
        iVar18 = controller_packet_length_matches_type(iVar11);
        if (iVar18 == 0) {
LAB_010153de:
          uVar12 = controller_procedure_slot_reserve(DAT_0101561c,iVar11);
        }
        else {
          uVar15 = (uint)*(byte *)(iVar11 + 3);
          if ((uVar15 < 2) || (uVar15 == 0x16)) {
            iVar18 = FUN_0100f7e0(*(undefined1 *)(*(int *)(iVar5 + 4) + 0xc5));
            if (iVar18 != 0) {
              iVar18 = *(int *)(iVar5 + 4);
              if (*(int8_t *)(iVar18 + 0xc5) != '!') {
                if (*(int8_t *)(iVar18 + 0xc5) != '\"') {
                  if (uVar15 == 0x16) {
                    uVar12 = 0x20;
                  }
                  else {
                    uVar12 = 2;
                  }
                  goto LAB_01014bdc;
                }
                *(undefined1 *)(iVar18 + 0xc5) = 0x2f;
              }
            }
          }
          else if (0x2a < uVar15) {
            if ((uVar15 == 0xff) && (*(int *)(iVar5 + 8) != 0)) {
              *(undefined1 *)(*(int *)(iVar5 + 4) + 0x3b6) = 1;
              uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
              goto LAB_01014f3c;
            }
            goto LAB_010153de;
          }
          pcVar17 = *(code **)(DAT_01015620 + uVar15 * 4);
          if (pcVar17 == (code *)0x0) goto LAB_010153de;
          uVar12 = (*pcVar17)(DAT_0101561c,*(undefined4 *)(iVar5 + 0x14));
        }
        if (uVar12 != 0) {
          iVar18 = *(int *)(iVar5 + 4);
          goto LAB_01014bdc;
        }
        uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
      }
LAB_01014f3c:
      if (((int)(uVar15 << 0x1d) < 0) && (*(int8_t *)(*(int *)(iVar5 + 4) + 199) == '\a')) {
        *(undefined1 *)(iVar5 + 0x1c) = 1;
      }
      if ((int)(uVar15 << 0x1e) < 0) {
        uVar12 = (uint)*(byte *)(*(int *)(iVar5 + 0x10) + 3);
        if (uVar12 < 0x2b) {
          pcVar17 = *(code **)(DAT_010151c8 + uVar12 * 4);
          if (pcVar17 == (code *)0x0) {
LAB_01015316:
                    /* WARNING: Subroutine does not return */
            fatal(0x31,0x57c);
          }
          (*pcVar17)(DAT_010151cc);
          uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
          iVar18 = *(int *)(iVar5 + 4);
        }
        else {
          if (uVar12 != 0xff) goto LAB_01015316;
          iVar18 = *(int *)(iVar5 + 4);
          *(undefined1 *)(iVar18 + 0xc5) = 0x32;
          *(undefined1 *)(iVar18 + 0x3b4) = 0;
        }
      }
      else {
        iVar18 = *(int *)(iVar5 + 4);
      }
      uVar12 = uVar15 & 0x10;
      if ((uVar15 & 0x10) != 0) {
        if (*(int8_t *)(iVar18 + 0xc6) == '\v') {
          *(undefined1 *)(iVar18 + 0xc6) = 0xc;
          uVar12 = 0;
        }
        else {
          uVar12 = 0;
        }
      }
    }
LAB_01014bdc:
    if ((int)((uint)*(byte *)(iVar5 + 0x18) << 0x1c) < 0) {
      iVar18 = FUN_0100d3c0(iVar18 + 0xa8,5,*(undefined1 *)(iVar18 + 0xc6),1);
      if (iVar18 == 0) {
        uStack_34 = iVar18;
        FUN_0100b630(3,&uStack_34);
        if (uStack_34 != 0) {
          *(undefined1 *)(uStack_34 + 8) = 0;
          sdc_work_submit(uStack_34,*(undefined4 *)(iVar5 + 4),0x10);
        }
        iVar18 = *(int *)(iVar5 + 4);
      }
      else {
        iVar18 = *(int *)(iVar5 + 4);
        uVar12 = 8;
      }
    }
    param_2 = (param_2 | uVar12) & 0xff;
    if (*(int *)(iVar5 + 8) != 0) {
      uStack_34 = 0;
      uStack_30 = 0;
      uStack_2c = 0;
      pcStack_28 = (int8_t *)0x0;
      uStack_24 = 0;
      iVar18 = radio_phy_airtime_base_get(*(undefined1 *)(iVar18 + 0x6f));
      sVar8 = radio_phy_airtime_tail_get(*(undefined1 *)(*(int *)(iVar5 + 4) + 0x6f));
      puVar16 = *(undefined2 **)(iVar5 + 4);
      uStack_34 = (uStack_34 & 0xffff0000u) | *puVar16;
      uStack_30 = ((uint32_t)(uint16_t)(sVar8 + (short)(uint)
    ((ulonglong)DAT_01014df0 * (ulonglong)(iVar18 + 500) >> 0x26)) << 16) |
    puVar16[0x5e];
      uVar9 = FUN_0100d5d0(*(undefined4 *)(puVar16 + 10));
      iVar18 = *(int *)(iVar5 + 4);
      uStack_34 = ((uint32_t)uVar9 << 16) | (uint16_t)uStack_34;
      if (*(int8_t *)(iVar18 + 0x3b6) != '\0') {
        pcStack_28 = (int8_t *)(*(int *)(iVar5 + 0x14) + 3);
        uVar6 = FUN_0100e5d8();
        iVar18 = *(int *)(iVar5 + 4);
        uStack_24 = (uStack_24 & 0xffffff00u) | uVar6;
      }
      uStack_2c = (uStack_2c & 0xffffff00u) |
        ((byte)uStack_2c & 0xfeu) | (*(byte *)(iVar18 + 0x3b5) & 1u);
      (**(code **)(iVar5 + 8))(&uStack_34);
      iVar18 = *(int *)(iVar5 + 4);
      *(undefined2 *)(iVar18 + 0x3b5) = 0;
      if (((pcStack_28 != (int8_t *)0x0) && (*(int8_t *)(iVar18 + 0x3b4) == '\0')) &&
         (*(int8_t *)(iVar18 + 0xc5) != '2')) {
        uVar15 = uStack_24 & 0xff;
        if (uVar15 != 0) {
          if (*pcStack_28 == -1) {
            if (uVar15 < 0x1c) goto LAB_01014c94;
          }
          else if (((*pcStack_28 == '\a') && (uVar15 == 2)) && (pcStack_28[1] == -1)) {
LAB_01014c94:
            *(int8_t **)(iVar18 + 0x3b8) = pcStack_28;
            *(undefined1 *)(iVar18 + 0x3b7) = (undefined1)uStack_24;
            *(undefined1 *)(iVar18 + 0x3b4) = 1;
          }
        }
      }
    }
    if ((*(int8_t *)(iVar18 + 0x14e) == -2) && (param_2 == 0)) {
      iVar11 = FUN_0100d3c0(iVar18 + 0xa8,1,*(undefined1 *)(iVar18 + 199),1);
      iVar18 = *(int *)(iVar5 + 4);
      if (iVar11 == 0) {
        if (*(int8_t *)(iVar18 + 0x160) == '\0') {
          iVar11 = FUN_0100d3c0(iVar18 + 0xa8,4,*(undefined1 *)(iVar18 + 0xc6),1);
          iVar18 = *(int *)(iVar5 + 4);
          uVar9 = (undefined2)iVar11;
          if (iVar11 == 0) {
            uVar15 = *(uint *)(iVar18 + 0xb4);
            if ((uVar15 & 1) == 0) {
              if ((uVar15 & 2) == 0) {
                if ((int)(uVar15 << 0x1d) < 0) {
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  *(undefined2 *)(iVar18 + 0x102) = 0;
                  *(undefined1 *)(iVar18 + 0x14e) = 0x13;
                }
                else if ((int)(uVar15 << 0x1c) < 0) {
                  *(undefined1 *)(iVar18 + 0x150) = *(undefined1 *)(iVar18 + 0x148);
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  *(undefined1 *)(iVar18 + 0x14e) = 7;
                  *(undefined2 *)(iVar18 + 0x102) = 0;
                }
                else if ((int)(uVar15 << 0x18) < 0) {
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  *(undefined1 *)(iVar18 + 0x14e) = 0x1b;
                  *(undefined2 *)(iVar18 + 0x102) = 0;
                }
                else if ((uVar15 & 0x30) == 0) {
                  if ((uVar15 & 0x40) == 0) {
                    if (-1 < (int)(uVar15 << 0x17)) goto LAB_0101574c;
                    if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                    *(undefined2 *)(iVar18 + 0x102) = 0;
                    *(undefined1 *)(iVar18 + 0x14e) = 0x1e;
                  }
                  else {
                    if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                    *(undefined2 *)(iVar18 + 0x102) = 0;
                    *(undefined1 *)(iVar18 + 0x14e) = 0x24;
                  }
                }
                else {
                  if (*(int8_t *)(iVar18 + 0x163) == '\0') {
                    if (*(int8_t *)(iVar18 + 0x162) != '\0') {
                      if (*(int8_t *)(iVar18 + 0xc6) == '&') {
                        bVar19 = true;
                      }
                      else {
                        bVar19 = *(int8_t *)(iVar18 + 0xc5) == '&';
                      }
                      FUN_0100f110(iVar18,iVar18 + 0x162,iVar18 + 0x3be,bVar19);
                      iVar18 = *(int *)(iVar5 + 4);
                      *(uint *)(iVar18 + 0xb4) = *(uint *)(iVar18 + 0xb4) & 0xffffffdf | 0x10;
                      *(undefined1 *)(iVar18 + 0x162) = 0;
                    }
                    if (*(int *)(*(int *)(iVar5 + 4) + 0xb4) << 0x1b < 0) {
                      controller_timing_windows_clamp();
                      FUN_0100fae4(DAT_01015ca0);
                      iVar18 = *(int *)(iVar5 + 4);
                      *(undefined2 *)(iVar18 + 0x150) = *(undefined2 *)(iVar18 + 0x4e);
                      *(undefined2 *)(iVar18 + 0x152) = *(undefined2 *)(iVar18 + 0x52);
                      if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                      *(undefined1 *)(iVar18 + 0x14e) = 0x15;
                      *(undefined2 *)(iVar18 + 0x102) = 0;
                      goto LAB_01014cb0;
                    }
                  }
LAB_0101574c:
                  iVar18 = *(int *)(iVar5 + 4);
                  cVar7 = *(int8_t *)(iVar18 + 0xc6);
                  if (cVar7 == '+') {
                    if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                    *(undefined1 *)(iVar18 + 0x14e) = 0x20;
                    *(undefined2 *)(iVar18 + 0x102) = 0;
                  }
                  else if (cVar7 == '0') {
                    if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                    *(undefined1 *)(iVar18 + 0x14e) = 0x11;
                    *(undefined2 *)(iVar18 + 0x102) = 0;
                  }
                  else {
                    if ((cVar7 != '#') ||
                       ((*(int8_t *)(iVar18 + 0x16c) != '\x02' &&
                        ((*(int8_t *)(iVar18 + 0x16c) != '\x01' || (*(int8_t *)(iVar18 + 0x16d) != '\0')
                         ))))) goto switchD_010154a4_caseD_13;
                    if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                    *(undefined1 *)(iVar18 + 0x14e) = 0x17;
                    *(undefined2 *)(iVar18 + 0x102) = 0;
                  }
                }
              }
              else {
                if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                *(undefined2 *)(iVar18 + 0x102) = 0;
                *(byte *)(iVar18 + 0x107) = *(byte *)(iVar18 + 0x107) | 1;
                *(undefined1 *)(iVar18 + 0x14e) = 0xc;
              }
            }
            else {
              if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
              *(undefined2 *)(iVar18 + 0x102) = uVar9;
              *(undefined1 *)(iVar18 + 0x14e) = 9;
            }
          }
          else {
            switch(*(undefined1 *)(iVar18 + 0xc6)) {
            case 0x12:
              if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
              *(undefined1 *)(iVar18 + 0x14e) = 0xb;
              *(undefined2 *)(iVar18 + 0x102) = 0;
              break;
            default:
switchD_010154a4_caseD_13:
              iVar18 = FUN_0100d3c0(*(int *)(iVar5 + 4) + 0xa8,0,
                                    *(undefined1 *)(*(int *)(iVar5 + 4) + 0xc5),1);
              if ((iVar18 == 0) ||
                 ((iVar18 = FUN_0100d3c0(*(int *)(iVar5 + 4) + 0xa8,4,
                                         *(undefined1 *)(*(int *)(iVar5 + 4) + 0xc6),1), iVar18 != 0
                  || (iVar18 = *(int *)(iVar5 + 4), *(int8_t *)(iVar18 + 0xf4) == '\0')))) {
                iVar18 = *(int *)(iVar5 + 4);
                if (*(int8_t *)(iVar18 + 0xc5) == '\n') {
                  *(undefined1 *)(iVar18 + 0x150) = *(undefined1 *)(iVar18 + 0x149);
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  uVar6 = 7;
LAB_0101567a:
                  *(undefined1 *)(iVar18 + 0x14e) = uVar6;
                  *(undefined2 *)(iVar18 + 0xfc) = 0;
                  *(undefined1 *)(iVar18 + 0x100) = 1;
                }
                else if (iVar11 == 0) {
                  iVar18 = FUN_0100d3c0(iVar18 + 0xa8,0,*(int8_t *)(iVar18 + 0xc5),1);
                  if (iVar18 == 0) goto LAB_0101580c;
                  iVar18 = *(int *)(iVar5 + 4);
                  if (*(int8_t *)(iVar18 + 0x173) == '\0') {
                    if ((*(int8_t *)(iVar18 + 0x172) == '\0') ||
                       ((*(byte *)(iVar18 + 0x107) & 3) != 0)) {
                      if ((*(int8_t *)(iVar18 + 0x162) == '\0') || (*(int8_t *)(iVar18 + 0x163) != '\0')
                         ) {
                        if (((*(int8_t *)(iVar18 + 0x16c) == '\x01') &&
                            (*(int8_t *)(iVar18 + 0x16d) == '\0')) &&
                           (iVar18 = FUN_0100d3c0(iVar18 + 0xa8,0xb,*(undefined1 *)(iVar18 + 0xc6),1
                                                 ), iVar18 == 0)) {
                          iVar18 = *(int *)(iVar5 + 4);
                          switch(*(undefined1 *)(iVar18 + 0x6e)) {
                          case 1:
                            switch(*(undefined1 *)(iVar18 + 0x6f)) {
                            case 1:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x01') {
LAB_01015b3a:
                                if (*(int8_t *)(iVar18 + 0x16f) == '\x01') {
LAB_01015b42:
                                  iVar18 = FUN_01029882(*(undefined2 *)(iVar18 + 0x170),
                                                        *(undefined1 *)(iVar18 + 0x6e),
                                                        iVar18 + 0x3bc,
                                                        *(undefined2 *)(iVar18 + 0xbc));
                                  if (iVar18 == 0) {
                                    FUN_0101f934(DAT_01015ca0,0);
                                    goto LAB_0101580c;
                                  }
                                  iVar18 = *(int *)(iVar5 + 4);
                                  *(undefined1 *)(iVar18 + 0xc5) = 0x28;
                                  goto LAB_01014cb0;
                                }
                              }
                              break;
                            case 2:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x01') {
LAB_01015b6a:
                                if (*(int8_t *)(iVar18 + 0x16f) == '\x02') goto LAB_01015b42;
                              }
                              break;
                            default:
                              goto switchD_01015a2c_caseD_3;
                            case 4:
                            case 8:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x01') {
LAB_01015bdc:
                                if (*(int8_t *)(iVar18 + 0x16f) == '\x04') goto LAB_01015b42;
                              }
                            }
                            break;
                          case 2:
                            switch(*(undefined1 *)(iVar18 + 0x6f)) {
                            case 1:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x02') goto LAB_01015b3a;
                              break;
                            case 2:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x02') goto LAB_01015b6a;
                              break;
                            default:
                              goto switchD_01015a2c_caseD_3;
                            case 4:
                            case 8:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x02') goto LAB_01015bdc;
                            }
                            break;
                          default:
switchD_01015a2c_caseD_3:
                    /* WARNING: Subroutine does not return */
                            fatal(6,0x294);
                          case 4:
                          case 8:
                            switch(*(undefined1 *)(iVar18 + 0x6f)) {
                            case 1:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x04') goto LAB_01015b3a;
                              break;
                            case 2:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x04') goto LAB_01015b6a;
                              break;
                            default:
                              goto switchD_01015a2c_caseD_3;
                            case 4:
                            case 8:
                              if (*(int8_t *)(iVar18 + 0x16e) == '\x04') goto LAB_01015bdc;
                            }
                          }
                          iVar18 = FUN_0100d3c0(iVar18 + 0xa8,3,*(undefined1 *)(iVar18 + 0xc6),1);
                          if ((iVar18 != 0) ||
                             (iVar18 = FUN_0100d3c0(*(int *)(iVar5 + 4) + 0xa8,2,
                                                    *(undefined1 *)(*(int *)(iVar5 + 4) + 0xc6),1),
                             iVar18 != 0)) goto LAB_0101580c;
                          iVar18 = *(int *)(iVar5 + 4);
                          if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                          *(undefined2 *)(iVar18 + 0xfc) = 0;
                          *(undefined1 *)(iVar18 + 0x14e) = 0x16;
                          *(undefined1 *)(iVar18 + 0x100) = 1;
                        }
                        else {
                          iVar18 = *(int *)(iVar5 + 4);
                          if (*(int8_t *)(iVar18 + 0x1a9) != '\0') {
                            if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                            uVar6 = 0x23;
                            goto LAB_0101567a;
                          }
                          if (*(int8_t *)(iVar18 + 0x1a6) == '\0') {
                            if (*(int8_t *)(iVar18 + 0x1aa) == '\0') {
                              if (*(int8_t *)(iVar18 + 0x174) == '\0') {
                                if (*(int8_t *)(iVar18 + 0x1b2) == '\0') {
LAB_0101580c:
                                  iVar11 = FUN_0100d3c0(*(int *)(iVar5 + 4) + 0xa8,0,
                                                        *(undefined1 *)(*(int *)(iVar5 + 4) + 0xc5),
                                                        1);
                                  iVar18 = *(int *)(iVar5 + 4);
                                  if ((iVar11 != 0) && (*(int8_t *)(iVar18 + 0x3b4) != '\0')) {
                                    if (*(int8_t *)(iVar18 + 0x14e) != -2) {
LAB_01015c18:
                    /* WARNING: Subroutine does not return */
                                      FUN_01014884();
                                    }
                                    uVar6 = 0xff;
                                    goto LAB_0101567a;
                                  }
                                }
                                else {
                                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                                  *(undefined2 *)(iVar18 + 0xfc) = 0;
                                  *(undefined1 *)(iVar18 + 0x14e) = 0x1d;
                                  *(undefined1 *)(iVar18 + 0x100) = 1;
                                }
                              }
                              else {
                                iVar18 = FUN_01016250(*(undefined1 *)(iVar18 + 0x178));
                                iVar11 = *(int *)(iVar5 + 4);
                                if (iVar18 == 0) {
                                  iVar18 = (*(code *)*DAT_01015ca4)
                                                     (DAT_01015ca0,iVar11 + 0x179,iVar11 + 0x19b,
                                                      *(undefined1 *)(iVar11 + 0x178));
                                }
                                else {
                                  iVar18 = (*(code *)*DAT_01015aa8)
                                                     (DAT_01015aac,iVar11 + 0x179,
                                                      *(undefined1 *)(iVar11 + 0x178));
                                }
                                if (iVar18 != 0) {
                                  if (iVar18 == 2) {
                                    *(undefined1 *)(*(int *)(iVar5 + 4) + 0x174) = 0;
                                  }
                                  goto LAB_0101580c;
                                }
                                iVar11 = FUN_01016250(*(undefined1 *)(*(int *)(iVar5 + 4) + 0x178));
                                iVar18 = *(int *)(iVar5 + 4);
                                if (iVar11 == 0) {
                                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                                  *(undefined2 *)(iVar18 + 0xfc) = 0;
                                  *(undefined1 *)(iVar18 + 0x14e) = 0x2a;
                                  *(undefined1 *)(iVar18 + 0x100) = 1;
                                }
                                else {
                                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                                  *(undefined2 *)(iVar18 + 0xfc) = 0;
                                  *(undefined1 *)(iVar18 + 0x14e) = 0x1c;
                                  *(undefined1 *)(iVar18 + 0x100) = 1;
                                }
                              }
                            }
                            else {
                              if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                              *(undefined2 *)(iVar18 + 0xfc) = 0;
                              *(undefined1 *)(iVar18 + 0x14e) = 0x22;
                              *(undefined1 *)(iVar18 + 0x100) = 1;
                            }
                          }
                          else {
                            if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                            *(undefined2 *)(iVar18 + 0xfc) = 0;
                            *(undefined1 *)(iVar18 + 0x14e) = 0x25;
                            *(undefined1 *)(iVar18 + 0x100) = 1;
                            *(undefined1 *)(iVar18 + 0x1a6) = 0;
                            iVar18 = *(int *)(iVar5 + 4);
                          }
                        }
                      }
                      else {
                        if (*(int8_t *)(iVar18 + 0xc6) == '&') {
                          bVar19 = true;
                        }
                        else {
                          bVar19 = *(int8_t *)(iVar18 + 0xc5) == '&';
                        }
                        FUN_0100f110(iVar18,iVar18 + 0x162,iVar18 + 0x3be,bVar19);
                        iVar18 = *(int *)(iVar5 + 4);
                        *(undefined1 *)(*(int *)(iVar5 + 4) + 0x162) = 0;
                        if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                        *(undefined2 *)(iVar18 + 0xfc) = 0;
                        *(undefined1 *)(iVar18 + 0x14e) = 0x14;
                        *(undefined1 *)(iVar18 + 0x100) = 1;
                        *(undefined2 *)(iVar18 + 0x150) = *(undefined2 *)(iVar18 + 0x4e);
                        *(undefined2 *)(iVar18 + 0x152) = *(undefined2 *)(iVar18 + 0x52);
                      }
                    }
                    else {
                      if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                      *(undefined2 *)(iVar18 + 0xfc) = uVar9;
                      *(undefined1 *)(iVar18 + 0x172) = 0;
                      *(byte *)(iVar18 + 0x107) = *(byte *)(iVar18 + 0x107) | 1;
                      *(undefined1 *)(iVar18 + 0x14e) = 0xc;
                      *(undefined1 *)(iVar18 + 0x100) = 1;
                    }
                  }
                  else {
                    if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                    *(undefined2 *)(iVar18 + 0xfc) = uVar9;
                    *(undefined1 *)(iVar18 + 0x173) = 0;
                    *(undefined1 *)(iVar18 + 0x14e) = 0xe;
                    *(undefined1 *)(iVar18 + 0x100) = 1;
                  }
                }
              }
              else {
                if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                *(undefined2 *)(iVar18 + 0xfc) = 0;
                *(undefined1 *)(iVar18 + 0x14e) = 0x12;
                *(undefined1 *)(iVar18 + 0x100) = 1;
              }
              break;
            case 0x16:
              bVar14 = *(byte *)(iVar18 + 0x154);
              if (bVar14 < 8) {
                cVar7 = FUN_010091f8(iVar18 + (byte)(bVar14 + 8) + 0x2f8,'\b' - bVar14);
                *(int8_t *)(*(int *)(iVar5 + 4) + 0x154) =
                     *(int8_t *)(*(int *)(iVar5 + 4) + 0x154) + cVar7;
              }
              uVar15 = (uint)*(byte *)(*(int *)(iVar5 + 4) + 0x154);
              uVar12 = uVar15 - 8 & 0xff;
              if (uVar12 < 4) {
                cVar7 = FUN_010091f8(*(int *)(iVar5 + 4) + uVar15 + 0x13c,4 - uVar12 & 0xff);
                *(int8_t *)(*(int *)(iVar5 + 4) + 0x154) =
                     *(int8_t *)(*(int *)(iVar5 + 4) + 0x154) + cVar7;
              }
              iVar18 = *(int *)(iVar5 + 4);
              if (0xb < *(byte *)(iVar18 + 0x154)) {
                if (*(byte *)(iVar18 + 0x154) != 0xc) {
                    /* WARNING: Subroutine does not return */
                  fatal(0x31,0x5f6);
                }
                *(undefined1 *)(iVar18 + 0x154) = 0;
                if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                *(undefined2 *)(iVar18 + 0x102) = 0;
                *(undefined1 *)(iVar18 + 0x14e) = 4;
              }
              break;
            case 0x17:
              if (*(int8_t *)(iVar18 + 0x3a0) == '\x01') {
                if (*(int8_t *)(iVar18 + 0x2c0) == '\0') {
                  FUN_010108b8(iVar18 + 0x3a1,iVar18 + 0x2f8,0,iVar18 + 0x130);
                  iVar18 = *(int *)(iVar5 + 4);
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  *(undefined2 *)(iVar18 + 0x102) = 0;
                  *(undefined1 *)(iVar18 + 0x3a0) = 0;
                  *(undefined1 *)(iVar18 + 0x14e) = 5;
                }
              }
              else if (*(int8_t *)(iVar18 + 0x3a0) == '\x02') {
                if (*(int8_t *)(iVar18 + 0x106) == '\0') {
                  FUN_0100f7d0(DAT_01015aac,3);
                  iVar18 = *(int *)(iVar5 + 4);
                  if ((*(byte *)(iVar18 + 0x116) & 4) == 0) {
                    uVar6 = 0xd;
                  }
                  else {
                    uVar6 = 0x11;
                  }
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  *(undefined1 *)(iVar18 + 0x14e) = uVar6;
                  *(undefined2 *)(iVar18 + 0x102) = 0;
                }
                else {
                  *(undefined1 *)(iVar18 + 0x150) = 6;
                  if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
                  *(undefined1 *)(iVar18 + 0x14e) = 2;
                  *(undefined2 *)(iVar18 + 0x102) = 0;
                }
                iVar18 = *(int *)(iVar5 + 4);
                *(undefined1 *)(iVar18 + 0x3a0) = 0;
              }
              break;
            case 0x1d:
              if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
              *(undefined1 *)(iVar18 + 0x14e) = 6;
              *(undefined2 *)(iVar18 + 0x102) = 0;
            }
          }
        }
        else {
          *(undefined2 *)(iVar18 + 0xfa) = 0;
          *(undefined1 *)(iVar18 + 0x150) = *(undefined1 *)(iVar18 + 0x161);
          if (*(int8_t *)(iVar18 + 0x14e) != -2) goto LAB_01015c18;
          *(undefined2 *)(iVar18 + 0xfc) = 0;
          *(undefined1 *)(iVar18 + 0x14e) = 2;
          *(undefined1 *)(iVar18 + 0x100) = 1;
        }
      }
    }
LAB_01014cb0:
    *(short *)(iVar18 + 0x2e8) = *(short *)(iVar18 + 0x2e8) + 1;
    if (*(int8_t *)(iVar18 + 0x2ec) == '\0') {
      iVar11 = FUN_0100b608();
      if ((iVar11 != 0) && (*(int8_t *)(*(int *)(iVar5 + 4) + 0x2ee) == '\0')) {
        *(undefined2 *)(iVar18 + 0x2e8) = 0;
      }
      iVar11 = FUN_0100b624();
      if ((iVar11 != 0) &&
         (bVar14 = *(int8_t *)(iVar18 + 0x2f4) + 1, *(byte *)(iVar18 + 0x2f4) = bVar14, 2 < bVar14)) {
        *(undefined2 *)(iVar18 + 0x2e8) = 0;
        *(undefined1 *)(iVar18 + 0x2f4) = 0;
      }
    }
    else {
      iVar11 = FUN_0100b614();
      if (iVar11 != 0) {
        *(undefined2 *)(iVar18 + 0x2e8) = 0;
      }
    }
    iVar11 = FUN_0100d3c0(*(int *)(iVar5 + 4) + 0xa8,0,*(undefined1 *)(*(int *)(iVar5 + 4) + 0xc6),1
                         );
    iVar18 = *(int *)(iVar5 + 4);
    if ((iVar11 == 0) && (*(int8_t *)(iVar18 + 0xc6) != '\f')) {
LAB_01014cf0:
      uVar15 = (uint)*(byte *)(iVar18 + 0xc9);
LAB_01014cf4:
      *(undefined1 *)(iVar18 + 0x2ea) = 0;
      sVar8 = 1;
LAB_01014cfc:
      *(undefined1 *)(iVar18 + 0x2ee) = 0;
    }
    else {
      iVar18 = FUN_0100d3c0(iVar18 + 0xa8,0,*(undefined1 *)(iVar18 + 0xc5),1);
      if (iVar18 == 0) {
        iVar18 = *(int *)(iVar5 + 4);
        uVar15 = (uint)*(byte *)(iVar18 + 0xc9);
        goto LAB_01014cf4;
      }
      iVar11 = FUN_0100d3c0(*(int *)(iVar5 + 4) + 0xa8,0,*(undefined1 *)(*(int *)(iVar5 + 4) + 199),
                            1);
      iVar18 = *(int *)(iVar5 + 4);
      uVar15 = (uint)*(byte *)(iVar18 + 0xc9);
      if (((iVar11 == 0) || (uVar15 != 2)) || (*(int8_t *)(iVar18 + 0x2f4) != '\0'))
      goto LAB_01014cf4;
      iVar10 = FUN_01026d16(iVar10);
      iVar18 = *(int *)(iVar5 + 4);
      if (((iVar10 == 0) || (*(int8_t *)(iVar18 + 0x14e) != -2)) || (*(ushort *)(iVar18 + 0x2e2) < 2))
      goto LAB_01014cf0;
      *(undefined1 *)(iVar18 + 0x2ea) = 1;
      if ((int)(*(ushort *)(iVar18 + 0xf8) - 2) <= (int)(uint)*(ushort *)(iVar18 + 0xf6)) {
        uVar2 = *(ushort *)(iVar18 + 0x2e8);
        uVar1 = *(ushort *)(iVar5 + 0x1a);
        if (uVar2 < uVar1) {
          uVar15 = 1;
          goto LAB_010156c2;
        }
LAB_010156ca:
        *(undefined1 *)(iVar18 + 0x2ea) = 0;
        if (*(int8_t *)(iVar18 + 0x7b) == '\0') {
          uVar12 = 1;
          if (*(int *)(iVar18 + 0x74) != 0) goto LAB_01015054;
          goto LAB_010156e4;
        }
        uVar15 = (uint)*(byte *)(iVar18 + 0xc9);
        sVar8 = 1;
        goto LAB_01014cfc;
      }
      uVar2 = *(ushort *)(iVar18 + 0x2e8);
      uVar1 = *(ushort *)(iVar5 + 0x1a);
      uVar15 = (*(ushort *)(iVar18 + 0xf8) - 1) - (uint)*(ushort *)(iVar18 + 0xf6) & 0xffff;
      if (uVar2 < uVar1) {
LAB_010156c2:
        uVar12 = (uint)(ushort)((uVar1 + 1) - uVar2);
      }
      else {
        uVar12 = 1;
      }
      if (uVar15 <= uVar12) {
        uVar12 = uVar15;
      }
      if (uVar12 == 1) goto LAB_010156ca;
      if ((*(int8_t *)(iVar18 + 0x7b) == '\0') && (*(int *)(iVar18 + 0x74) != 0)) {
LAB_01015054:
        uVar1 = *(short *)(iVar18 + 0xf2) - *(short *)(iVar18 + 0xbc);
        if ((0 < (short)uVar1) && ((int)(short)uVar1 <= (int)uVar12)) {
          uVar12 = (uint)uVar1;
        }
      }
      if ((*(int8_t *)(iVar5 + 0x1d) == '\0') || (uVar12 < 2)) {
LAB_010156e4:
        sVar8 = (short)uVar12;
        uVar15 = (uint)*(byte *)(iVar18 + 0xc9);
        goto LAB_01014cfc;
      }
      sVar8 = 1;
      uVar15 = (uint)*(byte *)(iVar18 + 0xc9);
      *(undefined1 *)(iVar18 + 0x2ee) = 1;
    }
    sVar8 = sVar8 + *(short *)(iVar18 + 0xbc);
    *(short *)(iVar18 + 0x2e4) = sVar8;
    if (uVar15 < 2) {
LAB_01014d14:
      uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
      *(short *)(iVar18 + 0x2e0) = sVar8;
      goto LAB_01014d1a;
    }
    if (1 < uVar15 - 2) {
                    /* WARNING: Subroutine does not return */
      fatal(0x31,0x952);
    }
    if (*(int8_t *)(iVar18 + 199) == '\b') {
      if (2 < *(ushort *)(iVar18 + 0xf6)) {
        uVar15 = (uint)*(ushort *)(iVar5 + 0xc);
        *(short *)(iVar18 + 0x2e0) = *(short *)(iVar18 + 0xbc) + *(short *)(iVar18 + 0xf8) + 1;
        goto LAB_01014d1a;
      }
      goto LAB_01014d14;
    }
    if ((*(ushort *)(iVar18 + 0xf6) + 1 < (uint)*(ushort *)(iVar18 + 0xf8)) &&
       (uVar15 = (uint)*(ushort *)(iVar18 + 0xf8) - (uint)*(ushort *)(iVar18 + 0xf6) & 0xffff,
       uVar15 != 2)) {
      uVar15 = uVar15 - 3 & 0xffff;
    }
    else {
      uVar15 = 0;
    }
    if (*(int8_t *)(iVar18 + 0xf4) == '\0') {
LAB_010150be:
      if (*(int8_t *)(iVar18 + 0xcb) == '\0') {
        iVar10 = FUN_0100d3c0(iVar18 + 0xa8,6,*(undefined1 *)(iVar18 + 0xc6),1);
        iVar18 = *(int *)(iVar5 + 4);
        if (iVar10 != 0) goto LAB_010150c8;
      }
      else {
LAB_010150c8:
        if ((*(uint *)(iVar18 + 0xec) < *(int *)(iVar18 + 0xe8) + 2U) ||
           (iVar10 = *(uint *)(iVar18 + 0xec) - *(int *)(iVar18 + 0xe8), iVar10 == 2)) {
          uVar12 = 0;
        }
        else {
          uVar12 = iVar10 - 3;
        }
        if (uVar12 < uVar15) {
          uVar15 = uVar12 & 0xffff;
        }
      }
      sVar8 = (short)uVar15;
      if (uVar15 != 0) {
        sVar8 = sVar8 + -1;
      }
    }
    else {
      iVar10 = FUN_0100d3c0(iVar18 + 0xa8,9,*(undefined1 *)(iVar18 + 0xc5),1);
      iVar18 = *(int *)(iVar5 + 4);
      if (iVar10 != 0) goto LAB_010150be;
      sVar8 = 0;
    }
    *(short *)(iVar18 + 0x2e0) = *(short *)(iVar18 + 0x2e4) + sVar8;
    if (-1 < (int)((uint)*(ushort *)(iVar5 + 0xc) << 0x19)) goto LAB_01014eb4;
LAB_01014d20:
    *(undefined2 *)(iVar18 + 0x2f6) = 0;
    if (*(int8_t *)(iVar18 + 0x160) != '\0') goto LAB_01014d30;
LAB_01014ecc:
    iVar10 = FUN_0100d3c0(iVar18 + 0xa8,1,*(undefined1 *)(iVar18 + 199),1);
    iVar18 = *(int *)(iVar5 + 4);
    if (iVar10 != 0) goto LAB_01014d30;
  }
  else {
LAB_01014d1a:
    if ((int)(uVar15 << 0x19) < 0) goto LAB_01014d20;
LAB_01014eb4:
    *(short *)(iVar18 + 0x2f6) = *(short *)(iVar18 + 0x2f6) + *(short *)(iVar18 + 0x2e6);
    if (*(int8_t *)(iVar18 + 0x160) == '\0') goto LAB_01014ecc;
LAB_01014d30:
    *(short *)(iVar18 + 0xfa) = *(short *)(iVar18 + 0xfa) + *(short *)(iVar18 + 0x2e6);
  }
  if (*(int8_t *)(iVar18 + 0x100) != '\0') {
    *(short *)(iVar18 + 0xfc) = *(short *)(iVar18 + 0xfc) + *(short *)(iVar18 + 0x2e6);
  }
  if ('\0' < *(int8_t *)(iVar18 + 0x104)) {
    *(short *)(iVar18 + 0x102) = *(short *)(iVar18 + 0x102) + *(short *)(iVar18 + 0x2e6);
  }
  cVar7 = *(int8_t *)(iVar18 + 0xe5);
  if (cVar7 == '\0') {
    if (param_1 == 0) {
      if (*(int8_t *)(iVar5 + 0x1c) == '\x02') {
        cVar7 = *(int8_t *)(iVar18 + 0x150);
        if (cVar7 != '\x06') {
          cVar7 = '\x16';
        }
      }
      else if (*(int8_t *)(iVar5 + 0x1c) == '\x01') {
        cVar7 = *(int8_t *)(iVar18 + 200);
        if (cVar7 == '\0') goto LAB_010150ea;
      }
      else if (param_2 == 0) {
        if ((((*(int8_t *)(iVar18 + 0x100) == '\0') ||
             (*(ushort *)(iVar18 + 0xfc) < *(ushort *)(iVar18 + 0xfe))) &&
            ((*(int8_t *)(iVar18 + 0x104) < '\x01' ||
             (*(ushort *)(iVar18 + 0x102) < *(ushort *)(iVar18 + 0xfe))))) &&
           ((*(ushort *)(iVar18 + 0xfa) < *(ushort *)(iVar18 + 0xf8) ||
            (*(int8_t *)(iVar18 + 0x160) == '\0')))) {
          if (*(int8_t *)(iVar18 + 0xc9) == '\0') {
            if (*(ushort *)(iVar18 + 0xf6) < 6) goto LAB_010150ea;
            cVar7 = '>';
          }
          else {
            if (*(ushort *)(iVar18 + 0xf6) < *(ushort *)(iVar18 + 0xf8)) {
LAB_010150ea:
              FUN_01013e98(iVar18,0);
              goto LAB_01014dc8;
            }
            cVar7 = '\b';
          }
        }
        else {
          cVar7 = '\"';
        }
      }
      else if ((int)(param_2 << 0x1b) < 0) {
        cVar7 = '\x1e';
      }
      else {
        if ((int)(param_2 << 0x1c) < 0) goto LAB_01014f20;
        if ((int)(param_2 << 0x1a) < 0) {
          cVar7 = '#';
        }
        else {
          if ((param_2 & 3) == 0) {
                    /* WARNING: Subroutine does not return */
            fatal(0x31,0xadd);
          }
          cVar7 = '*';
        }
      }
    }
    else {
LAB_01014f20:
      cVar7 = '=';
    }
  }
  if (*(int8_t *)(iVar18 + 0xe4) == '\0') {
    *(int8_t *)(iVar18 + 0xe5) = cVar7;
    sdc_work_submit(iVar18 + 0xdc,DAT_010151c4,2);
    iVar18 = *(int *)(iVar5 + 4);
  }
  *(undefined2 *)(iVar18 + 0xc5) = 0;
  *(undefined1 *)(iVar18 + 0xc9) = 0;
  if (*(int8_t *)(iVar18 + 0x2eb) == '\0') {
    FUN_01013e98(iVar18,3);
  }
  else {
    FUN_01013e98(iVar18,2);
  }
LAB_01014dc8:
  if ((code *)*DAT_01014df4 != (code *)0x0) {
    (*(code *)*DAT_01014df4)(*(undefined4 *)(iVar5 + 4),*DAT_01014df8);
  }
  *(undefined1 *)(*(int *)(iVar5 + 4) + 0x2eb) = 0;
  FUN_0100a984();
  return;
}
