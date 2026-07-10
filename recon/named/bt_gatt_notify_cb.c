/* named: bt_gatt_notify_cb */
/* globals referenced:
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed bt_gatt_notify_cb @ 0x5b754  (parity: 300/300 trials, PROVEN) */

extern int bt_gatt_attr_get_handle();
extern int bt_gatt_foreach_attr_type(int,...);
extern int gatt_notify(int,...);
extern int assert_post_action(int,...);
extern int printk(int,...);
extern int bt_uuid_cmp(int,...);
extern int FUN_0008270c(int,...);
extern int bt_gatt_attr_value_handle();

int bt_gatt_notify_cb(int param_1, int *param_2)
{
  int iVar1;
  int uVar2;
  unsigned char local_28[2];
  unsigned short local_26;
  unsigned int *local_24;
  unsigned short local_20;
  int local_1c;
  unsigned short local_18;
  int *local_14;

  if (param_2 == 0) {
    printk(0x99cbd, 0xf4b3d, 0xf46b8, 0xae3);
    printk(0xf4a0a);
    uVar2 = 0xae3;
  } else {
    if (param_2[1] != 0 || param_2[0] != 0) {
      iVar1 = FUN_0008270c(0x200020d4);
      if (-1 < (iVar1 << 0x1d)) {
        return 0xfffffff5;
      }
      if (param_1 != 0 && *(char*)(param_1+0xd) != 7) {
        return 0xffffff80;
      }
      local_24 = (unsigned int*)param_2[1];
      iVar1 = bt_gatt_attr_get_handle();
      local_20 = (unsigned short)iVar1;
      if (param_2[0] == 0) {
        if (iVar1 != 0) goto LAB;
      } else {
        local_24 = 0;
        bt_gatt_foreach_attr_type(iVar1, 0xffff, param_2[0], 0, 1, 0x825fb, &local_24);
        if (local_24 != 0) {
          param_2[1] = (int)local_24;
LAB:
          local_28[0] = 0;
          local_26 = 0x2803;
          iVar1 = bt_uuid_cmp(*local_24, local_28);
          if (iVar1 == 0) {
            if (-1 < (int)((unsigned int)(*(unsigned char*)(local_24[3]+6)) << 0x1b)) {
              return 0xffffffea;
            }
            local_20 = (unsigned short)bt_gatt_attr_value_handle();
          }
          if (param_1 != 0) {
            uVar2 = gatt_notify(param_1, local_20, param_2);
            return uVar2;
          }
          local_1c = 0xffffff80;
          local_26 = 0x2902;
          local_18 = 1;
          local_28[0] = 0;
          local_14 = param_2;
          bt_gatt_foreach_attr_type(local_20, 0xffff, local_28, 0, 1, 0x5b891, &local_24);
          return local_1c;
        }
      }
      return 0xfffffffe;
    }
    printk(0x99cbd, 0xf4b44, 0xf46b8, 0xae4);
    printk(0xf4a0a);
    uVar2 = 0xae4;
  }
  assert_post_action(0xf46b8, uVar2);
  return 0;
}

