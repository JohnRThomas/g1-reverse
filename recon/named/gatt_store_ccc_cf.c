/* readable reconstruction; identity: FUN_00082f3a @ 0x00082f3a
 * public-name: gatt_store_ccc_cf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   gatt_store_ccc_cf                        <= FUN_00082f3a @ 0x00082f3a
 */
/* Reconstructed gatt_store_ccc_cf @ 0x00082f3a from NCS 2.5.1 gatt.c.
 * Raw backmap: FUN_00082f3a@0x00082f3a. */

#include <stdint.h>
#define gatt_store_ccc_cf gatt_store_ccc_cf
extern uint8_t *find_sc_cfg_59b94(uint32_t id,const void *peer);
extern int bt_addr_le_is_bonded(uint32_t id,const void *peer);
extern int32_t atomic_and_4(volatile int32_t *target,int32_t value);
extern void bt_gatt_store_ccc(uint32_t id,const void *peer);
extern void bt_gatt_store_cf(uint32_t id,const void *peer);
extern int32_t read_struct_first_word(volatile int32_t *target); /* atomic_get */
void gatt_store_ccc_cf(uint32_t id,const void *peer)
{
 uint8_t *entry=find_sc_cfg_59b94(id,peer);
 if(bt_addr_le_is_bonded(id,peer)!=0 && entry!=0){
  volatile int32_t *flags=(volatile int32_t*)(entry+8u);
  if((atomic_and_4(flags,-2)&1)!=0)bt_gatt_store_ccc(id,peer);
  if((atomic_and_4(flags,-3)&2)!=0)bt_gatt_store_cf(id,peer);
  if(read_struct_first_word(flags)==0){
   entry[0]=0;*(uint32_t*)(entry+1u)=0;*(uint32_t*)(entry+4u)=0;
   __atomic_store_n(flags,0,__ATOMIC_SEQ_CST);
  }
 }
}
