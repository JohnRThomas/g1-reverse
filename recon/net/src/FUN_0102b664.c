/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21004fa0[];
#define G1N_21004fa1 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x1))
#define G1N_21004fa2 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x2))
#else
#define G1N_21004fa1 0x21004fa1ul
#define G1N_21004fa2 0x21004fa2ul
#endif
/* CPUNET ESB radio stop and peripheral release @ 0x0102b664.
 * Raw back-map: FUN_0102b664@0x0102b664; true extent 0x96.
 * CFG_VERIFY_CALL_ARITIES=1,0,0
 */
#include <stdint.h>

extern void FUN_0102eb48(unsigned int irq);
extern void FUN_01033354(void);
extern void FUN_01033968(void);

#define g1_esb_radio_owner_reset  FUN_01033354
#define g1_esb_radio_suspend      FUN_01033968
#define g1_esb_radio_release      FUN_0102b664

int g1_esb_radio_release(void)
{
    volatile uint8_t *const clock_ready = (volatile uint8_t *)G1N_21004fa1;
    volatile uint8_t *const receive_mode = (volatile uint8_t *)G1N_21004fa2;
    volatile uint32_t *const gpio0 = (volatile uint32_t *)0x418c0500u;
    volatile uint32_t *const nvic = (volatile uint32_t *)0xe000e100u;
    volatile uint32_t *const radio = (volatile uint32_t *)0x41008000u;
    volatile uint32_t *const timer3 = (volatile uint32_t *)0x41019000u;
    volatile uint32_t *const power = (volatile uint32_t *)0x41004000u;
    uint32_t saved_basepri;

    *clock_ready = 0;
    gpio0[2] = 0x20000000u;

    if (*receive_mode == 0) {
        __asm__ volatile ("mrs %0, basepri" : "=r" (saved_basepri));
        __asm__ volatile ("msr basepri_max, %0\n\tisb"
                          : : "r" (0x40u) : "memory");
        FUN_0102eb48(8);
        nvic[0x80 / 4] = 0x100u;
        __asm__ volatile ("dsb\n\tisb" : : : "memory");

        radio[0x200 / 4] = 0;
        radio[0x110 / 4] = 0;
        radio[0x10 / 4] = 1;
        while (radio[0x110 / 4] == 0) {
        }
        timer3[1] = 1;
        radio[0x308 / 4] = UINT32_MAX;
        g1_esb_radio_owner_reset();
        nvic[0x180 / 4] = 0x100u;

        __asm__ volatile ("msr basepri, %0\n\tisb"
                          : : "r" (saved_basepri) : "memory");
    } else if (*receive_mode == 1) {
        g1_esb_radio_suspend();
    }

    gpio0[3] = 0x20000000u;
    power[0x500 / 4] = 1;
    return 0;
}
