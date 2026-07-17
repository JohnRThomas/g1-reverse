#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00056a68 @ 0x00056a68
 * public-name: FUN_00056a68
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_set_state                       <= FUN_00056704 @ 0x00056704
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3dad                             @ 0x000f3dad
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Reconstructed FUN_00056a68 @ 0x56a68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
extern int FUN_00080ed8(unsigned int);
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
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f7a30) /*=0xf7a30*/,((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x5d9);
    printk(((unsigned long)&rodata_f3dad) /*=0xf3dad*/,*(unsigned char*)((int)param_1+2));
    assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x5d9);
    /* fallthrough */
  case 7:
    iVar1=FUN_00080ed8(*param_1);
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
