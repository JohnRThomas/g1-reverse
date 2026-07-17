/* readable reconstruction; identity: FUN_000336a0 @ 0x000336a0
 * public-name: uart_read_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uart_read_start                          <= FUN_000336a0 @ 0x000336a0
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 * address symbols (name @ address):
 *   ADDR_uart_callback_THUMB                 @ 0x00033385
 *   rodata_a7b13                             @ 0x000a7b13
 *   rodata_a7b29                             @ 0x000a7b29
 *   rodata_a7b41                             @ 0x000a7b41
 *   g_uart_rx_mem_slab                       @ 0x200037b8
 */
/* Reconstructed FUN_000336a0 @ 0x336a0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int k_mem_slab_alloc(unsigned,void*,int,int,int);
typedef int (*fp1)(int,unsigned,int);
typedef int (*fp2)(int,unsigned,int,int);
unsigned uart_read_start(int param_1, unsigned param_2, unsigned param_3){
  int iVar1; unsigned local_14, uStack_10;
  if(param_1!=0){
    local_14=param_2; uStack_10=param_3;
    iVar1=k_mem_slab_alloc(0x200037b8,&local_14,0,0,param_1);
    if(iVar1==0){
      void **p = *(void***)(param_1+8);
      if((fp1)p[0]!=0 && (iVar1=((fp1)p[0])(param_1,0x33385,param_1))==0){
        void **p2 = *(void***)(param_1+8);
        iVar1=((fp2)p2[3])(param_1,local_14,0x100,10000);
        if(iVar1==0) return 0;
        DEBUG_PRINT(0xa7b41); return 0xfffffffd;
      }
      DEBUG_PRINT(0xa7b29); return 0xfffffffe;
    }
    DEBUG_PRINT(0xa7b13);
  }
  return 0xffffffff;
}
