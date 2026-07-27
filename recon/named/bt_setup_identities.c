/* readable reconstruction; identity: FUN_000553f8 @ 0x000553f8
 * public-name: bt_setup_identities
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_id_set_static_random_addr             <= FUN_00054d18 @ 0x00054d18
 *   bt_id_create                             <= FUN_00055204 @ 0x00055204
 *   hci_read_static_addresses                <= FUN_00055350 @ 0x00055350
 *   bt_setup_identities                      <= FUN_000553f8 @ 0x000553f8
 *   bt_addr_copy                             <= FUN_00080fba @ 0x00080fba
 * address symbols (name @ address):
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_000553f8 @ 0x553f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_id_set_static_random_addr(int,void*);
extern int bt_id_create(int);
extern int hci_read_static_addresses(void*,int);
extern void bt_addr_copy(int, int);
int bt_setup_identities(void){
  uint8_t local30;
  uint8_t stack2f[7];
  uint8_t stack28[24];
  volatile uint8_t *g = (volatile uint8_t*)0x20002000UL;
  if(*(volatile uint8_t*)(g+7) == 0){
    int iVar1 = hci_read_static_addresses(stack28, 1);
    *(volatile uint8_t*)(g+7) = (uint8_t)iVar1;
    if(iVar1 != 0){
      uint8_t bVar4 = 0;
      do {
        uint32_t uVar3 = bVar4;
        if((uint32_t)*(volatile uint8_t*)(g+7) <= uVar3) return 0;
        bt_addr_copy(stack2f, stack28 + uVar3*0x16);
        local30 = 1;
        iVar1 = bt_id_set_static_random_addr((int)uVar3, &local30);
        bVar4++;
      } while(iVar1 == 0);
      return iVar1;
    }
  }
  return bt_id_create(0);
}
