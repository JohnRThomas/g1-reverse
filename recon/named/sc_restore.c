/* named: sc_restore */
/* globals referenced:
//   0x20002a20  g_bt_gatt_sc_ccc             
*/
/* Reconstructed sc_restore @ 0x5b554  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000569a0(int,...);
extern int find_sc_cfg_59bcc(int,...);
extern int bt_gatt_indicate(int,...);
extern int bt_conn_get_security(int,...);
extern int bt_conn_is_peer_addr_le(int,...);
extern int gatt_ccc_changed(int,...);
extern int FUN_00082a42(int,...);
extern int bt_gatt_check_perm(int,...);
unsigned int sc_restore(int param_1, int param_2, int *param_3)
{
  int dummy[16];
  int iVar8 = *param_3;
  if (*(int*)(param_1+8) == 0x5a465) {
    unsigned char *puVar9 = *(unsigned char**)(param_1+0xc);
    if ((*(short*)(puVar9+8) != 0) &&
        (bt_conn_is_peer_addr_le(iVar8, *puVar9, (int)(puVar9+1)) != 0)) {
      int local_48 = bt_gatt_check_perm(iVar8, param_1, 0x12a);
      if (local_48 != 0) {
        if (local_48 == 3) {
          FUN_00082a42(0x88128, 0x1880, dummy);
          return 1;
        }
        unsigned int uVar10 = (local_48 == 5) ? 3 : 2;
        unsigned int uVar5 = (unsigned int)bt_conn_get_security(iVar8);
        if (uVar5 < uVar10) {
          if (uVar10 <= *(unsigned char*)((int)param_3+4)) return 1;
          *(char*)((int)param_3+4) = (char)uVar10;
          return 1;
        }
      }
      gatt_ccc_changed(param_1, (int)puVar9);
      if (puVar9 == (unsigned char*)0x20002a20UL) {
        int iVar4 = find_sc_cfg_59bcc(*(unsigned char*)(iVar8+8), iVar8+0x90);
        if ((iVar4 != 0) && ((*(short*)(iVar4+8) != 0) || (*(short*)(iVar4+10) != 0))) {
          int iVar6 = FUN_000569a0(iVar8);
          unsigned short uVar1 = *(unsigned short*)(iVar4+10);
          *(volatile unsigned short*)(0x2000ff14UL + iVar6*4) = *(unsigned short*)(iVar4+8);
          *(volatile unsigned short*)(0x2000ff14UL + iVar6*4 + 2) = uVar1;
          int iVar7 = iVar6*0x18 + 0x2000aebc;
          *(volatile int*)(iVar7+0x10) = 0x2000ff14 + (short)iVar6*4;
          *(volatile int*)(iVar7+4) = 0x8b3dc;
          *(volatile int*)(iVar7+8) = 0x82bd5;
          *(volatile unsigned short*)(iVar7+0x14) = 4;
          int r = bt_gatt_indicate(iVar8, 0x2000aebc + (short)iVar6*0x18);
          if (r != 0) {
            FUN_00082a42(0x88128, 0x1040, dummy);
          }
        }
      }
    }
  }
  return 1;
}

