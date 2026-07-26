/* readable reconstruction; identity: FUN_00073ec0 @ 0x00073ec0
 * public-name: add_thread_to_wait_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   unready_thread                           <= FUN_00073e88 @ 0x00073e88
 *   add_thread_to_wait_queue                 <= FUN_00073ec0 @ 0x00073ec0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84d6                             @ 0x000f84d6
 */
/* Reconstructed FUN_00073ec0 @ 0x73ec0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern void unready_thread(void);
extern void assert_post_action(uint32_t,uint32_t);
void add_thread_to_wait_queue(volatile int *param_1, volatile int *param_2, uint32_t param_3, uint32_t param_4){
  volatile int *piVar1,*piVar2;
  unready_thread();
  *(volatile uint8_t*)((int)param_1+0xd) = *(volatile uint8_t*)((int)param_1+0xd) | 2;
  piVar2=(volatile int*)0x20006720;
  if(param_2!=0){
    param_1[2]=(int)param_2;
    if(param_1==piVar2){
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0xf84d6,0xf82f4,0xc1,param_4);
      assert_post_action(0xf82f4,0xc1);
    }
    piVar2=(volatile int*)*param_2;
    if(param_2!=piVar2){
      for(;piVar2!=0;piVar2=(volatile int*)*piVar2){
        if((*(volatile int8_t*)((int)param_1+0xe)!=*(volatile int8_t*)((int)piVar2+0xe)) &&
           (*(volatile int8_t*)((int)param_1+0xe) < *(volatile int8_t*)((int)piVar2+0xe))){
          piVar1=(volatile int*)piVar2[1];
          *param_1=(int)piVar2;
          param_1[1]=(int)piVar1;
          *piVar1=(int)param_1;
          piVar2[1]=(int)param_1;
          return;
        }
        if(piVar2==(volatile int*)param_2[1]) break;
      }
    }
    piVar2=(volatile int*)param_2[1];
    *param_1=(int)param_2;
    param_1[1]=(int)piVar2;
    *piVar2=(int)param_1;
    param_2[1]=(int)param_1;
  }
}
