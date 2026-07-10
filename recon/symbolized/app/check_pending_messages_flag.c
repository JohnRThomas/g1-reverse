#include "g1_app_symbols.h"
/* named: check_pending_messages_flag */
/* Reconstructed check_pending_messages_flag @ 0x2c1fc  (parity: 300/300 trials, PROVEN) */

extern void k_uptime_get_2(void);
extern int msg_content_recalc_unread(void);

void check_pending_messages_flag(void)
{
    k_uptime_get_2();
    int iVar1 = msg_content_recalc_unread();
    if (iVar1 != 0) {
        *(volatile unsigned char*)((uintptr_t)&g_pending_message_flag) /*=0x20018d9e*/ = 1;
    }
}

