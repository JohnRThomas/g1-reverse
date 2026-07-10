/* named: gatt_ccc_settings_set */
/* Reconstructed gatt_ccc_settings_set @ 0x5af8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ccc_set_direct(int,...);
extern int strtol_ascii_scan(int,...);
extern int settings_name_steq(int,...);
extern int settings_name_next(int,...);
extern int bt_settings_decode_key(int,...);
extern int FUN_00082a42(int,...);
extern int bt_gatt_foreach_attr_0(int,...);
typedef int (*codeptr)(int,...);
unsigned int gatt_ccc_settings_set(int param_1,int param_2,codeptr param_3,int param_4,int param_5)
{
  int iVar1;
  unsigned int uVar2;
  int local_100, local_fc;
  unsigned int uStack_108;
  unsigned char af8[8];
  unsigned char ae0[16];
  int dummy[16];
  iVar1 = settings_name_steq(param_5, 0xf4a9e, &local_100);
  if (iVar1 == 0) {
    uVar2 = ccc_set_direct(0);
  } else {
    settings_name_next(local_100, &local_fc);
    if (local_100 == 0) {
      FUN_00082a42(0x88128, 0x1040, dummy);
    } else {
      if ((local_fc == 0) || (uStack_108 = strtol_ascii_scan(local_fc,0,10), uStack_108 == 0)) {
        iVar1 = bt_settings_decode_key(local_100, af8);
        if (iVar1 == 0) {
          if (param_2 == 0) {
          } else {
            unsigned int uStack_e4 = (unsigned int)param_3(param_4, (int)ae0, 0xc0);
            if ((int)uStack_e4 < 0) {
              FUN_00082a42(0x88128, 0x1840, dummy);
              return uStack_e4;
            }
          }
          bt_gatt_foreach_attr_0(1, 0xffff, 0x59ded, dummy);
          return 0;
        }
        FUN_00082a42(0x88128, 0x1c40, dummy);
      } else {
        FUN_00082a42(0x88128, 0x1840, dummy);
      }
    }
    uVar2 = 0xffffffea;
  }
  return uVar2;
}

