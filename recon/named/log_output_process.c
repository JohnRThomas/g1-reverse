/* readable reconstruction; identity: FUN_0004db04 @ 0x0004db04
 * public-name: log_output_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   print_formatted                          <= FUN_0004da6c @ 0x0004da6c
 *   newline_print                            <= FUN_0004da90 @ 0x0004da90
 *   log_output_process                       <= FUN_0004db04 @ 0x0004db04
 *   cbpprintf_external                       <= FUN_0007db9e @ 0x0007db9e
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   log_output_flush_noop                    <= FUN_0007ee44 @ 0x0007ee44
 *   log_output_flush                         <= FUN_0007eece @ 0x0007eece
 * address symbols (name @ address):
 *   rodata_4daad                             @ 0x0004daad
 *   ADDR_cbvprintf_wrapper_THUMB             @ 0x0007eec1
 *   rodata_8acc4                             @ 0x0008acc4
 *   rodata_8acd8                             @ 0x0008acd8
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_a7993                             @ 0x000a7993
 *   rodata_a8c37                             @ 0x000a8c37
 *   rodata_f0e73                             @ 0x000f0e73
 *   rodata_f0ed2                             @ 0x000f0ed2
 *   rodata_f0ed7                             @ 0x000f0ed7   [INLINED -- G6 literal batch]
 *   rodata_f0ee3                             @ 0x000f0ee3
 *   rodata_f0ee7                             @ 0x000f0ee7
 *   rodata_f0ef0                             @ 0x000f0ef0
 *   rodata_f0f0c                             @ 0x000f0f0c
 *   rodata_f0f12                             @ 0x000f0f12
 *   rodata_f0f16                             @ 0x000f0f16
 *   rodata_f0f1b                             @ 0x000f0f1b   [INLINED -- G6 literal batch]
 *   rodata_f0f24                             @ 0x000f0f24
 *   rodata_f0f26                             @ 0x000f0f26
 *   rodata_f7b6d                             @ 0x000f7b6d
 *   rodata_f7b6f                             @ 0x000f7b6f
 *   rodata_f8a6b                             @ 0x000f8a6b
 *   g_2000a0e0                               @ 0x2000a0e0
 *   g_2000a0e4                               @ 0x2000a0e4
 */
