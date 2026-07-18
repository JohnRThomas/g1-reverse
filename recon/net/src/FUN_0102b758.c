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
    volatile uint32_t *const radio_state = (volatile uint32_t *)0x210005b4u;
    volatile uint32_t *const gpio0 = (volatile uint32_t *)0x418c0500u;
    volatile uint8_t *const clock_ready = (volatile uint8_t *)0x21004fa1u;

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
