/* named: gatt_delayed_store_enqueue */
/* Reconstructed gatt_delayed_store_enqueue @ 0x59d24  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int find_sc_cfg_59b94(uint32_t,uint32_t);
extern void FUN_0007350c(uint32_t,uint32_t,int,int);
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,...);
extern int bt_addr_le_is_bonded(void);
extern void atomic_or_0(int,uint32_t);
extern int FUN_0008270c(uint32_t);
extern void FUN_000828da(int,uint32_t,int);

void gatt_delayed_store_enqueue(uint32_t param_1, uint32_t param_2, uint32_t param_3){
  int iVar2 = bt_addr_le_is_bonded();
  int iVar3 = find_sc_cfg_59b94(param_1, param_2);
  if (iVar2 == 0) return;
  if (iVar3 == 0){
    int iVar4;
    int t = FUN_0008270c(0x20006330);
    if (t == 0){ iVar2 = 0; iVar4 = 0; }
    else {
      t = FUN_0008270c(0x2000633c);
      if (t == 0){ iVar4 = 1; iVar2 = 0xc; }
      else {
        t = FUN_0008270c(0x20006348);
        if (t != 0){
          printk(0x99cbd,0xf1722,0xf46b8,0x577);
          printk(0xf46e8);
          assert_post_action(0xf46b8,0x577);
        }
        iVar4 = 2; iVar2 = 0x18;
      }
    }
    int iVar1 = 0x20006328;
    iVar3 = iVar2 + 0x20006328;
    FUN_000828da(0x20006328 + iVar2 + 1, param_2, iVar3);
    *(volatile char*)(iVar1 + iVar4*0xc) = (char)param_1;
  }
  atomic_or_0(iVar3 + 8, 1 << (param_3 & 0xff));
  FUN_0007350c(0x20006350, 0, 0x8000, 0);
}

