#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_net_buf__param_0172                    [param_0172; library]
 * Raw function identity: 0x0005f24c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005f24c @ 0x0005f24c
 * public-name: net_buf_unref
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_queue_prepend                          <= FUN_00086518 @ 0x00086518
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f45be                             @ 0x000f45be
 *   rodata_f539a                             @ 0x000f539a
 *   acl_tx_pool                              @ 0x20003a7c
 */
/* Reconstructed FUN_0005f24c @ 0x5f24c  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
extern void k_queue_prepend(int,int);
typedef void (*release_fn_t)(int object);

void net_buf_unref(int param_1){
  const uintptr_t class_table = ((unsigned long)&acl_tx_pool) /*=0x20003a7c*/;
  unsigned char refs;
  int next;
  release_fn_t release;
  if(param_1==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f45be) /*=0xf45be*/,((unsigned long)&rodata_f539a) /*=0xf539a*/,0x1d3);
    assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/,0x1d3);
    k_queue_prepend(((unsigned long)&acl_tx_pool) /*=0x20003a7c*/, 0);
    return;
  }
  do{
    next=*(int*)(param_1+4);
    refs=(unsigned char)(*(unsigned char*)(param_1+8)-1);
    *(unsigned char*)(param_1+8)=refs;
    if(refs!=0) return;
    if(*(int*)(param_1+0x14)!=0){
      if((*(unsigned char*)(param_1+9)&1)==0){
        uintptr_t ops=*(uintptr_t*)((unsigned int)*(unsigned char*)(param_1+10)*0x34+class_table+0x2c);
        release=*(release_fn_t*)(ops+8);
        release(param_1);
      }
      *(int*)(param_1+0x14)=0;
    }
    *(int*)(param_1+0xc)=0;
    *(int*)(param_1+4)=0;
    release=*(release_fn_t*)((unsigned int)*(unsigned char*)(param_1+10)*0x34+class_table+0x28);
    if(release==0) k_queue_prepend((int)((unsigned int)*(unsigned char*)(param_1+10)*0x34+class_table),param_1);
    else release(param_1);
    param_1=next;
  }while(next!=0);
}
