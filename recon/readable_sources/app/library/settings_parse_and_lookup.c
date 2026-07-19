#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e540 @ 0x0004e540
 * public-name: settings_parse_and_lookup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_parse_and_lookup                <= FUN_0004e540 @ 0x0004e540
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   settings_name_steq                       <= FUN_0007f1a0 @ 0x0007f1a0
 * address symbols (name @ address):
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0d20                             @ 0x000f0d20
 *   rodata_f1126                             @ 0x000f1126
 *   rodata_f1158                             @ 0x000f1158
 *   g_settings_handlers                      @ 0x2000a10c
 */
/* Reconstructed FUN_0004e540 @ 0x4e540  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,...);
extern int settings_name_steq(uint32_t,uint32_t,void*);

uint32_t* settings_parse_and_lookup(uint32_t param_1, uint32_t *param_2, uint32_t param_3){
  uint32_t *puVar1, *puVar3, *puVar5;
  int *piVar4;
  int iVar2;
  uint32_t uVar6, uVar7;
  volatile uint32_t *local_24;
  volatile uint32_t uStack_20;
  if (param_2 != 0) *param_2 = 0;
  puVar1 = (uint32_t*)0x88328;
  puVar5 = 0;
  puVar3 = (uint32_t*)((unsigned long)&__settings_handler_static_list_start) /*=0x882b0*/;
  uVar7 = param_1;
  local_24 = param_2;
  uStack_20 = param_3;
  while (1){
    if (puVar1 < puVar3){
      printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f1158) /*=0xf1158*/, ((unsigned long)&rodata_f1126) /*=0xf1126*/, 0x94, uVar7);
      printk(((unsigned long)&rodata_f0d20) /*=0xf0d20*/);
      assert_post_action(((unsigned long)&rodata_f1126) /*=0xf1126*/, 0x94);
    }
    if (puVar1 <= puVar3) break;
    uVar6 = *puVar3;
    iVar2 = settings_name_steq(param_1, uVar6, (void*)&local_24);
    if (iVar2 != 0 && (puVar5 == 0 || (iVar2 = settings_name_steq(uVar6, *puVar5, 0), iVar2 != 0))
        && (puVar5 = puVar3, param_2 != 0)){
      *param_2 = (uint32_t)local_24;
    }
    puVar3 = puVar3 + 5;
  }
  for (piVar4 = (int*)*(volatile uint32_t*)((unsigned long)&g_settings_handlers) /*=0x2000a10c*/; piVar4 != 0; piVar4 = (int*)*piVar4){
    uVar7 = piVar4[-5];
    iVar2 = settings_name_steq(param_1, uVar7, (void*)&local_24);
    if (iVar2 != 0 && ((puVar5 == 0 || (iVar2 = settings_name_steq(uVar7, *puVar5, 0), iVar2 != 0))
        && (puVar5 = (uint32_t*)(piVar4 - 5), param_2 != 0))){
      *param_2 = (uint32_t)local_24;
    }
  }
  return puVar5;
}
