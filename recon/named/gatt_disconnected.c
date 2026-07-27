/* readable reconstruction; identity: FUN_0005c87c @ 0x0005c87c
 * public-name: gatt_disconnected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg_by_addr                      <= FUN_00059b5c @ 0x00059b5c
 *   bt_gatt_store_cf                         <= FUN_0005a8bc @ 0x0005a8bc
 *   bt_gatt_store_ccc                        <= FUN_0005c80c @ 0x0005c80c
 *   gatt_disconnected                        <= FUN_0005c87c @ 0x0005c87c
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   rodata_5a2fd                             @ 0x0005a2fd
 */
/* Reconstructed FUN_0005c87c @ 0x5c87c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int find_cf_cfg_by_addr(int,int);
extern void bt_gatt_store_cf(unsigned int, unsigned int);
extern int bt_gatt_store_ccc(unsigned int, unsigned int);
extern int bt_addr_le_is_bonded(unsigned char, const void*);
extern void bt_addr_le_copy_828da(void*, const void*);
extern void bt_gatt_foreach_attr_0(unsigned short, unsigned short, void*, void*);
void gatt_disconnected(int param_1, uint32_t param_2, uint32_t param_3){
  int iVar3 = param_1 + 0x90;
  uint32_t local[2];
  local[0] = param_2;
  local[1] = param_3;
  int iVar1 = bt_addr_le_is_bonded(*(volatile uint8_t*)(param_1+8), iVar3);
  bt_gatt_foreach_attr_0(1, 0xffff, 0x0005a2fd, local);
  if(iVar1 != 0){
    bt_gatt_store_ccc(*(volatile uint8_t*)(param_1+8), iVar3);
  }
  int iVar2 = find_cf_cfg_by_addr(*(volatile uint8_t*)(param_1+8), param_2);
  if(iVar2 != 0){
    bt_addr_le_copy_828da(iVar2+1, param_3);
    if(iVar1 != 0){
      bt_gatt_store_cf(*(volatile uint8_t*)(param_1+8), iVar3);
    }
  }
}
