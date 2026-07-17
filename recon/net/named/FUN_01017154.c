/* readable reconstruction; identity: FUN_01017154 @ 0x01017154
 * public-name: FUN_01017154
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_get_active_link_index           <= FUN_0100d760 @ 0x0100d760
 *   sdc_llcp_decode_control_pdu              <= FUN_0101a070 @ 0x0101a070
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 */
/* Reconstructed net-core packet handler @ 0x01017154. */
#include <stdint.h>

extern uint32_t FUN_0100aa3c(uint8_t, uint32_t, uint8_t, void *);
extern uint32_t sdc_llcp_get_active_link_index(void);
extern uint32_t FUN_0101709c(void *, uint32_t);
extern void sdc_llcp_decode_control_pdu(const void *, void *);
extern void FUN_010295d6(void *, uint32_t);

uint32_t FUN_01017154(const uint8_t *packet)
{
    uint8_t parsed[40];
    volatile uint8_t *state = (volatile uint8_t *)0x21000f90;

    *(volatile uint8_t *)0x2100001c = (uint8_t)sdc_llcp_get_active_link_index();
    if ((packet[0] & 0x0f) != 7)
        return 1;

    sdc_llcp_decode_control_pdu(packet, parsed);
    *(uint32_t *)(parsed + 8) = 0;
    if (parsed[0] != 0 || (parsed[1] & 1) == 0)
        return 1;

    if (FUN_0100aa3c(parsed[0x11], *(uint32_t *)(parsed + 4),
                     state[0x90], (void *)(state + 0x89)) == 0)
        return 1;

    FUN_010295d6((void *)(state + 0x84), 1);
    if (FUN_0101709c(parsed, 0xff) == 0)
        return 1;
    return 3;
}
