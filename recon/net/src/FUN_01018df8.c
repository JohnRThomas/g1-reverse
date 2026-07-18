/* net-core FUN_01018df8 @ 0x01018df8, true executable extent 0x32. */
#include <stdint.h>

extern void sdc_llcp_stop_rx_timeout(void);    /* FUN_010208b0 */
extern void sdc_llcp_release_rx_context(void); /* FUN_0101fca8 */
extern void sdc_event_publish(uint32_t, uint32_t, uint32_t, uint32_t); /* FUN_0101b4f4 */
#define LLCP_STATE ((volatile uint8_t *)(uintptr_t)0x21000f90u)
#define RADIO_PENDING ((volatile uint8_t *)(uintptr_t)0x2100104au)

void FUN_01018df8(uint32_t call_context)
{
    if (LLCP_STATE[0x7c] != 0u) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        LLCP_STATE[0x7c] = 0u;
    }
    *(volatile uint16_t *)(LLCP_STATE + 0xba) = 0u;
    LLCP_STATE[0x70] = 1u;
    RADIO_PENDING[2] = 0u;
    sdc_event_publish(call_context, 1u, 0x2100104au, 0u);
}
