/* named: FUN_00055e74 */
/* globals referenced:
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed FUN_00055e74 @ 0x55e74  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0004d944(uint32_t,int,void*);
extern int bt_hci_cmd_create(int,int);
extern int FUN_00053d70(int,int,int);
extern void* net_buf_simple_add(int,int);

int FUN_00055e74(uint32_t *param_1, int param_2, uint32_t param_3, uint32_t param_4){
  volatile int *piVar1 = (volatile int*)0x2000ac70UL;
  int iVar2;
  volatile uint32_t *puVar3;
  uint32_t *puVar4, *puVar5;
  volatile uint32_t local_28, local_24, uStack_18;
  volatile int iStack_20;
  if (*(volatile int*)0x2000ac70UL == param_2) return -0x78;
  if ((*(volatile int*)0x2000ac70UL == 0) && ((*(volatile int*)0x200020d4UL << 0x1a) >= 0)){
    if ((*(volatile int*)0x200020d4UL << 0x1b) >= 0) return -0x7d;
    *(volatile int*)0x2000ac70UL = param_2;
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
      iVar2 = FUN_00053d70(0x2026, iVar2, 0);
      if (iVar2 == 0) return 0;
    }
    *piVar1 = 0;
    local_24 = 0xf39f4;
    local_28 = 3;
    iStack_20 = iVar2;
    FUN_0004d944(0x88120, 0x1880, (void*)&local_28);
    return iVar2;
  }
  return -0x10;
}

