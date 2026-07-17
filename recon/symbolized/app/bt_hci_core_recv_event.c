#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000536b8 @ 0x000536b8
 * public-name: bt_hci_core_recv_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_core_recv_event                   <= FUN_000536b8 @ 0x000536b8
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_lookup_masked                   <= FUN_00056908 @ 0x00056908
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 *   net_buf_slist_get                        <= FUN_0005f148 @ 0x0005f148
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_hci_evt_get_flags                     <= FUN_00080e14 @ 0x00080e14
 *   k_work_submit_to_queue                   <= FUN_000865fc @ 0x000865fc
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_8b190                             @ 0x0008b190
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2e84                             @ 0x000f2e84
 *   rodata_f2eb8                             @ 0x000f2eb8
 *   rodata_f2ef5                             @ 0x000f2ef5
 *   rodata_f2f17                             @ 0x000f2f17
 *   rodata_f2f45                             @ 0x000f2f45
 *   g_bt_hci_recv_fifo                       @ 0x20002144
 *   g_bt_hci_rx_work                         @ 0x20002980
 *   bt_workqueue                             @ 0x20005f08
 *   g_bt_hci_acl_frag_conn_handle            @ 0x2000ff08
 */
/* Reconstructed FUN_000536b8 @ 0x536b8  (parity: 300/300 trials, PROVEN) */
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
#define ASSERT() __builtin_trap()

void bt_hci_core_recv_event(void){
  int iVar4,iVar6,iVar8; unsigned int uVar10; int uVar9;
  unsigned char *puVar7; unsigned short *puVar5;
  unsigned short uVar1,uVar2;
  int st[8];
  iVar4 = net_buf_slist_get(((unsigned long)&g_bt_hci_recv_fifo) /*=0x20002144*/);
  if (iVar4 == 0) return;
  uVar10 = VB(iVar4+0x18);
  if (uVar10 == 1) {
    if (VH(iVar4+0x10) < 2) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f2eb8) /*=0xf2eb8*/,((unsigned long)&rodata_f2e84) /*=0xf2e84*/,0xa5d); ASSERT(); }
    puVar7 = (unsigned char*)net_buf_simple_pull_5f594(iVar4+0xc,2);
    iVar8 = bt_hci_evt_get_flags(*puVar7);
    if ((int)(iVar8<<0x1e) >= 0) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f2f17) /*=0xf2f17*/,((unsigned long)&rodata_f2e84) /*=0xf2e84*/,0xa61); ASSERT(); }
    FUN_00053658(*puVar7, iVar4, ((unsigned long)&rodata_8b190) /*=0x8b190*/, 6);
  } else {
    uVar9 = ((unsigned long)&rodata_f2f45) /*=0xf2f45*/;
    if (uVar10 == 3) {
      if (VH(iVar4+0x10) < 4) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f2eb8) /*=0xf2eb8*/,((unsigned long)&rodata_f2e84) /*=0xf2e84*/,0x200); ASSERT(); }
      puVar5 = (unsigned short*)net_buf_simple_pull_5f594(iVar4+0xc,4);
      uVar1 = puVar5[1];
      uVar2 = puVar5[0];
      iVar6 = net_buf_id(iVar4);
      VH(((unsigned long)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/ + iVar6*2) = (unsigned short)(((unsigned int)uVar2 << 0x14) >> 0x14);
      if ((unsigned int)uVar1 != (unsigned int)VH(iVar4+0x10)) {
        FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/,0x2040,st);
        goto LAB_0005373c;
      }
      iVar6 = net_buf_id(iVar4);
      iVar6 = ble_conn_lookup_masked(VH(((unsigned long)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/ + iVar6*2), 0xf);
      if (iVar6 != 0) {
        FUN_00056394(iVar6, iVar4, uVar2 >> 0xc);
        ble_conn_unref(iVar6);
        goto LAB_00053792;
      }
      iVar6 = net_buf_id(iVar4);
      uVar10 = VH(((unsigned long)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/ + iVar6*2);
      uVar9 = ((unsigned long)&rodata_f2ef5) /*=0xf2ef5*/;
    }
    FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/,0x1840,st);
  }
LAB_0005373c:
  net_buf_unref(iVar4);
LAB_00053792:
  if (VI(((unsigned long)&g_bt_hci_recv_fifo) /*=0x20002144*/) != 0) {
    if ((int)k_work_submit_to_queue(((unsigned long)&bt_workqueue) /*=0x20005f08*/, ((unsigned long)&g_bt_hci_rx_work) /*=0x20002980*/) < 0) {
      FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/,0x1840,st);
    }
  }
}
