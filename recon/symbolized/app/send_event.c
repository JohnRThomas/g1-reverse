#include "g1_app_symbols.h"
/* named: send_event */
/* Reconstructed send_event @ 0x276ec  (parity: 300/300 trials, PROVEN) */

extern int enqueue_bt_data(void*, int);
extern int ancs_get_conn_ctx(void);
extern void k_msleep_ticks32768_a(int);
extern void thunk_FUN_00072880(int);

void send_event(int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar3;
  unsigned char cVar1;
  unsigned char *pcVar2 = (unsigned char*)((uintptr_t)&g_send_event_pending_id) /*=0x2000302e*/;
  unsigned char buf[8];

  iVar3 = ancs_get_conn_ctx();
  if ((unsigned int)(param_1 - 0xf0) > 2 || *pcVar2 == 0xff) {
    cVar1 = *(unsigned char*)(iVar3 + 0x248);
    *pcVar2 = (unsigned char)param_1;
    if (cVar1 != 0) {
      goto build;
    }
    if (*(int*)(iVar3 + 0x220) != 0) {
      goto build;
    }
    if (*(unsigned char*)(iVar3 + 0x248) != 0) {
      return;
    }
    thunk_FUN_00072880(iVar3 + 0x218);
    k_msleep_ticks32768_a(1);
    return;
  build:
    buf[0] = 0xf5;
    buf[1] = (unsigned char)param_1;
    buf[2] = 0xcb;
    enqueue_bt_data(buf, 3);
    *pcVar2 = 0xff;
    return;
  }
}

