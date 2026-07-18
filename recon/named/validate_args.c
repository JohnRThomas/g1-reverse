/* readable reconstruction; identity: FUN_0007e1c6 @ 0x0007e1c6
 * public-name: validate_args
 * durable-map: recon/catalogs/function_names_app.json
 */
/* validate_args @ 0x0007e1c6; raw FUN_0007e1c6 */
#include <stdint.h>

extern int sys_notify_validate(void *); /* FUN_0007e238 */

int validate_args(const void *manager, uint8_t *client)
{
    if (!manager || !client) {
        return -22;
    }

    int result = sys_notify_validate(client + 4);
    if (result == 0 && *(uint32_t *)(client + 8) > 3u) {
        return -22;
    }
    return result;
}
