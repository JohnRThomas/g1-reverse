#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054a44 @ 0x00054a44
 * public-name: bt_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hci_vs_init                              <= FUN_00012080 @ 0x00012080
 *   bt_settings_subsys_init_check            <= FUN_00052edc @ 0x00052edc
 *   bt_enable                                <= FUN_00054a44 @ 0x00054a44
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   k_work_submit                            <= FUN_00072fdc @ 0x00072fdc
 *   k_work_queue_init                        <= FUN_000730b4 @ 0x000730b4
 *   k_work_queue_start                       <= FUN_000730e8 @ 0x000730e8
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   atomic_and_3                             <= FUN_00080ea8 @ 0x00080ea8
 *   posix_stub_enosys                        <= FUN_00086412 @ 0x00086412
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   ADDR_hci_tx_thread_THUMB                 @ 0x000545f1
 *   rodata_88138                             @ 0x00088138
 *   rodata_f3376                             @ 0x000f3376
 *   rodata_f338f                             @ 0x000f338f
 *   rodata_f3395                             @ 0x000f3395
 *   rodata_f339b                             @ 0x000f339b
 *   g_ble_dev_state                          @ 0x20002000
 *   rx_thread_data                           @ 0x20005e30
 *   bt_workqueue                             @ 0x20005f08
 *   ready_cb                                 @ 0x2000ac6c
 *   rx_thread_stack                          @ 0x2002bb80
 *   bt_workqueue_stack                       @ 0x2002bf80
 */
/* Reconstructed FUN_00054a44 @ 0x54a44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int hci_vs_init(void);
extern int bt_settings_subsys_init_check(void);
extern void z_impl_k_thread_create(unsigned,unsigned,int,unsigned,int,int,int,int);
extern void k_work_submit(int);
extern void k_work_queue_init(unsigned);
extern void k_work_queue_start(unsigned,unsigned,int,int,int);
extern int atomic_or(volatile long*, long);
extern void bt_log_forward_3arg(unsigned,unsigned,void*);
extern long atomic_and_3(volatile long*, long);
extern void posix_stub_enosys(unsigned,unsigned);
#define z_impl_k_queue_init z_impl_k_queue_init
extern void z_impl_k_queue_init(void *queue);
extern void z_impl_k_sem_init(int,int);
typedef int (*cf)(void);
int bt_enable(int param_1)
{
  int iVar1 = ((unsigned long)&g_ble_dev_state) /*=0x20002000*/, iVar3; unsigned uVar2;
  int local_40, local_38; unsigned local_3c, uStack_34, local_20, local_1c;
  if (*(int*)(iVar1 + 0x168) == 0) {
    iVar3 = -0x13; local_1c = ((unsigned long)&rodata_f3376) /*=0xf3376*/; local_20 = 2;
    bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1040, &local_20);
  } else {
    uVar2 = atomic_and_3(iVar1 + 0xd4, 0xfffffffd);
    iVar3 = atomic_or(uVar2, 1);
    if (iVar3 << 0x1f < 0) {
      iVar3 = -0x78;
    } else {
      iVar3 = bt_settings_subsys_init_check();
      if (iVar3 == 0) {
        *(volatile int*)((unsigned long)&ready_cb) /*=0x2000ac6c*/ = param_1;
        z_impl_k_sem_init(iVar1 + 0x128, 1);
        z_impl_k_queue_init((void *)(iVar1 + 0x14c));
        local_38 = 0; uStack_34 = 0; local_40 = iVar3;
        z_impl_k_thread_create(((unsigned long)&rx_thread_data) /*=0x20005e30*/, ((unsigned long)&rx_thread_stack) /*=0x2002bb80*/, 0x400, ADDR_hci_tx_thread_THUMB /*=0x545f1*/, 0, 0, 0, 0xfffffff7);
        posix_stub_enosys(((unsigned long)&rx_thread_data) /*=0x20005e30*/, ((unsigned long)&rodata_f338f) /*=0xf338f*/);
        k_work_queue_init(((unsigned long)&bt_workqueue) /*=0x20005f08*/);
        k_work_queue_start(((unsigned long)&bt_workqueue) /*=0x20005f08*/, ((unsigned long)&bt_workqueue_stack) /*=0x2002bf80*/, 0x898, 0xfffffff8, 0);
        posix_stub_enosys(((unsigned long)&bt_workqueue) /*=0x20005f08*/, ((unsigned long)&rodata_f3395) /*=0xf3395*/);
        iVar3 = (*(cf*)(*(int*)(iVar1 + 0x168) + 0xc))();
        if (iVar3 == 0) {
          if (param_1 == 0) iVar3 = hci_vs_init();
          else k_work_submit(iVar1 + 0xc4);
        } else {
          local_3c = ((unsigned long)&rodata_f339b) /*=0xf339b*/; local_40 = 3; local_38 = iVar3;
          bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, &local_40);
        }
      }
    }
  }
  return iVar3;
}
