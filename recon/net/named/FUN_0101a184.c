/* readable reconstruction; identity: FUN_0101a184 @ 0x0101a184
 * public-name: FUN_0101a184
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101a184 @ 0x0101a184, exact Thumb extent 0x92 bytes. */
#include <stdint.h>

extern uint32_t FUN_010190c4(void);
#define controller_phy_mode_get FUN_010190c4

/* Select the controller timing budget for a PHY-mask and active PHY mode. */
uint32_t FUN_0101a184(uint32_t phy_mask)
{
    if (controller_phy_mode_get() == 1u) {
        if (phy_mask == 8u) {
            return 0x4290u;
        }
        if (phy_mask == 4u) {
            return 0x11beu;
        }
        return phy_mask == 2u ? 0x428u : 0x848u;
    }

    if (phy_mask == 8u) {
        return 0x190u + 0x1f9cu + 0x4100u;
    }
    if (phy_mask == 4u) {
        return 0x17eu + 0xb38u + 0x1040u;
    }
    if (phy_mask == 2u) {
        return 0x18u + 0x30cu + 0x410u;
    }
    return 0x28u + ((phy_mask & 0xcu) != 0u ? 0x52cu : 0x4dcu) +
           0x820u;
}
