#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00071294 @ 0x00071294
 * public-name: rpmsg_virtio_send_copy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_virtio_tx_enqueue                  <= FUN_000710b4 @ 0x000710b4
 *   rpmsg_virtio_send_copy                   <= FUN_00071294 @ 0x00071294
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   metal_io_block_write                     <= FUN_00085508 @ 0x00085508
 *   rpmsg_virtio_get_tx_buffer_wait          <= FUN_00085b0c @ 0x00085b0c
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7ba6                             @ 0x000f7ba6
 *   rodata_f7c1a                             @ 0x000f7c1a
 */
/* Reconstructed FUN_00071294 @ 0x71294  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
typedef unsigned int uint;
extern unsigned long rpmsg_virtio_tx_enqueue(unsigned char*, unsigned long, unsigned long, unsigned char*, unsigned long);
extern void assert_post_action(const char *, unsigned int);
extern int metal_io_block_write(int*, unsigned int, int, int);
extern int rpmsg_virtio_get_tx_buffer_wait(int,int*,uint32_t,int,int,uint32_t,uint32_t);
uint32_t rpmsg_virtio_send_copy(int param_1,uint32_t param_2,uint32_t param_3,int param_4,int param_5,uint32_t param_6){
  int local_24=param_4;
  int iVar1=rpmsg_virtio_get_tx_buffer_wait(param_1,&local_24,param_6,param_4,param_1,param_2,param_3);
  uint32_t uVar4=0xfffff82e;
  if(iVar1!=0){
    int* piVar2=*(int* volatile*)(param_1+0xac);
    if(local_24<=param_5) param_5=local_24;
    uint uVar5=iVar1-*(volatile int*)piVar2;
    if((uint)*(volatile int*)(piVar2+2)<=uVar5) uVar5=0xffffffff;
    int iVar3=metal_io_block_write(piVar2,uVar5,param_4,param_5);
    if(param_5!=iVar3){
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7c1a) /*=0xf7c1a*/,((unsigned long)&rodata_f7ba6) /*=0xf7ba6*/,0x207);
      assert_post_action(((unsigned long)&rodata_f7ba6) /*=0xf7ba6*/,0x207);
    }
    uVar4=rpmsg_virtio_tx_enqueue(param_1,param_2,param_3,iVar1,param_5);
  }
  return uVar4;
}
