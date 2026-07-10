#include "g1_app_symbols.h"
/* named: FUN_00054d18 */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed FUN_00054d18 @ 0x54d18  (parity: 300/300 trials, PROVEN) */

extern int FUN_000530b4(void);
extern int id_find(void*);
extern int FUN_00080d3a(void);
extern int bt_addr_le_create_static(void*);
extern int bt_addr_le_eq(int,unsigned);
extern int FUN_00080fb4(unsigned);
extern int FUN_00080fc4(int,int);
int FUN_00054d18(int param_1,int param_2,unsigned param_3){
  int iVar1,iVar2;
  int iStack_18,iStack_14; unsigned uStack_10;
  iStack_18=param_1; iStack_14=param_2; uStack_10=param_3;
  if(param_2==0 || (iVar1=bt_addr_le_eq(param_2,((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/), iVar1!=0)){
    do{
      iVar1=bt_addr_le_create_static(&iStack_18);
      if(iVar1!=0) return iVar1;
      iVar1=id_find(&iStack_18);
    } while(iVar1 >= 0);
    iVar2=FUN_00080fc4(param_1*7+((uintptr_t)&g_ble_dev_state) /*=0x20002000*/, (int)&iStack_18);
    iVar1=param_2;
    if(param_2==0) goto LAB;
  } else {
    iVar1=((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + param_1*7;
    iVar2=param_2;
  }
  FUN_00080fc4(iVar1,iVar2);
  LAB:
  iVar1=FUN_00080fb4(((uintptr_t)&g_ble_dev_ncmd_sem) /*=0x200020d4*/);
  if((iVar1<<0x1d) < 0){ FUN_000530b4(); FUN_00080d3a(); }
  return 0;
}

