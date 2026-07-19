#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_14         => struct g1_layout_l2cap_connected_locals__stack_1191     [stack_1191; G1-original]
 * Raw function identity: 0x0005791c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005791c @ 0x0005791c
 * public-name: bt_l2cap_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_chan_add                           <= FUN_00057874 @ 0x00057874
 *   bt_l2cap_connected                       <= FUN_0005791c @ 0x0005791c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_87fc8                             @ 0x00087fc8
 *   rodata_87fec                             @ 0x00087fec
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0d20                             @ 0x000f0d20
 *   rodata_f3f55                             @ 0x000f3f55
 *   rodata_f402a                             @ 0x000f402a
 */
/* Reconstructed FUN_0005791c @ 0x5791c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int l2cap_chan_add(int,int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
void bt_l2cap_connected(int param_1,int param_2){
  uint16_t *puVar2=(uint16_t*)((unsigned long)&rodata_87fec) /*=0x87fec*/;
  uint16_t *puVar5=(uint16_t*)((unsigned long)&rodata_87fc8) /*=0x87fc8*/;
  int local_14=param_2;
  while(1){
    if(puVar2<puVar5){ printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f402a) /*=0xf402a*/,((unsigned long)&rodata_f3f55) /*=0xf3f55*/,0x185,param_1); printk(((unsigned long)&rodata_f0d20) /*=0xf0d20*/); assert_post_action(((unsigned long)&rodata_f3f55) /*=0xf3f55*/,0x185); }
    if(puVar2<=puVar5) break;
    int iVar3 = (*(int(**)(int,void*))(puVar5+2))(param_1,&local_14);
    if(iVar3>=0){
      uint16_t uVar1=*puVar5;
      *(volatile uint16_t*)(local_14+0x14)=uVar1;
      *(volatile uint16_t*)(local_14+0x24)=uVar1;
      iVar3=l2cap_chan_add(param_1,local_14,*(int*)(puVar5+4));
      if(iVar3==0) return;
      if(*(void**)(*(int*)(local_14+4))!=0){ (*(void(**)(void))(*(int*)(local_14+4)))(); }
      *(volatile unsigned*)(local_14+0x10) |= 1;
      void *pcVar4=*(void**)(*(int*)(local_14+4)+0x1c);
      if(pcVar4!=0){ (*(void(*)(int,int))pcVar4)(local_14,local_14+0x10); }
    }
    puVar5=puVar5+6;
  }
}
