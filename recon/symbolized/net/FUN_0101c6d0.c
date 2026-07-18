#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101c6d0 @ 0x0101c6d0
 * public-name: FUN_0101c6d0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_typed_handle_lookup           <= FUN_01009d18 @ 0x01009d18
 *   controller_packet_length_matches_type    <= FUN_0100e610 @ 0x0100e610
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   controller_work_update_or_enqueue        <= FUN_0100efc8 @ 0x0100efc8
 *   controller_timing_windows_clamp          <= FUN_0100f1f8 @ 0x0100f1f8
 *   controller_procedure_counters_reset      <= FUN_0100f784 @ 0x0100f784
 * address symbols (name @ address):
 *   rodata_10100a1                           @ 0x010100a1
 *   rodata_10101cd                           @ 0x010101cd
 *   g_210001e0                               @ 0x210001e0
 *   g_21000208                               @ 0x21000208
 *   g_21000210                               @ 0x21000210
 *   g_210004ac                               @ 0x210004ac
 *   g_210004bc                               @ 0x210004bc
 *   g_net_link_ctx_b                         @ 0x21001124
 */
/* Full net-core reconstruction FUN_0101c6d0 @ 0x101c6d0. */
#include <stdint.h>
typedef uint8_t undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;
typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint32_t code(uintptr_t, ...);
#define CARRY4(a,b) ((uint32_t)(a) > UINT32_MAX - (uint32_t)(b))
#define DAT_0101c978 ((unsigned long)&g_net_link_ctx_b) /*=0x21001124*/
#define DAT_0101c97c 0x010109cdu
#define DAT_0101c980 ((unsigned long)&rodata_10100a1) /*=0x10100a1*/
#define DAT_0101c984 0x21000400u
#define DAT_0101cce8 ((unsigned long)&g_net_link_ctx_b) /*=0x21001124*/
#define DAT_0101ccec 0x21000354u
#define DAT_0101ccf0 ((volatile uint32_t *)((unsigned long)&g_210001e0) /*=0x210001e0*/)
#define DAT_0101ccf4 ((unsigned long)&rodata_10101cd) /*=0x10101cd*/
#define DAT_0101ccf8 ((volatile uint32_t *)((unsigned long)&g_210004ac) /*=0x210004ac*/)
#define DAT_0101d260 ((volatile uint32_t *)((unsigned long)&g_210004bc) /*=0x210004bc*/)
#define DAT_0101d264 ((unsigned long)&g_net_link_ctx_b) /*=0x21001124*/
#define DAT_0101d3f8 ((volatile uint32_t *)((unsigned long)&g_21000208) /*=0x21000208*/)
#define DAT_0101d3fc ((unsigned long)&g_net_link_ctx_b) /*=0x21001124*/
#define DAT_0101d400 ((volatile uint32_t *)((unsigned long)&g_21000210) /*=0x21000210*/)
extern uint32_t sdc_assertion_fail(uintptr_t, ...); extern uint32_t controller_typed_handle_lookup(uintptr_t, ...);
extern uint32_t FUN_0100a984(uintptr_t, ...); extern uint32_t FUN_0100b630(uintptr_t, ...);
extern uint32_t FUN_0100d14c(uintptr_t, ...); extern uint32_t FUN_0100d3c0(uintptr_t, ...);
extern uint32_t FUN_0100d5d0(uintptr_t, ...); extern uint32_t FUN_0100d7bc(uintptr_t, ...);
extern uint32_t controller_packet_length_matches_type(uintptr_t, ...); extern uint32_t sdc_work_submit(uintptr_t, ...);
extern uint32_t controller_work_update_or_enqueue(uintptr_t, ...); extern uint32_t FUN_0100f110(uintptr_t, ...);
extern uint32_t controller_timing_windows_clamp(uintptr_t, ...); extern uint32_t controller_procedure_counters_reset(uintptr_t, ...);
extern uint32_t FUN_0100f7e0(uintptr_t, ...); extern uint32_t FUN_0100f86c(uintptr_t, ...);
extern uint32_t FUN_0100fae4(uintptr_t, ...); extern uint32_t FUN_01016250(uintptr_t, ...);
extern uint32_t FUN_0101bdd4(uintptr_t, ...); extern uint32_t FUN_0101c420(uintptr_t, ...);
extern uint32_t FUN_0101f934(uintptr_t, ...); extern uint32_t FUN_010258cc(uintptr_t, ...);
extern uint32_t FUN_01029882(uintptr_t, ...); extern uint32_t FUN_010298ba(uintptr_t, ...);
void FUN_0101c6d0(int param_1,uint param_2)

