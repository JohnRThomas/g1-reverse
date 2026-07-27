/* readable reconstruction; identity: FUN_000562a4 @ 0x000562a4
 * public-name: ble_conn_pool_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_pool_alloc                      <= FUN_000562a4 @ 0x000562a4
 *   k_work_init                              <= FUN_00072e50 @ 0x00072e50
 *   k_work_init_delayable                    <= FUN_000732d4 @ 0x000732d4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_ble_conn_process_complete_or_disconnect_THUMB @ 0x000570a1
 *   rodata_813d1                             @ 0x000813d1
 */
/* Reconstructed FUN_000562a4 @ 0x562a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void k_work_init(struct k_work *, void (*)(struct k_work *));
extern void k_work_init_delayable(struct k_work_delayable *, void (*)(struct k_work *));
extern void memset_bytes(void*, int, int);
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
  k_work_init_delayable(param_1+0x60, 0x000570a1);
  k_work_init(param_1+0x28, 0x000813d1);
  return param_1;
}
