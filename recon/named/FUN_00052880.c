/* named: FUN_00052880 */
/* Reconstructed FUN_00052880 @ 0x52880  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000527dc(int,...);
extern int FUN_00056f4c(int,...);
extern int bt_gatt_notify_cb(int,...);
extern int mutex_lock_syscall_handler(int,...);
extern int FUN_000729fc(int,...);
extern int mutex_unlock_syscall_handler(int,...);
extern int FUN_00080c06(int,...);
extern int att_get_max_payload_len(int,...);
extern int memset_bytes(int,...);
extern int thunk_FUN_0005f24c(int,...);
unsigned int FUN_00052880(int param_1)
{
  unsigned char buf68[0x18];
  unsigned char buf50[0x28];
  int local_60;
  unsigned int uVar6, uVar4;
  memset_bytes((int)buf68, 0, 0x18);
  int iVar8 = *(int*)(param_1+0x18);
  local_60 = *(int*)(param_1+0xc);
  if ((iVar8 != 0) && (FUN_00056f4c(iVar8, (int)buf50) == 0) && (buf50[0x24] == 2)) {
    uVar4 = (unsigned int)att_get_max_payload_len(param_1);
    if (uVar4 == 0) { uVar6 = 1; goto DONE; }
    int iVar3 = FUN_000527dc(iVar8);
    if ((iVar3 != 0) && (*(unsigned char*)(iVar3+0x69) != 0) &&
        (*(unsigned char*)(param_1+0x1c) == *(unsigned char*)(iVar3+0x69))) {
      FUN_000729fc(iVar3+0x6c);
      unsigned int uVar7 = 0; int bVar2 = 0; unsigned int uVar5;
      while ((uVar6 = 0), (uVar5 = *(unsigned short*)(param_1+0x10)), (uVar7 < uVar5)) {
        if ((*(unsigned char*)(iVar3+0x69) == 0) ||
            (*(unsigned char*)(param_1+0x1c) != *(unsigned char*)(iVar3+0x69))) goto LAB_528a8;
        if ((int)uVar5 < (int)(uVar7 + uVar4)) uVar4 = (uVar5 - uVar7) & 0xffff;
        int r9 = bt_gatt_notify_cb(iVar8, (int)buf68);
        if (r9 == -0xc) {
          if (!bVar2) {
            if (uVar4 < 0x14) { uVar6 = 2; break; }
            uVar4 = (uVar4 << 0xf) >> 0x10;
          }
          mutex_unlock_syscall_handler(0);
        } else {
          if (r9 != 0) { uVar6 = 1; goto DONE; }
          unsigned short uVar1 = (unsigned short)((short)uVar7 + (short)uVar4);
          uVar7 = uVar1;
          local_60 = *(int*)(param_1+0xc) + uVar1;
          mutex_lock_syscall_handler(iVar3+0x6c, 0, 0xffffffff, 0xffffffff);
          bVar2 = 1;
        }
      }
      goto DONE;
    }
  }
LAB_528a8:
  uVar6 = 5;
DONE:
  FUN_00080c06(param_1+0x18);
  thunk_FUN_0005f24c(param_1);
  return uVar6;
}

