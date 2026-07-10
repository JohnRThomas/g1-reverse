/* named: gatt_disconnected */
/* Reconstructed gatt_disconnected @ 0x5c87c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int find_cf_cfg_by_addr(int,int);
extern int bt_gatt_store_cf(int,int);
extern int bt_gatt_store_ccc(int,int);
extern int bt_addr_le_is_bonded(int,int);
extern int FUN_000828da(int,int);
extern int bt_gatt_foreach_attr_0(int,int,int,void*);
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
    FUN_000828da(iVar2+1, param_3);
    if(iVar1 != 0){
      bt_gatt_store_cf(*(volatile uint8_t*)(param_1+8), iVar3);
    }
  }
}

