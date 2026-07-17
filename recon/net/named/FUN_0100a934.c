/* readable reconstruction; identity: FUN_0100a934 @ 0x0100a934
 * public-name: FUN_0100a934
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a934 @ 0x0100a934, exact Thumb extent 0x1c bytes. */
#include <stdint.h>

#define CONTROLLER_STATE ((volatile uint8_t *)0x21000bf8u)

uint32_t FUN_0100a934(void)
{
    if (CONTROLLER_STATE[0x32] == 1u) {
        return 0u;
    }
    CONTROLLER_STATE[0x32] = 1u;
    *(volatile uint16_t *)(CONTROLLER_STATE + 0x34) =
        *(volatile uint16_t *)(CONTROLLER_STATE + 0x36);
    return 1u;
}
