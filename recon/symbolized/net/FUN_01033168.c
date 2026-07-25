#include "g1_net_symbols.h"
extern volatile unsigned int g1_esb_window_request[4];
/* readable reconstruction; identity: FUN_01033168 @ 0x01033168
 * public-name: FUN_01033168
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01033168 @ 0x1033168  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB retransmission-window request @ 0x01033168 (Ghidra-gap, extent 0x2a).
 * Programs the request length at 0x21000670+0xc from TIMER2 CC[1] (0x544)
 * + 0x81 us and submits it through the 0x21000530 vtable slot 8; on failure it
 * sets TIMER2 SHORTS 0x40004 directly.
 */
extern void FUN_01033c74(void);
extern unsigned int FUN_010218c0(unsigned int, unsigned int);

void FUN_01033168(void)
{
    volatile unsigned int *volatile *inst =
        (volatile unsigned int *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;
    volatile unsigned int *w = (volatile unsigned int *)((unsigned long)g1_esb_window_request) /*=0x21000670*/;

    w[3] = (*inst)[0x544u / 4u] + 0x81u;
    FUN_01033c74();
    if (FUN_010218c0(((unsigned long)g1_esb_window_request) /*=0x21000670*/, G1N_2100065c) == 0u) {
        (*inst)[0x200u / 4u] = 0x40004u;
    }
}
