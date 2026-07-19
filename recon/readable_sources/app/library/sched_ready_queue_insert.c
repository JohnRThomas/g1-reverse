#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_thread__param_0408                   [param_0408; library]
 * Raw function identity: 0x00073840.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00073840 @ 0x00073840
 * public-name: sched_ready_queue_insert
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   sched_ready_queue_insert                 <= FUN_00073840 @ 0x00073840
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84d6                             @ 0x000f84d6
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_00073840 @ 0x73840  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void sched_update_cache(int,...);
extern void assert_post_action(int,...);
extern void printk(int,...);
void sched_ready_queue_insert(int *param_1){
  if( *(int8_t*)((int)param_1+0xd) < 0
      || (*(uint8_t*)((int)param_1+0xd) & 0x1f)!=0
      || param_1[6]!=0 ) return;
  *(uint8_t*)((int)param_1+0xd) = *(uint8_t*)((int)param_1+0xd) | 0x80;
  int iVar1 = ((unsigned long)&_kernel) /*=0x2000b448*/;
  if(param_1 == (int*)0x20006720){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f84d6) /*=0xf84d6*/,((unsigned long)&rodata_f82f4) /*=0xf82f4*/,0xc1);
    assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/,0xc1);
  }
  unsigned *puVar2 = (unsigned*)(((unsigned long)&_kernel) /*=0x2000b448*/+0x1c);
  unsigned *puVar3 = 0;
  if((unsigned*)*puVar2 != puVar2) puVar3 = (unsigned*)*puVar2;
  unsigned *puVar4 = *(unsigned**)(((unsigned long)&_kernel) /*=0x2000b448*/+0x20);
  for(; puVar3!=0; puVar3=(unsigned*)*puVar3){
    if( *(int8_t*)((int)param_1+0xe) != *(int8_t*)((int)puVar3+0xe)
        && *(int8_t*)((int)param_1+0xe) < *(int8_t*)((int)puVar3+0xe) ){
      puVar2 = (unsigned*)puVar3[1];
      *param_1 = (int)puVar3;
      param_1[1] = (int)puVar2;
      *puVar2 = (unsigned)param_1;
      puVar3[1] = (unsigned)param_1;
      goto LAB;
    }
    if(puVar3==puVar4) break;
  }
  *param_1 = (int)puVar2;
  param_1[1] = (int)puVar4;
  *puVar4 = (unsigned)param_1;
  *(int**)(iVar1+0x20) = param_1;
LAB:
  sched_update_cache(0);
}
