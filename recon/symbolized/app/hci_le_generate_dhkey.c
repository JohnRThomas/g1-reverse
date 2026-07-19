#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055e74 @ 0x00055e74
 * public-name: hci_le_generate_dhkey
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   hci_le_generate_dhkey                    <= FUN_00055e74 @ 0x00055e74
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 * address symbols (name @ address):
 *   rodata_88120                             @ 0x00088120
 *   rodata_f39f4                             @ 0x000f39f4
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 *   g_bt_dh_key_cb                           @ 0x2000ac70
 */
/* Reconstructed FUN_00055e74 @ 0x55e74  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void z_log_msg_runtime_create(uint32_t,int,void*);
extern int bt_hci_cmd_create(int,int);
extern int bt_hci_cmd_send_sync(int,int,int);
extern void* net_buf_simple_add(int,int);

int hci_le_generate_dhkey(uint32_t *param_1, int param_2, uint32_t param_3, uint32_t param_4){
  volatile int *piVar1 = (volatile int*)((unsigned long)&g_bt_dh_key_cb) /*=0x2000ac70*/;
  int iVar2;
  volatile uint32_t *puVar3;
  uint32_t *puVar4, *puVar5;
  volatile uint32_t local_28, local_24, uStack_18;
  volatile int iStack_20;
  if (*(volatile int*)((unsigned long)&g_bt_dh_key_cb) /*=0x2000ac70*/ == param_2) return -0x78;
  if ((*(volatile int*)((unsigned long)&g_bt_dh_key_cb) /*=0x2000ac70*/ == 0) && ((*(volatile int*)((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/ << 0x1a) >= 0)){
    if ((*(volatile int*)((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/ << 0x1b) >= 0) return -0x7d;
    *(volatile int*)((unsigned long)&g_bt_dh_key_cb) /*=0x2000ac70*/ = param_2;
    uStack_18 = param_4;
    iVar2 = bt_hci_cmd_create(0x2026,0x40);
    if (iVar2 == 0){
      iVar2 = -0x69;
    } else {
      puVar3 = (volatile uint32_t*)net_buf_simple_add(iVar2+0xc,0x40);
      puVar4 = param_1;
      do {
        puVar5 = puVar4 + 1;
        *puVar3 = *puVar4;
        puVar3 = puVar3 + 1;
        puVar4 = puVar5;
      } while (puVar5 != param_1 + 0x10);
      iVar2 = bt_hci_cmd_send_sync(0x2026, iVar2, 0);
      if (iVar2 == 0) return 0;
    }
    *piVar1 = 0;
    local_24 = ((unsigned long)&rodata_f39f4) /*=0xf39f4*/;
    local_28 = 3;
    iStack_20 = iVar2;
    z_log_msg_runtime_create(((unsigned long)&rodata_88120) /*=0x88120*/, 0x1880, (void*)&local_28);
    return iVar2;
  }
  return -0x10;
}
