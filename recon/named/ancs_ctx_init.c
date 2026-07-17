/* readable reconstruction; identity: FUN_00018208 @ 0x00018208
 * public-name: ancs_ctx_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_ctx_init                            <= FUN_00018208 @ 0x00018208
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_notify_config_change_if_connected_THUMB @ 0x00017e85
 *   ADDR_init_ble_work_thread_THUMB          @ 0x0002201d
 *   g_settings_notify_mutex                  @ 0x20006a1c
 *   g_ble_conn_ctx_ptr                       @ 0x20006a30
 */
/* Reconstructed FUN_00018208 @ 0x18208  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void kmutex_dlist_init(unsigned);
extern void z_impl_k_sem_init(void*,int,int);
extern unsigned malloc(int);
extern void memset_bytes(unsigned,int,int,unsigned);
void ancs_ctx_init(uint32_t *param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  uint32_t *puVar1; unsigned uVar2;
  param_1[0x93]=(uint32_t)(param_1+0xe5);
  *param_1=0x2201d;
  kmutex_dlist_init(0x20006a1c);
  param_1[3]=0x17e85;
  z_impl_k_sem_init(param_1+0x86,0,1);
  z_impl_k_sem_init(param_1+0x8c,0,2);
  param_1[0x94]=(uint32_t)(param_1+0x230);
  puVar1=(uint32_t*)0x20006a30;
  *(volatile uint8_t*)((int)param_1+0x365)=0;
  *(volatile uint8_t*)((int)param_1+0x366)=0;
  *(volatile uint8_t*)((int)(param_1+0xd9))=0;
  *(volatile uint32_t*)puVar1=(uint32_t)param_1;
  uVar2=malloc(0x15);
  param_1[0x95]=uVar2;
  memset_bytes(uVar2,0,0x15,param_4);
  return;
}
