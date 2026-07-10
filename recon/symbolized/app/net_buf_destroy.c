#include "g1_app_symbols.h"
/* named: net_buf_destroy */
/* Reconstructed net_buf_destroy @ 0x56080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef int (*fnptr_t)(int,int,int);
extern void printk(int a,int b,int c,int d);
extern void assert_post_action(int a,int b);
extern void net_pkt_skip(int a);
void net_buf_destroy(int param_1, int param_2)
{
  fnptr_t UNRECOVERED_JUMPTABLE;
  int uVar1;
  if (param_2 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "tx" /*=0xf3aa8*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x46);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x46);
  }
  UNRECOVERED_JUMPTABLE = (fnptr_t)*(volatile uint32_t *)(param_2 + 4);
  uVar1 = *(volatile int *)(param_2 + 8);
  *(volatile int *)(param_2 + 0xc) = 0;
  *(volatile int *)(param_2 + 4) = 0;
  *(volatile int *)(param_2 + 8) = 0;
  net_pkt_skip(((uintptr_t)&g_bt_conn_tx_pending_cnt) /*=0x20003a60*/);
  (*UNRECOVERED_JUMPTABLE)(param_1, uVar1, 0xffffff92);
}

