#include "g1_app_symbols.h"
/* named: bt_send */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed bt_send @ 0x54a44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int hci_vs_init(void);
extern int FUN_00052edc(void);
extern void FUN_00071eac(unsigned,unsigned,int,unsigned,int,int,int,int);
extern void FUN_00072fdc(int);
extern void k_work_queue_init(unsigned);
extern void k_work_queue_start(unsigned,unsigned,int,int,int);
extern int atomic_or(unsigned,int);
extern void FUN_00080ea2(unsigned,unsigned,void*);
extern unsigned atomic_and_3(int,unsigned);
extern void posix_stub_enosys(unsigned,unsigned);
extern void z_impl_k_queue_init(int);
extern void z_impl_k_sem_init(int,int);
typedef int (*cf)(void);
int bt_send(int param_1)
{
  int iVar1 = ((uintptr_t)&g_ble_dev_state) /*=0x20002000*/, iVar3; unsigned uVar2;
  int local_40, local_38; unsigned local_3c, uStack_34, local_20, local_1c;
  if (*(int*)(iVar1 + 0x168) == 0) {
    iVar3 = -0x13; local_1c = "No HCI driver registered" /*=0xf3376*/; local_20 = 2;
    FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1040, &local_20);
  } else {
    uVar2 = atomic_and_3(iVar1 + 0xd4, 0xfffffffd);
    iVar3 = atomic_or(uVar2, 1);
    if (iVar3 << 0x1f < 0) {
      iVar3 = -0x78;
    } else {
      iVar3 = FUN_00052edc();
      if (iVar3 == 0) {
        *(volatile int*)((uintptr_t)&ready_cb) /*=0x2000ac6c*/ = param_1;
        z_impl_k_sem_init(iVar1 + 0x128, 1);
        z_impl_k_queue_init(iVar1 + 0x14c);
        local_38 = 0; uStack_34 = 0; local_40 = iVar3;
        FUN_00071eac(((uintptr_t)&rx_thread_data) /*=0x20005e30*/, ((uintptr_t)&rx_thread_stack) /*=0x2002bb80*/, 0x400, ((uintptr_t)&tbl_545e8) /*=0x545f1*/, 0, 0, 0, 0xfffffff7);
        posix_stub_enosys(((uintptr_t)&rx_thread_data) /*=0x20005e30*/, "BT TX" /*=0xf338f*/);
        k_work_queue_init(((uintptr_t)&bt_workqueue) /*=0x20005f08*/);
        k_work_queue_start(((uintptr_t)&bt_workqueue) /*=0x20005f08*/, ((uintptr_t)&bt_workqueue_stack) /*=0x2002bf80*/, 0x898, 0xfffffff8, 0);
        posix_stub_enosys(((uintptr_t)&bt_workqueue) /*=0x20005f08*/, "BT RX" /*=0xf3395*/);
        iVar3 = (*(cf*)(*(int*)(iVar1 + 0x168) + 0xc))();
        if (iVar3 == 0) {
          if (param_1 == 0) iVar3 = hci_vs_init();
          else FUN_00072fdc(iVar1 + 0xc4);
        } else {
          local_3c = "HCI driver open failed (%d)" /*=0xf339b*/; local_40 = 3; local_38 = iVar3;
          FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, &local_40);
        }
      }
    }
  }
  return iVar3;
}

