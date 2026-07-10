#include "g1_app_symbols.h"
/* named: bt_hci_core_recv_event */
/* Reconstructed bt_hci_core_recv_event @ 0x536b8  (parity: 300/300 trials, PROVEN) */
extern void FUN_00053658(int,int,int,int);
extern void FUN_00056394(int,int,int);
extern void ble_conn_unref(int);
extern int  ble_conn_lookup_masked(int,int);
extern int  net_buf_id(int);
extern int  net_buf_slist_get(int);
extern void net_buf_unref(int);
extern int  net_buf_simple_pull_5f594(int,int);
extern void printk(int,int,int,int);
extern int  bt_hci_evt_get_flags(int);
extern void FUN_00080ea2(int,int,void*);
extern int  k_work_submit_to_queue(int,int);
#define VI(a) (*(volatile int*)(a))
#define VH(a) (*(volatile unsigned short*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define ASSERT() __asm__ volatile("svc #2")

void bt_hci_core_recv_event(void){
  int iVar4,iVar6,iVar8; unsigned int uVar10; int uVar9;
  unsigned char *puVar7; unsigned short *puVar5;
  unsigned short uVar1,uVar2;
  int st[8];
  iVar4 = net_buf_slist_get(((uintptr_t)&g_bt_hci_recv_fifo) /*=0x20002144*/);
  if (iVar4 == 0) return;
  uVar10 = VB(iVar4+0x18);
  if (uVar10 == 1) {
    if (VH(iVar4+0x10) < 2) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"buf->len >= sizeof(*hdr)" /*=0xf2eb8*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/hci_core.c" /*=0xf2e84*/,0xa5d); ASSERT(); }
    puVar7 = (unsigned char*)net_buf_simple_pull_5f594(iVar4+0xc,2);
    iVar8 = bt_hci_evt_get_flags(*puVar7);
    if ((int)(iVar8<<0x1e) >= 0) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"bt_hci_evt_get_flags(hdr->evt) & (1UL << (1))" /*=0xf2f17*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/hci_core.c" /*=0xf2e84*/,0xa61); ASSERT(); }
    FUN_00053658(*puVar7, iVar4, ((uintptr_t)&tbl_8b148) /*=0x8b190*/, 6);
  } else {
    uVar9 = "Unknown buf type %u" /*=0xf2f45*/;
    if (uVar10 == 3) {
      if (VH(iVar4+0x10) < 4) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"buf->len >= sizeof(*hdr)" /*=0xf2eb8*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/hci_core.c" /*=0xf2e84*/,0x200); ASSERT(); }
      puVar5 = (unsigned short*)net_buf_simple_pull_5f594(iVar4+0xc,4);
      uVar1 = puVar5[1];
      uVar2 = puVar5[0];
      iVar6 = net_buf_id(iVar4);
      VH(((uintptr_t)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/ + iVar6*2) = (unsigned short)(((unsigned int)uVar2 << 0x14) >> 0x14);
      if ((unsigned int)uVar1 != (unsigned int)VH(iVar4+0x10)) {
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/,0x2040,st);
        goto LAB_0005373c;
      }
      iVar6 = net_buf_id(iVar4);
      iVar6 = ble_conn_lookup_masked(VH(((uintptr_t)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/ + iVar6*2), 0xf);
      if (iVar6 != 0) {
        FUN_00056394(iVar6, iVar4, uVar2 >> 0xc);
        ble_conn_unref(iVar6);
        goto LAB_00053792;
      }
      iVar6 = net_buf_id(iVar4);
      uVar10 = VH(((uintptr_t)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/ + iVar6*2);
      uVar9 = "Unable to find conn for handle %u" /*=0xf2ef5*/;
    }
    FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/,0x1840,st);
  }
LAB_0005373c:
  net_buf_unref(iVar4);
LAB_00053792:
  if (VI(((uintptr_t)&g_bt_hci_recv_fifo) /*=0x20002144*/) != 0) {
    if ((int)k_work_submit_to_queue(((uintptr_t)&bt_workqueue) /*=0x20005f08*/, ((uintptr_t)&g_bt_hci_rx_work) /*=0x20002980*/) < 0) {
      FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/,0x1840,st);
    }
  }
}

