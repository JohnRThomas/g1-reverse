/* named: gatt_connected */
/* globals referenced:
//   0x2000af18  g_known_device_table         
*/
/* Reconstructed gatt_connected @ 0x5c8d8  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005306c(unsigned,int);
extern int find_cf_cfg_by_addr(unsigned,int);
extern int bt_gatt_clear_sc(unsigned,int);
extern void FUN_0005a39c(void);
extern int bt_addr_le_eq_0(int,int);
extern void list_unlink_and_release(int,int,int,void*);
extern void bt_gatt_foreach_attr_0(int,int,int,void*);
int gatt_connected(unsigned param_1, int param_2, int param_3){
  int local_20 = param_2;
  int iVar1, iVar2, iVar4;
  int *piVar3;
  (void)param_3;
  bt_gatt_foreach_attr_0(1, 0xffff, 0x0005a2d5, &local_20);
  iVar1 = FUN_0005306c(param_1, param_2);
  if (iVar1 >= 0 && (iVar1 = bt_gatt_clear_sc(param_1,param_2)) >= 0){
    iVar1 = find_cf_cfg_by_addr(param_1,param_2);
    if (iVar1 != 0) FUN_0005a39c();
    iVar1 = FUN_0005306c(param_1,param_2);
    if (iVar1 >= 0){
      iVar4 = 0; iVar1 = 0x2000af19;
      do {
        if ((unsigned)*(volatile unsigned char*)(iVar1-1) == param_1 &&
            (iVar2 = bt_addr_le_eq_0(param_2, iVar1)) != 0){
          iVar4 = iVar4 + 0x2000af18;
          piVar3 = *(int**)(iVar4 + 8);
          if (piVar3 != 0){
            iVar1 = *piVar3;
            if (iVar1 != 0) iVar1 -= 0x18;
            *(volatile unsigned short*)((char*)piVar3 - 8) = 0;
            list_unlink_and_release(0, iVar4, 0, piVar3 - 6);
            if (iVar1 != 0){
              while ((iVar2 = *(volatile int*)(iVar1+0x18)) != 0){
                *(volatile unsigned short*)(iVar1+0x10) = 0;
                list_unlink_and_release(0, iVar4, 0, (void*)iVar1);
                iVar1 = iVar2 - 0x18;
              }
              *(volatile unsigned short*)(iVar1+0x10) = 0;
              list_unlink_and_release(0, iVar4, 0, (void*)iVar1);
            }
          }
          break;
        }
        iVar4 += 0x10;
        iVar1 += 0x10;
      } while (iVar4 != 0x30);
      iVar1 = 0;
    }
  }
  return iVar1;
}

