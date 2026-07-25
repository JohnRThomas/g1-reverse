#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032804 @ 0x01032804
 * public-name: FUN_01032804
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01032804 @ 0x1032804  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE 4 - "ACK transmitted, arm RX" @ 0x01032804 (Ghidra gap,
 * extent 0x36).  Entered through the continuation slot
 * g_net_radio_irq_continuation_ptr (0x210049a0), which FUN_01032e54 loads with
 * the RUNTIME Thumb pointer 0x01033005 (= analysis 0x01032804 | 1).  It sets
 * RADIO SHORTS 0x117, notifies the ESB event handler with the configured
 * payload length, points PACKETPTR at the RX staging buffer 0x2100625e, and
 * publishes state 4 with continuation 0x01033655 (= FUN_01032e54).
 */
extern void controller_mode1_state_validate(void); /* FUN_010218d8 */
extern void FUN_010218cc(unsigned int, unsigned int);

void FUN_01032804(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned char *cfg = (volatile unsigned char *)((unsigned long)&g_esb_state) /*=0x21004a94*/;
    void (*handler)(unsigned int);

    controller_mode1_state_validate();
    FUN_010218cc(0x0103cafcu, 0x2100065cu);
    radio[0x200u / 4u] = 0x117u;
    handler = *(void (*volatile *)(unsigned int))((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/;
    handler(cfg[0x11]);
    radio[0x504u / 4u] = 0x2100625eu;
    #ifdef G1_COHESIVE_BUILD
    /* P4 iteration 25 - CODE POINTER.  0x01033655 is a RUNTIME Thumb pointer;
       runtime->analysis is -0x800, so it is (0x01032e54 | 1) = FUN_01032e54, an ESB
       radio state-machine entry recovered from the Ghidra gap this
       iteration.  Left as the shipped literal the relocated build stores
       an address inside unrelated code and FUN_010327d8's `bx r3`
       dispatches nowhere (measured, iteration 24 probeN:
       0x210049a0 = 0x010338B1, pending bitmap 0x210049b0 stuck at 0,
       IRQ 0x1d never raised, the announcement never re-armed). */
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = ADDR_FUN_01032e54_THUMB;
#else
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = 0x01033655u;
#endif
    *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 4u;
}
