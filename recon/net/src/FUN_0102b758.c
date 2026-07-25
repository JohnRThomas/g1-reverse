/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21004fa0[];
#define G1N_21004fa1 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x1))
#else
#define G1N_21004fa1 0x21004fa1ul
#endif
/* CPUNET ESB clock-transition callback @ 0x0102b758.
 * Raw back-map: FUN_0102b758@0x0102b758; true extent 0x30.
 *
 * The callback address is stored as runtime Thumb pointer 0x0102bf59 in the
 * literal at analysis address 0x0102b660 and registered by FUN_0102b5bc.
 * CFG_VERIFY_CALL_ARITIES=0,0
 */
#include <stdint.h>

#define g1_esb_transport_start  FUN_0102b718
#define g1_esb_radio_release    FUN_0102b664
#define g1_esb_clock_transition FUN_0102b758

extern int g1_esb_transport_start(void);
extern int g1_esb_radio_release(void);

void g1_esb_clock_transition(unsigned int transition)
{
#ifdef G1_COHESIVE_BUILD
/* P4 iteration 21 - the ESB radio operating-state word (original VA
 * 0x210005b4) is emitted by recon/application/net/src/timeslot_owner.c.  Left
 * as a raw literal it landed inside the emitted g1_timeslot_request_earliest
 * and overwrote that request's `request_type` byte.  Parity keeps the
 * original literal. */
extern volatile unsigned int g_net_radio_op_state;
#define G1_NET_RADIO_OP_STATE (&g_net_radio_op_state)
#else
#define G1_NET_RADIO_OP_STATE ((volatile unsigned int *)0x210005b4u)
#endif

    volatile uint32_t *const radio_state = G1_NET_RADIO_OP_STATE;
    volatile uint32_t *const gpio0 = (volatile uint32_t *)0x418c0500u;
    volatile uint8_t *const clock_ready = (volatile uint8_t *)G1N_21004fa1;

    if (transition == 0) {
        if (*radio_state != 3) {
            gpio0[2] = 0x80000000u;
            (void)g1_esb_transport_start();
        }
    } else if (transition == 1 && *clock_ready != 0) {
        gpio0[3] = 0x80000000u;
        (void)g1_esb_radio_release();
    }
}
