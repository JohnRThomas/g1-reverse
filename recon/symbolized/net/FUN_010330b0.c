#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010330b0 @ 0x010330b0
 * public-name: FUN_010330b0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010330b0 @ 0x10330b0  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE 3 - "frame keyed, arm the ACK window" @ 0x010330b0 (Ghidra
 * gap, extent 0x92).  FUN_01032c28 and FUN_010331c8 both load the continuation
 * slot 0x210049a0 with the RUNTIME Thumb pointer 0x010338b1
 * (= analysis 0x010330b0 | 1).  It re-programs the DPPI wiring, arms TIMER2
 * CC[0] (ACK wait = g_net_radio_op_status + 13 us) and CC[1]
 * (retransmit_delay - 0x81/0x28 us depending on config.use_fast_ramp_up),
 * points PACKETPTR at the ACK staging buffer, and publishes state 3 with
 * continuation 0x010339c9 (= FUN_010331c8).
 */
extern void FUN_01033bf0(unsigned int, unsigned int);
extern void FUN_01033ca4(void);
extern void FUN_01033084(void);
extern void FUN_0103a9dc(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_01033d54(void);
extern void FUN_01033d20(void);

void FUN_010330b0(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned char *cfg = (volatile unsigned char *)((unsigned long)&g_esb_state) /*=0x21004a94*/;
    volatile unsigned int *timer;
    void (*handler)(unsigned int);
    unsigned int sub, proto;

    FUN_01033bf0(0u, 1u);
    FUN_01033ca4();
    FUN_01033084();
    radio[0x200u / 4u] = 0x113u;
    FUN_0103a9dc(((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/, 0u,
                 *(volatile unsigned int *)((unsigned long)&g_net_radio_op_status) /*=0x210049a4*/ + 0xdu, 0u);
    sub = (cfg[0x13] == 0u) ? 0x81u : 0x28u;
    FUN_0103a9dc(((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/, 1u,
                 (unsigned int)(*(volatile unsigned short *)((unsigned long)&g_esb_state + 0xcu) /*=0x21004aa0*/) - sub, 0u);
    timer = *(volatile unsigned int *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;
    timer[0x200u / 4u] = 0x20002u;
    timer[0x140u / 4u] = 0u;
    (void)timer[0x140u / 4u];
    timer[0x144u / 4u] = 0u;
    (void)timer[0x144u / 4u];
    FUN_01033d54();
    FUN_01033d20();
    radio[0x10cu / 4u] = 0u;
    proto = cfg[0];
    (void)radio[0x10cu / 4u];
    if (proto == 0u) {
        handler = *(void (*volatile *)(unsigned int))((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/;
        handler(proto);
    }
    radio[0x504u / 4u] = G1N_2100625e;
    #ifdef G1_COHESIVE_BUILD
    /* P4 iteration 25 - CODE POINTER.  0x010339c9 is a RUNTIME Thumb pointer;
       runtime->analysis is -0x800, so it is (0x010331c8 | 1) = FUN_010331c8, an ESB
       radio state-machine entry recovered from the Ghidra gap this
       iteration.  Left as the shipped literal the relocated build stores
       an address inside unrelated code and FUN_010327d8's `bx r3`
       dispatches nowhere (measured, iteration 24 probeN:
       0x210049a0 = 0x010338B1, pending bitmap 0x210049b0 stuck at 0,
       IRQ 0x1d never raised, the announcement never re-armed). */
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = ADDR_FUN_010331c8_THUMB;
#else
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = 0x010339c9u;
#endif
    *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 3u;
}
