/* readable reconstruction; identity: FUN_00080e38 @ 0x00080e38
 * public-name: update_sec_level
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed update_sec_level @ 0x80e38  (CFG-directed candidate) */
/* Owner: NCS 2.5.1 Bluetooth host hci_core.c; raw backmap FUN_00080e38@0x00080e38. */
#include <stdint.h>
#include <stdbool.h>
int update_sec_level(int connection_arg) {
    uint8_t *connection = (uint8_t *)connection_arg;
    const uint8_t *keys = *(const uint8_t * const *)(connection + 0xc0u);
    uint8_t level;
    if (keys != 0 && (keys[0x0du] & 1u) != 0u) {
        if ((keys[0x0du] & 0x10u) != 0u && keys[0x0cu] == 16u) {
            level = 4u;
        } else {
            level = 3u;
        }
    } else {
        level = 2u;
    }
    connection[9] = level;
    return connection[10] <= level;
}
