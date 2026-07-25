#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01033084 @ 0x01033084
 * public-name: FUN_01033084
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01033084 @ 0x1033084  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB timeslot/notification release @ 0x01033084 (Ghidra-gap, extent 0x20).
 * Takes the 0x21000530 vtable slot 0x10 hook, then slot 0xc with the
 * (0x0103cafc, 0x2100065c) descriptor pair, and clears TIMER2 SHORTS bits
 * 0x40004.  Called by FUN_010330b0.
 */
extern void controller_mode1_state_validate(void); /* FUN_010218d8 */
extern void FUN_010218cc(unsigned int, unsigned int);

void FUN_01033084(void)
{
    volatile unsigned int *reg;
    controller_mode1_state_validate();
    FUN_010218cc(0x0103cafcu, 0x2100065cu);
    reg = *(volatile unsigned int *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;
    reg[0x200u / 4u] = reg[0x200u / 4u] & ~0x40004u;
}
