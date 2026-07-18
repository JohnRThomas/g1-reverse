/* Reconstructed FUN_0007f7c4 @ 0x0007f7c4.
 * Exact branch veneer to bt_ancs_app_attr_request @ 0x0007f7d2.
 */
#include <stdint.h>
extern int FUN_0007f7d2(void *, const uint8_t *, uint32_t, void *);
int FUN_0007f7c4(void *client, const uint8_t *app_id,
                 uint32_t length, void *callback)
{
    return FUN_0007f7d2(client, app_id, length, callback);
}