/* Reconstructed FUN_0004db04 @ 0x4db04  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
typedef unsigned int uint;
extern int print_formatted(unsigned,...);
extern int newline_print(unsigned,unsigned);
extern int cbpprintf_external(unsigned,unsigned,unsigned,int);
extern int assert_post_action(unsigned,unsigned);
extern int log_output_flush_noop(void);
extern int log_output_flush(unsigned);
#define U8(a)  (*(volatile uint8_t*)(uintptr_t)(a))
#define U32(a) (*(volatile uint32_t*)(uintptr_t)(a))

void log_output_process(uint param_1,uint param_2,int param_3,int param_4,uint param_5,
                  unsigned char param_6,int param_7,unsigned char *param_8,uint param_9,uint param_10)
{
  uint uVar1=0, uVar6;
  int iVar2, iVar3, iVar5;
  uint uVar4, uVar7, uVar8, uVar9, uVar10, local_3c;
  unsigned char *local_38;

  uVar8 = (uint)param_6;
  local_38 = param_8;
  local_3c = param_9;
  if (uVar8 == 0) {
    uVar6 = 0x0007eee9;
    if (param_4 == 1) uVar6 = 0x0004daad;
    if (param_7 == 0) {
      if (param_9 != 0) {
        iVar2 = 0;
        uVar6 = 0x000a7993;
        uVar1 = 0x000f7b6f;
        goto LAB_dcaa;
      }
      goto LAB_dd7a;
    }
    iVar2 = 0;
LAB_dc74:
    iVar3 = cbpprintf_external(uVar6,0x0007eec1,param_1,param_7);
    if (iVar3 < 0) {
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"err >= 0"),0x000f0e73,0x219);
      uVar6 = 0x219;
LAB_db3e:
      assert_post_action(0x000f0e73,uVar6);
    }
    uVar6 = 0x000a7993;
    uVar1 = 0x000f7b6f;
    if (param_9 != 0) {
LAB_dcaa:
      uVar4 = local_3c;
      if (0xf < local_3c) uVar4 = 0x10;
      newline_print(param_1,param_10);
      for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
        print_formatted(param_1,uVar1);
      }
      print_formatted(param_1,uVar6,*local_38);
      uVar9 = 1;
      do {
        if ((uVar9 & 7) == 0) print_formatted(param_1,uVar1);
        if (uVar9 < uVar4) print_formatted(param_1,uVar6,local_38[uVar9]);
        else print_formatted(param_1,0x000f7b6d);
        uVar9 = uVar9 + 1;
      } while (uVar9 != 0x10);
      uVar9 = 0;
      print_formatted(param_1,0x000f0f24);
      do {
        uVar7 = (uint)(unsigned char)local_38[uVar9];
        if ((U8(0x000f8a6b + uVar7) & 0x97) == 0) uVar7 = 0x2e;
        print_formatted(param_1,0x000f0f26,uVar7);
        while (1) {
          uVar9 = uVar9 + 1;
          if (uVar9 == 0x10) {
            local_38 = local_38 + uVar4;
            local_3c = local_3c - uVar4;
            if (local_3c != 0) goto LAB_dcaa;
            goto LAB_dd74;
          }
          if ((uVar9 & 7) == 0) print_formatted(param_1,uVar1);
          if (uVar9 < uVar4) break;
          print_formatted(param_1,uVar1);
        }
      } while (1);
    }
LAB_dd74:
    if (uVar8 == 0) goto LAB_dd7a;
  } else {
    if (4 < uVar8) {
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"level <= 4U"),0x000f0e73,0x1bf);
      uVar6 = 0x1bf;
      goto LAB_db3e;
    }
    iVar2 = log_output_flush_noop();
    if (iVar2 == 0) iVar3 = 0;
    else iVar3 = print_formatted(param_1,0x000f0ee3,iVar2);
    if ((param_10 & 2) != 0) {
      if ((param_10 & 0x44) == 0) {
        uVar4 = print_formatted(param_1,0x000f0ee7,param_2);
      } else {
        uVar4 = U32(0x2000a0e4);
        if (uVar4 != 0) {
          uVar9 = (param_2 / U32(0x2000a0e0)) / uVar4;
          uVar7 = (param_2 / U32(0x2000a0e0) - uVar4 * uVar9) * 1000;
          uVar10 = uVar7 / uVar4;
          uVar4 = print_formatted(param_1,0x000f0ef0,uVar9/0xe10,(uVar9%0xe10)/0x3c,
                               (uVar9%0xe10)%0x3c,uVar10,((uVar7 - uVar4*uVar10)*1000)/uVar4);
        }
      }
      iVar3 = iVar3 + uVar4;
    }
    if ((param_10 & 1) != 0) {
      iVar2 = U32(0x0008acc4 + uVar8*4);
      if (iVar2 == 0) iVar2 = 0x000f0ed2;
      print_formatted(param_1,0x000a8c37,iVar2);
    }
    if ((param_10 & 8) == 0) iVar2 = 0;
    else iVar2 = print_formatted(param_1,0x000f0f0c,U32(0x0008acd8 + uVar8*4));
    if (param_3 != 0) {
      iVar5 = print_formatted(param_1,0x000f0f12,param_3);
      iVar2 = iVar2 + iVar5;
    }
    if (param_4 != 0) {
      iVar5 = print_formatted(param_1,0x000f0f16,param_4);
      iVar2 = iVar2 + iVar5;
    }
    iVar2 = iVar2 + iVar3;
    uVar6 = 0x0004daad;
    if (param_7 != 0) goto LAB_dc74;
    uVar6 = 0x000a7993;
    uVar1 = 0x000f7b6f;
    if (param_9 != 0) goto LAB_dcaa;
  }
  if ((int)(param_10 << 0x1f) < 0) {
    print_formatted(param_1,0x000a8c37,0x000f0ed2);
  }
  newline_print(param_1,param_10);
LAB_dd7a:
  log_output_flush(param_1);
  return;
}
