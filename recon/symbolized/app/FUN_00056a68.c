#include "g1_app_symbols.h"
/* named: FUN_00056a68 */
/* Reconstructed FUN_00056a68 @ 0x56a68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
extern int bt_hci_disconnect(unsigned int);
extern void ble_conn_set_state(void*,unsigned int);
extern int default_tail(void);
int FUN_00056a68(unsigned short* param_1, unsigned char param_2){
  int iVar1; unsigned int uVar2;
  switch(*(unsigned char*)((int)param_1+0xd)){
  case 2:
    *(unsigned char*)((int)param_1+0xc)=param_2;
    uVar2=0;
    break;
  case 6:
    if(*(char*)((int)param_1+2)==1) return 0;
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,((uintptr_t)&rodata_f7a30) /*=0xf7a30*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/,0x5d9);
    printk("\tInvalid conn type %u\n" /*=0xf3dad*/,*(unsigned char*)((int)param_1+2));
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/,0x5d9);
    /* fallthrough */
  case 7:
    iVar1=bt_hci_disconnect(*param_1);
    if(iVar1!=0) return iVar1;
    if(*(char*)((int)param_1+0xd)!=7) return 0;
    uVar2=8;
    break;
  case 8:
    return 0;
  default:
    return default_tail();
  }
  ble_conn_set_state(param_1,uVar2);
  return 0;
}