{
  byte bVar1;
  int iVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  undefined4 uVar10;
  char cVar11;
  undefined1 uVar12;
  uint uVar13;
  code *pcVar14;
  undefined2 *puVar15;
  int local_20;
  char local_1c;

  iVar2 = DAT_0101c978;
  uVar8 = (uint)*(ushort *)(DAT_0101c978 + 10);
  iVar7 = *(int *)(DAT_0101c978 + 4);
  if ((int)(uVar8 << 0x17) < 0) {
    *(undefined2 *)(iVar7 + 0xf6) = 0;
    if (*(char *)(iVar7 + 0xcb) != '\0') goto LAB_0101c6f6;
LAB_0101c868:
    iVar7 = FUN_0100d3c0(iVar7 + 0xa8,6,*(undefined1 *)(iVar7 + 0xc5));
    uVar8 = (uint)*(ushort *)(iVar2 + 10);
    if (iVar7 != 0) {
      iVar7 = *(int *)(iVar2 + 4);
      if (((int)(uVar8 << 0x14) < 0) && (*(char *)(iVar7 + 0xcb) != '\0')) goto LAB_0101c890;
      goto LAB_0101c6fc;
    }
  }
  else {
    *(short *)(iVar7 + 0xf6) = *(short *)(iVar7 + 0xf6) + 1;
    if (*(char *)(iVar7 + 0xcb) == '\0') goto LAB_0101c868;
LAB_0101c6f6:
    if ((int)(uVar8 << 0x14) < 0) {
LAB_0101c890:
      *(undefined4 *)(iVar7 + 0xe8) = 0;
    }
    else {
LAB_0101c6fc:
      uVar4 = *(uint *)(iVar7 + 0xec);
      uVar13 = *(int *)(iVar7 + 0xe8) + 1;
      *(uint *)(iVar7 + 0xe8) = uVar13;
      if ((uVar4 < uVar13) || (uVar4 - uVar13 <= *(ushort *)(iVar7 + 0x1c) + 5)) {
        *(undefined1 *)(iVar7 + 0xf4) = 1;
      }
      if (uVar4 <= uVar13) {
        *(undefined4 *)(iVar7 + 0xe8) = 0;
        controller_work_update_or_enqueue(iVar7 + 0x1c5,DAT_0101c97c,2);
        uVar8 = (uint)*(ushort *)(iVar2 + 10);
      }
    }
  }
  if (((uVar8 & 0x300) != 0) && (*(char *)(*(int *)(iVar2 + 4) + 0xc9) == '\0')) {
    *(undefined1 *)(*(int *)(iVar2 + 4) + 0xc9) = 1;
    FUN_0101bdd4(0);
  }
  if ((param_1 == 1) || (param_2 != 0)) goto LAB_0101c89c;
  param_2 = (uint)*(ushort *)(iVar2 + 10);
  if ((int)(param_2 << 0x1d) < 0) {
    iVar7 = *(int *)(iVar2 + 4);
    if (*(char *)(iVar7 + 0xc5) == '\x03') {
                    /* WARNING: Subroutine does not return */
      sdc_assertion_fail(0x36,0x497);
    }
    if (*(char *)(iVar7 + 199) == '\a') {
      *(undefined1 *)(iVar2 + 0x14) = 1;
      *(undefined1 *)(iVar7 + 199) = 0;
    }
  }
  if ((int)(param_2 << 0x1e) < 0) {
    uVar8 = (uint)*(byte *)(*(int *)(iVar2 + 0xc) + 3);
    if ((0x2a < uVar8) || (pcVar14 = *(code **)(DAT_0101c984 + uVar8 * 4), pcVar14 == (code *)0x0))
    {
                    /* WARNING: Subroutine does not return */
      sdc_assertion_fail(0x36,0x58d);
    }
    (*pcVar14)(DAT_0101c978);
    param_2 = (uint)*(ushort *)(iVar2 + 10);
    puVar15 = *(undefined2 **)(iVar2 + 4);
    if ((int)(param_2 << 0x1c) < 0) goto LAB_0101c8f2;
LAB_0101c77e:
    uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
    goto LAB_0101c782;
  }
  puVar15 = *(undefined2 **)(iVar2 + 4);
  if (-1 < (int)(param_2 << 0x1c)) goto LAB_0101c77e;
LAB_0101c8f2:
  cVar11 = *(char *)(puVar15 + 0xa7);
  switch(cVar11) {
  case '\0':
    if (-1 < (int)(((uint)(ushort)puVar15[0x5e] - (uint)(ushort)puVar15[399]) * 0x10000)) {
      *(undefined1 *)(puVar15 + 0x18e) = 0;
      puVar15 = *(undefined2 **)(iVar2 + 4);
      cVar11 = *(char *)(puVar15 + 0xa7);
      goto switchD_0101c8fc_caseD_2;
    }
    break;
  case '\x01':
    if (-1 < (int)(((uint)(ushort)puVar15[0x5e] - (uint)(ushort)puVar15[0x18b]) * 0x10000)) {
      **(char **)(puVar15 + 0x188) = **(char **)(puVar15 + 0x188) + -1;
    }
    break;
  default:
    goto switchD_0101c8fc_caseD_2;
  case '\x03':
    if (((*(byte *)((int)puVar15 + 0xc5) & 0xfd) != 0x18) &&
       (*(byte *)((int)puVar15 + 0xc5) != 0x15)) {
      *(undefined1 *)(puVar15 + 0x198) = 0;
    }
    break;
  case '\x1c':
  case '*':
    *(undefined1 *)(puVar15 + 0xba) = 0;
    puVar15 = *(undefined2 **)(iVar2 + 4);
    cVar11 = *(char *)(puVar15 + 0xa7);
    *(undefined1 *)(puVar15 + 0x80) = 0;
    goto switchD_0101c8fc_caseD_2;
  case '!':
    if ((code *)*DAT_0101ccf8 != (code *)0x0) {
      (*(code *)*DAT_0101ccf8)((uintptr_t)puVar15);
      puVar15 = *(undefined2 **)(iVar2 + 4);
      cVar11 = *(char *)(puVar15 + 0xa7);
      goto switchD_0101c8fc_caseD_2;
    }
    break;
  case '\"':
    pcVar14 = (code *)*DAT_0101ccf0;
    *(undefined1 *)(puVar15 + 0xd5) = 0;
    if (pcVar14 != (code *)0x0) {
      (*pcVar14)(*(int *)(iVar2 + 4) + 0x158,*(int *)(iVar2 + 4) + 0x1aa);
    }
    controller_procedure_counters_reset(DAT_0101cce8);
    puVar15 = *(undefined2 **)(iVar2 + 4);
    cVar11 = *(char *)(puVar15 + 0xa7);
switchD_0101c8fc_caseD_2:
    if (cVar11 == -2) {
                    /* WARNING: Subroutine does not return */
      sdc_assertion_fail(0x36,0x599);
    }
  }
  uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
  *(undefined1 *)(puVar15 + 0xa7) = 0xfe;
  if (uVar8 == 0xe) {
    uVar8 = 0xf;
    *(undefined1 *)((int)puVar15 + 0xc5) = 0xf;
  }
  else if (uVar8 == 0x26) {
    uVar8 = 0x27;
    *(undefined1 *)((int)puVar15 + 0xc5) = 0x27;
  }
  else if (uVar8 == 0xc) {
    uVar8 = 0xd;
    *(undefined1 *)((int)puVar15 + 0xc5) = 0xd;
  }
  if (*(char *)((int)puVar15 + 199) == '\b') {
    *(undefined1 *)(iVar2 + 0x14) = 2;
    *(undefined1 *)((int)puVar15 + 199) = 0;
  }
  param_2 = (uint)*(ushort *)(iVar2 + 10);
LAB_0101c782:
  param_2 = param_2 & 1;
  if (param_2 != 0) {
    iVar6 = *(int *)(iVar2 + 0x10);
    uVar12 = *(undefined1 *)(iVar6 + 3);
    iVar7 = FUN_0100d3c0((uintptr_t)(puVar15 + 0x54),5,uVar8,0);
    if (iVar7 != 0) {
      switch(uVar12) {
      case 2:
      case 4:
      case 5:
      case 6:
      case 0xb:
      case 0xd:
      case 0x11:
        break;
      default:
        puVar15 = *(undefined2 **)(iVar2 + 4);
        param_2 = 8;
        uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
        goto LAB_0101c78a;
      }
    }
    iVar7 = controller_packet_length_matches_type(iVar6);
    if (iVar7 == 0) {
      param_2 = FUN_0100f86c(DAT_0101cce8,iVar6);
      puVar15 = *(undefined2 **)(iVar2 + 4);
      uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
    }
    else if ((*(byte *)(iVar6 + 3) < 0x2b) &&
            (pcVar14 = *(code **)(DAT_0101ccec + (uint)*(byte *)(iVar6 + 3) * 4),
            pcVar14 != (code *)0x0)) {
      param_2 = (*pcVar14)(0);
      puVar15 = *(undefined2 **)(iVar2 + 4);
      uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
    }
    else {
      param_2 = FUN_0100f86c(DAT_0101cce8,iVar6);
      puVar15 = *(undefined2 **)(iVar2 + 4);
      uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
    }
  }
LAB_0101c78a:
  if ((int)((uint)*(byte *)(iVar2 + 8) << 0x1c) < 0) {
    iVar7 = FUN_0100d3c0((uintptr_t)(puVar15 + 0x54),5,uVar8,0);
    if (iVar7 == 0) {
      local_20 = iVar7;
      FUN_0100b630(3,&local_20);
      if (local_20 != 0) {
        *(undefined1 *)(local_20 + 8) = 0;
        sdc_work_submit(local_20,*(undefined4 *)(iVar2 + 4),0x10);
      }
      puVar15 = *(undefined2 **)(iVar2 + 4);
      uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
    }
    else {
      puVar15 = *(undefined2 **)(iVar2 + 4);
      param_2 = 8;
      uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
    }
  }
  if (uVar8 - 0xc < 2) {
    if (puVar15[0x18b] == (short)(puVar15[0x5e] + 1)) {
      *(undefined4 *)(puVar15 + 0x67) = *(undefined4 *)(*(int *)(puVar15 + 0x188) + 1);
      *(undefined1 *)(puVar15 + 0x69) = *(undefined1 *)(*(int *)(puVar15 + 0x188) + 5);
      FUN_0100d14c((uintptr_t)puVar15,3);
      if (**(char **)(puVar15 + 0x188) == '\0') {
                    /* WARNING: Subroutine does not return */
        sdc_assertion_fail(0x36,0x21e);
      }
      if (*(char *)(*(int *)(iVar2 + 4) + 0x14e) != '\x01') {
        pcVar9 = *(char **)(*(int *)(iVar2 + 4) + 0x310);
        *pcVar9 = *pcVar9 + -1;
      }
      *(undefined1 *)((int)puVar15 + 0xc5) = 0;
      uVar8 = (uint)*(byte *)((int)puVar15 + 0xc5);
      *(undefined1 *)(puVar15 + 0x8f) = 0xff;
      goto LAB_0101c79c;
    }
  }
  else {
LAB_0101c79c:
    if ((uVar8 - 0xe < 2) && (puVar15[399] == (short)(puVar15[0x5e] + 1))) {
      puVar15[0x117] = *puVar15;
      uVar3 = FUN_0100d5d0(*(undefined4 *)(puVar15 + 0x194));
      puVar15[0x118] = uVar3;
      puVar15[0x119] = puVar15[0x196];
      uVar5 = DAT_0101ccf4;
      puVar15[0x11a] = puVar15[0x197];
      *(undefined1 *)((int)puVar15 + 0x22d) = 0;
      controller_work_update_or_enqueue((uintptr_t)(puVar15 + 0x112),uVar5,2);
      *(undefined1 *)(puVar15 + 0x18e) = 0;
      FUN_0100d14c((uintptr_t)puVar15,2);
      FUN_0101bdd4((uintptr_t)puVar15,3);
      *(undefined1 *)((int)puVar15 + 0xc5) = 0;
    }
  }
  iVar7 = *(int *)(iVar2 + 4);
  if (*(char *)(iVar7 + 0x14e) != -2) goto LAB_0101c7c0;
  iVar6 = FUN_0100d3c0(iVar7 + 0xa8,1,*(undefined1 *)(iVar7 + 199),0);
  iVar7 = *(int *)(iVar2 + 4);
  if (iVar6 != 0) goto LAB_0101c7c0;
  if (*(char *)(iVar7 + 0x160) != '\0') {
    *(undefined1 *)(iVar7 + 0x14e) = 2;
    goto LAB_0101c7c0;
  }
  iVar6 = FUN_0100d3c0(iVar7 + 0xa8,0,*(undefined1 *)(iVar7 + 0xc5),0);
  iVar7 = *(int *)(iVar2 + 4);
  if ((iVar6 != 0) && (*(char *)(iVar7 + 0xf4) != '\0')) {
    *(undefined2 *)(iVar7 + 0xfc) = 0;
    *(undefined1 *)(iVar7 + 0x100) = 1;
    *(undefined1 *)(iVar7 + 0x14e) = 0x12;
    goto LAB_0101c7c0;
  }
  switch(*(undefined1 *)(iVar7 + 0xc5)) {
  case 3:
    *(undefined1 *)(iVar7 + 0x150) = *(undefined1 *)(iVar7 + 0x149);
    *(undefined1 *)(iVar7 + 0x14e) = 7;
    break;
  default:
    iVar7 = FUN_0100d3c0(iVar7 + 0xa8,4,*(undefined1 *)(iVar7 + 0xc5),0);
    if (iVar7 != 0) goto LAB_0101c89c;
    iVar7 = *(int *)(iVar2 + 4);
    switch(*(undefined1 *)(iVar7 + 0xc6)) {
    case 1:
      *(undefined1 *)(iVar7 + 0x14e) = 0xc;
      *(undefined2 *)(iVar7 + 0x102) = 0;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      *(byte *)(iVar7 + 0x107) = *(byte *)(iVar7 + 0x107) | 1;
      break;
    case 2:
      *(undefined1 *)(iVar7 + 0x14e) = 0x13;
      *(undefined2 *)(iVar7 + 0x102) = 0;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      break;
    case 3:
      *(undefined1 *)(iVar7 + 0x150) = *(undefined1 *)(iVar7 + 0x148);
      *(undefined1 *)(iVar7 + 0x14e) = 7;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      break;
    case 4:
      *(undefined1 *)(iVar7 + 0x14e) = 9;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      break;
    case 6:
      *(undefined1 *)(iVar7 + 0x14e) = 0x1b;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      break;
    case 0x1f:
    case 0x20:
      if (*(char *)(iVar7 + 0x163) == '\0') {
        if (*(char *)(iVar7 + 0x162) != '\0') {
          FUN_0100f110(iVar7,iVar7 + 0x162,iVar7 + 0x31a,*(byte *)(iVar7 + 0xc5) - 0x26 < 2);
          iVar7 = *(int *)(iVar2 + 4);
          *(undefined1 *)(iVar7 + 0xc6) = 0x20;
          *(undefined1 *)(iVar7 + 0x162) = 0;
        }
        if (*(char *)(*(int *)(iVar2 + 4) + 0xc6) == ' ') {
          controller_timing_windows_clamp(0);
          FUN_0100fae4(DAT_0101d264);
          iVar7 = *(int *)(iVar2 + 4);
          *(undefined2 *)(iVar7 + 0x150) = *(undefined2 *)(iVar7 + 0x4e);
          *(undefined2 *)(iVar7 + 0x152) = *(undefined2 *)(iVar7 + 0x52);
          *(undefined1 *)(iVar7 + 0x14e) = 0x15;
          *(undefined2 *)(iVar7 + 0x102) = 0;
          *(undefined1 *)(iVar7 + 0xc6) = 0;
        }
      }
      break;
    case 0x23:
      if ((*(char *)(iVar7 + 0x16c) == '\x01') && (*(char *)(iVar7 + 0x16d) == '\0')) {
        uVar10 = *(undefined4 *)(iVar7 + 0x66);
        uVar5 = *(undefined4 *)(iVar7 + 0x16e);
      }
      else {
        if (*(char *)(iVar7 + 0x16c) != '\x02') break;
        uVar10 = *(undefined4 *)(iVar7 + 0x66);
        uVar5 = *(undefined4 *)(iVar7 + 0x6a);
      }
      FUN_010298ba(DAT_0101d264,uVar5,uVar10);
      *(undefined1 *)(*(int *)(iVar2 + 4) + 0x14e) = 0x18;
      break;
    case 0x29:
      *(undefined1 *)(iVar7 + 0x14e) = 0x24;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      break;
    case 0x30:
      *(undefined1 *)(iVar7 + 0x150) = 0;
      *(undefined2 *)(iVar7 + 0x102) = 0;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
      *(undefined1 *)(iVar7 + 0x14e) = 0x11;
      break;
    case 0x31:
      *(undefined1 *)(iVar7 + 0x14e) = 0x1e;
      *(undefined1 *)(iVar7 + 0xc6) = 0;
    }
    iVar7 = *(int *)(iVar2 + 4);
    if (*(char *)(iVar7 + 0x14e) != -2) break;
    iVar7 = FUN_0100d3c0(iVar7 + 0xa8,0,*(undefined1 *)(iVar7 + 0xc5));
    if (iVar7 != 0) {
      if ((*(char *)(*(int *)(iVar2 + 4) + 0x31c) == '\0') ||
         (iVar7 = FUN_0100f7e0(*(undefined1 *)(*(int *)(iVar2 + 4) + 0xc6)), iVar7 != 0)) {
        iVar7 = *(int *)(iVar2 + 4);
        if (*(char *)(iVar7 + 0x330) == '\0') {
          if (*(char *)(iVar7 + 0x173) == '\0') {
            iVar6 = *(int *)(iVar7 + 0x35c);
            if (iVar6 == 0) {
              if (*(char *)(iVar7 + 0x172) == '\0') {
                if ((*(char *)(iVar7 + 0x162) == '\0') || (*(char *)(iVar7 + 0x163) != '\0')) {
                  if ((*(char *)(iVar7 + 0x16c) == '\x01') &&
                     ((*(char *)(iVar7 + 0x16d) == '\0' &&
                      (iVar7 = FUN_0100f7e0(*(undefined1 *)(iVar7 + 0xc6)), iVar7 == 0)))) {
                    iVar7 = *(int *)(iVar2 + 4);
                    switch(*(undefined1 *)(iVar7 + 0x6e)) {
                    case 1:
                      switch(*(undefined1 *)(iVar7 + 0x6f)) {
                      case 1:
                        if (*(char *)(iVar7 + 0x16e) == '\x01') {
LAB_0101d35e:
                          if (*(char *)(iVar7 + 0x16f) == '\x01') {
LAB_0101d366:
                            iVar7 = FUN_01029882(*(undefined2 *)(iVar7 + 0x170),
                                                 *(undefined1 *)(iVar7 + 0x6e),iVar7 + 0x318,
                                                 *(undefined2 *)(iVar7 + 0xbc));
                            if (iVar7 == 0) {
                              FUN_0101f934(DAT_0101d3fc,0);
                            }
                            else {
                              *(undefined1 *)(*(int *)(iVar2 + 4) + 0xc5) = 0x28;
                            }
                            goto LAB_0101ce06;
                          }
                        }
                        break;
                      case 2:
                        if (*(char *)(iVar7 + 0x16e) == '\x01') {
LAB_0101d38c:
                          if (*(char *)(iVar7 + 0x16f) == '\x02') goto LAB_0101d366;
                        }
                        break;
                      default:
                        goto switchD_0101d2bc_caseD_3;
                      case 4:
                      case 8:
                        if (*(char *)(iVar7 + 0x16e) == '\x01') {
LAB_0101d3b0:
                          if (*(char *)(iVar7 + 0x16f) == '\x04') goto LAB_0101d366;
                        }
                      }
                      break;
                    case 2:
                      switch(*(undefined1 *)(iVar7 + 0x6f)) {
                      case 1:
                        if (*(char *)(iVar7 + 0x16e) == '\x02') goto LAB_0101d35e;
                        break;
                      case 2:
                        if (*(char *)(iVar7 + 0x16e) == '\x02') goto LAB_0101d38c;
                        break;
                      default:
                        goto switchD_0101d2bc_caseD_3;
                      case 4:
                      case 8:
                        if (*(char *)(iVar7 + 0x16e) == '\x02') goto LAB_0101d3b0;
                      }
                      break;
                    default:
switchD_0101d2bc_caseD_3:
                    /* WARNING: Subroutine does not return */
                      sdc_assertion_fail(6,0x294);
                    case 4:
                    case 8:
                      switch(*(undefined1 *)(iVar7 + 0x6f)) {
                      case 1:
                        if (*(char *)(iVar7 + 0x16e) == '\x04') goto LAB_0101d35e;
                        break;
                      case 2:
                        if (*(char *)(iVar7 + 0x16e) == '\x04') goto LAB_0101d38c;
                        break;
                      default:
                        goto switchD_0101d2bc_caseD_3;
                      case 4:
                      case 8:
                        if (*(char *)(iVar7 + 0x16e) == '\x04') goto LAB_0101d3b0;
                      }
                    }
                    uVar12 = 0x16;
                    goto LAB_0101cefa;
                  }
                  iVar7 = *(int *)(iVar2 + 4);
                  if (*(char *)(iVar7 + 0x174) == '\0') {
                    if (*(char *)(iVar7 + 0x1a9) == '\0') {
                      if (*(char *)(iVar7 + 0x1a6) == '\0') {
                        if (*(char *)(iVar7 + 0x1b2) == '\0') {
                          if (*(char *)(iVar7 + 0x1aa) != '\0') {
                            iVar7 = controller_typed_handle_lookup(*(undefined2 *)(iVar7 + 0x1ac),8);
                            if (iVar7 == 0) {
                              *(undefined1 *)(*(int *)(iVar2 + 4) + 0x1aa) = 0;
                            }
                            else if (*(char *)(iVar7 + 0x1c0) == '\0') {
                              *(undefined1 *)(*(int *)(iVar2 + 4) + 0x1aa) = 0;
                            }
                            else {
                              switch(*(undefined1 *)(iVar7 + 0x198)) {
                              case 2:
                                *(undefined1 *)(iVar7 + 0x1c1) =
                                     *(undefined1 *)(*(int *)(iVar2 + 4) + 0x1b0);
                              case 0:
                              case 1:
                                *(undefined1 *)(*(int *)(iVar2 + 4) + 0x1aa) = 0;
                                break;
                              case 3:
                                iVar7 = *(int *)(iVar2 + 4);
                                *(undefined1 *)(iVar7 + 0x14e) = 0x22;
                                *(undefined2 *)(iVar7 + 0xfc) = 0;
                                *(undefined1 *)(iVar7 + 0x100) = 1;
                                break;
                              default:
                    /* WARNING: Subroutine does not return */
                                sdc_assertion_fail(0x36,0x657);
                              }
                            }
                          }
                        }
                        else {
                          *(undefined2 *)(iVar7 + 0xfc) = 0;
                          *(undefined1 *)(iVar7 + 0x100) = 1;
                          *(undefined1 *)(iVar7 + 0x14e) = 0x1d;
                        }
                      }
                      else {
                        *(undefined2 *)(iVar7 + 0xfc) = 0;
                        *(undefined1 *)(iVar7 + 0x14e) = 0x25;
                        *(undefined1 *)(iVar7 + 0x100) = 1;
                        *(undefined1 *)(iVar7 + 0x1a6) = 0;
                      }
                    }
                    else {
                      *(undefined2 *)(iVar7 + 0xfc) = 0;
                      *(undefined1 *)(iVar7 + 0x100) = 1;
                      *(undefined1 *)(iVar7 + 0x14e) = 0x23;
                    }
                  }
                  else {
                    iVar7 = FUN_01016250(*(undefined1 *)(iVar7 + 0x178));
                    iVar6 = *(int *)(iVar2 + 4);
                    if (iVar7 == 0) {
                      iVar7 = (*(code *)*DAT_0101d400)
                                        (DAT_0101d3fc,iVar6 + 0x179,iVar6 + 0x19b,
                                         *(undefined1 *)(iVar6 + 0x178));
                    }
                    else {
                      iVar7 = (*(code *)*DAT_0101d3f8)
                                        (DAT_0101d3fc,iVar6 + 0x179,*(undefined1 *)(iVar6 + 0x178));
                    }
                    if (iVar7 == 0) {
                      iVar7 = FUN_01016250(*(undefined1 *)(*(int *)(iVar2 + 4) + 0x178));
                      iVar6 = *(int *)(iVar2 + 4);
                      *(undefined2 *)(iVar6 + 0xfc) = 0;
                      *(undefined1 *)(iVar6 + 0x100) = 1;
                      if (iVar7 == 0) {
                        *(undefined1 *)(iVar6 + 0x14e) = 0x2a;
                      }
                      else {
                        *(undefined1 *)(iVar6 + 0x14e) = 0x1c;
                      }
                    }
                    else if (iVar7 == 2) {
                      *(undefined1 *)(*(int *)(iVar2 + 4) + 0x174) = 0;
                    }
                  }
                }
                else {
                  if (*(char *)(iVar7 + 0xc6) == '&') {
                    uVar5 = 1;
                  }
                  else if (*(byte *)(iVar7 + 0xc5) - 0x26 < 2) {
                    uVar5 = 1;
                  }
                  else {
                    uVar5 = 0;
                  }
                  FUN_0100f110(iVar7,iVar7 + 0x162,iVar7 + 0x31a,uVar5);
                  *(undefined1 *)(*(int *)(iVar2 + 4) + 0x162) = 0;
                  iVar7 = *(int *)(iVar2 + 4);
                  *(undefined2 *)(iVar7 + 0xfc) = 0;
                  *(undefined1 *)(iVar7 + 0x100) = 1;
                  *(undefined2 *)(iVar7 + 0x150) = *(undefined2 *)(iVar7 + 0x4e);
                  *(undefined2 *)(iVar7 + 0x152) = *(undefined2 *)(iVar7 + 0x52);
                  *(undefined1 *)(iVar7 + 0x14e) = 0x14;
                }
              }
              else {
                bVar1 = *(byte *)(iVar7 + 0x107);
                if ((bVar1 & 3) == 0) {
                  *(byte *)(iVar7 + 0x172) = bVar1 & 3;
                  *(byte *)(iVar7 + 0x107) = bVar1 | 1;
                  *(undefined1 *)(iVar7 + 0x14e) = 0xc;
                }
              }
            }
            else {
              if (*(char *)(iVar6 + -0x51) != '\x01') {
                    /* WARNING: Subroutine does not return */
                sdc_assertion_fail(0x36,0x682);
              }
              if (*(char *)(iVar6 + -0x28) != '\0') {
                    /* WARNING: Subroutine does not return */
                sdc_assertion_fail(0x36,0x683);
              }
              if ((int)((uint)*(byte *)(iVar7 + 0x119) << 0x1a) < 0) {
                *(undefined2 *)(iVar7 + 0xfc) = 0;
                *(undefined1 *)(iVar7 + 0x100) = 1;
                *(undefined1 *)(iVar7 + 0x14e) = 0x1f;
              }
              else {
                (*(code *)*DAT_0101d260)(0);
              }
            }
          }
          else {
            *(undefined2 *)(iVar7 + 0xfc) = 0;
            *(undefined1 *)(iVar7 + 0x100) = 1;
            *(undefined1 *)(iVar7 + 0x14e) = 8;
          }
        }
        else if (*(char *)(iVar7 + 0xca) == '\0') {
          FUN_0101c420(0);
        }
        else {
          if (*(char *)(iVar7 + 0xcb) == '\0') {
                    /* WARNING: Subroutine does not return */
            sdc_assertion_fail(0x36,0x66a);
          }
          uVar12 = 10;
LAB_0101cefa:
          *(undefined1 *)(iVar7 + 0x14e) = uVar12;
          *(undefined2 *)(iVar7 + 0xfc) = 0;
          *(undefined1 *)(iVar7 + 0x100) = 1;
        }
      }
      else {
        *(undefined1 *)(*(int *)(iVar2 + 4) + 0x14e) = 0;
      }
    }
LAB_0101ce06:
    iVar7 = *(int *)(iVar2 + 4);
    if (*(char *)(iVar7 + 0x14e) != -2) break;
    iVar6 = FUN_0100d3c0(iVar7 + 0xa8,0,*(undefined1 *)(iVar7 + 0xc5));
    iVar7 = *(int *)(iVar2 + 4);
    if ((iVar6 == 0) || (*(char *)(iVar7 + 0x314) == '\0')) break;
    iVar6 = FUN_0100f7e0(*(undefined1 *)(iVar7 + 0xc6));
    iVar7 = *(int *)(iVar2 + 4);
    if ((iVar6 != 0) || (*(ushort *)(iVar7 + 0xbc) < 0xb)) break;
    iVar6 = FUN_0100d7bc((uintptr_t)&local_20);
    iVar7 = *(int *)(iVar2 + 4);
    if (iVar6 == 0) break;
    iVar6 = FUN_010258cc((uintptr_t)&local_20,iVar7 + 0xce,5);
    if (iVar6 == 0) {
      *(undefined1 *)(iVar7 + 0x314) = 0;
    }
    else {
      pcVar9 = *(char **)(iVar7 + 0x310);
      if (*pcVar9 == '\0') {
        *(int *)(pcVar9 + 1) = local_20;
        pcVar9[5] = local_1c;
      }
      else {
        iVar7 = FUN_010258cc((uintptr_t)&local_20,pcVar9 + 1,5);
        if (iVar7 != 0) goto LAB_0101c89c;
      }
      iVar7 = *(int *)(iVar2 + 4);
      **(char **)(iVar7 + 0x310) = **(char **)(iVar7 + 0x310) + '\x01';
      *(undefined1 *)(iVar7 + 0x14e) = 1;
      *(undefined1 *)(iVar7 + 0x314) = 0;
    }
LAB_0101c89c:
    iVar7 = *(int *)(iVar2 + 4);
    cVar11 = *(char *)(iVar7 + 0x160);
    goto joined_r0x0101c8a4;
  case 0x13:
    FUN_0101c420(0);
    iVar7 = *(int *)(iVar2 + 4);
    break;
  case 0x14:
    uVar12 = 0xb;
    goto LAB_0101cd9a;
  case 0x1a:
    uVar12 = 6;
    goto LAB_0101cd9a;
  case 0x25:
    *(undefined1 *)(iVar7 + 0x14e) = 0x18;
    *(undefined2 *)(iVar7 + 0xfc) = 0;
    break;
  case 0x2e:
    uVar12 = 0x21;
LAB_0101cd9a:
    *(undefined1 *)(iVar7 + 0x14e) = uVar12;
    *(undefined2 *)(iVar7 + 0xfc) = 0;
    *(undefined1 *)(iVar7 + 0x100) = 1;
    break;
  case 0x30:
    *(undefined1 *)(iVar7 + 0x150) = 1;
    *(undefined1 *)(iVar7 + 0x14e) = 0x11;
    *(undefined2 *)(iVar7 + 0xfc) = 0;
    *(undefined1 *)(iVar7 + 0xc5) = 0;
  }
LAB_0101c7c0:
  cVar11 = *(char *)(iVar7 + 0x160);
joined_r0x0101c8a4:
  if ((cVar11 != '\0') ||
     (iVar6 = FUN_0100d3c0(iVar7 + 0xa8,1,*(undefined1 *)(iVar7 + 199)), iVar6 != 0)) {
    *(short *)(iVar7 + 0xfa) = *(short *)(iVar7 + 0xfa) + 1;
  }
  if (*(char *)(iVar7 + 0x100) != '\0') {
    *(short *)(iVar7 + 0xfc) = *(short *)(iVar7 + 0xfc) + 1;
  }
  if (*(char *)(iVar7 + 0x104) != '\0') {
    *(short *)(iVar7 + 0x102) = *(short *)(iVar7 + 0x102) + 1;
  }
  uVar5 = DAT_0101c980;
  if (param_1 == 0) {
    if (*(char *)(iVar2 + 0x14) == '\x02') {
      cVar11 = '\x16';
    }
    else if (*(char *)(iVar2 + 0x14) == '\x01') {
      iVar6 = *(int *)(iVar2 + 4);
      cVar11 = *(char *)(iVar6 + 200);
      if (cVar11 == '\0') {
LAB_0101ca34:
        FUN_0101bdd4(iVar6,0);
        goto LAB_0101c84a;
      }
    }
    else if (param_2 == 0) {
      if (((*(char *)(iVar7 + 0x100) == '\0') ||
          (*(ushort *)(iVar7 + 0xfc) <= *(ushort *)(iVar7 + 0xfe))) &&
         ((*(char *)(iVar7 + 0x104) == '\0' ||
          (*(ushort *)(iVar7 + 0x102) <= *(ushort *)(iVar7 + 0xfe))))) {
        if (((*(ushort *)(iVar7 + 0xfa) < *(ushort *)(iVar7 + 0xf8)) ||
            (*(char *)(*(int *)(iVar2 + 4) + 0x160) == '\0')) &&
           (*(ushort *)(iVar7 + 0xfa) < *(ushort *)(iVar7 + 0xfe))) {
          if (*(char *)(iVar7 + 0xc9) == '\0') {
            if (*(ushort *)(iVar7 + 0xf6) < 6) goto LAB_0101ceac;
            cVar11 = '>';
          }
          else {
            if (*(ushort *)(iVar7 + 0xf6) < *(ushort *)(iVar7 + 0xf8)) {
LAB_0101ceac:
              iVar6 = *(int *)(iVar2 + 4);
              goto LAB_0101ca34;
            }
            cVar11 = '\b';
          }
          goto LAB_0101c814;
        }
      }
      cVar11 = '\"';
    }
    else if ((int)(param_2 << 0x1b) < 0) {
      cVar11 = '\x1e';
    }
    else {
      if ((int)(param_2 << 0x1c) < 0) goto LAB_0101c812;
      if ((param_2 & 3) == 0) {
        if (-1 < (int)(param_2 << 0x1a)) {
                    /* WARNING: Subroutine does not return */
          sdc_assertion_fail(0x36,0xb03);
        }
        cVar11 = '#';
      }
      else {
        cVar11 = '*';
      }
    }
  }
  else {
LAB_0101c812:
    cVar11 = '=';
  }
LAB_0101c814:
  *(char *)(iVar7 + 0xe5) = cVar11;
  sdc_work_submit(iVar7 + 0xdc,uVar5,2);
  uVar5 = *(undefined4 *)(iVar2 + 4);
  *(undefined2 *)(iVar7 + 0xc5) = 0;
  *(undefined1 *)(iVar7 + 0xc9) = 0;
  FUN_0101bdd4(uVar5,2);
  if (*(char *)(*(int *)(iVar2 + 4) + 0x14e) == '\x01') {
    pcVar9 = *(char **)(*(int *)(iVar2 + 4) + 0x310);
    *pcVar9 = *pcVar9 + -1;
  }
LAB_0101c84a:
  FUN_0100a984(0);
  return;
}
