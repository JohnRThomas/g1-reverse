#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000562a4 @ 0x000562a4
 * public-name: ble_conn_pool_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_pool_alloc                      <= FUN_000562a4 @ 0x000562a4
 *   k_work_init                              <= FUN_00072e50 @ 0x00072e50
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_ble_conn_process_complete_or_disconnect_THUMB @ 0x000570a1
 *   rodata_813d1                             @ 0x000813d1
 */
/* Reconstructed FUN_000562a4 @ 0x562a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int k_work_init(int,int);
extern int FUN_000732d4(int,int);
extern void memset_bytes(void *,int,unsigned);
int ble_conn_pool_alloc(int param_1, int param_2, int param_3, int param_4){
  int iVar1 = 0;
  volatile int *piVar2;
  while(1){
    if(iVar1==param_2) return 0;
    piVar2 = (volatile int*)(param_1+0xd0);
    int expected = 0;
    if (__atomic_compare_exchange_n(piVar2, &expected, 1, 0,
                                    __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
      break;
    param_1 += 0xd8;
    iVar1 += 1;
  }
  if(param_1==0) return 0;
  memset_bytes((void *)param_1,0,0xd0);
  FUN_000732d4(param_1+0x60, ADDR_ble_conn_process_complete_or_disconnect_THUMB /*=0x570a1*/);
  k_work_init(param_1+0x28, ((unsigned long)&rodata_813d1) /*=0x813d1*/);
  return param_1;
}
