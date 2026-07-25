/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21004fa0[];
#define G1N_21004fa1 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x1))
#define G1N_21004fa2 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x2))
#define G1N_21004fa3 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x3))
#else
#define G1N_21004fa1 0x21004fa1ul
#define G1N_21004fa2 0x21004fa2ul
#define G1N_21004fa3 0x21004fa3ul
#endif
/* CPUNET ESB transport start @ 0x0102b718.
 * Raw back-map: FUN_0102b718@0x0102b718; true extent 0x30.
 *
 * This is product glue, not an MPSL timeslot routine.  It is reached from
 * the clock-transition callback at FUN_0102b758 and starts the recovered ESB
 * radio/configuration path at FUN_0102b31c.
 * CFG_VERIFY_CALL_ARITIES=1,1
 */
#include <stdint.h>

#define g1_esb_radio_configure    FUN_0102b31c
#define g1_esb_start_announcement FUN_0102b3f0
#define g1_esb_transport_start    FUN_0102b718

extern int g1_esb_radio_configure(int receive_mode);
extern void g1_esb_start_announcement(int announce_start);

int g1_esb_transport_start(void)
{
    volatile uint32_t *const gpio0 = (volatile uint32_t *)0x418c0500u;
    volatile uint8_t *const requested_mode = (volatile uint8_t *)G1N_21004fa2;
    volatile uint8_t *const clock_ready = (volatile uint8_t *)G1N_21004fa1;
    volatile uint8_t *const transport_ready = (volatile uint8_t *)G1N_21004fa3;
    int err;

    gpio0[2] = 0x20000000u;
    err = g1_esb_radio_configure(*requested_mode);
    *clock_ready = 1;
    *transport_ready = 1;
    g1_esb_start_announcement(1);
    gpio0[3] = 0x20000000u;
    return err;
}
