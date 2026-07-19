/* readable reconstruction; identity: FUN_0007c3da @ 0x0007c3da
 * public-name: invoke_optional_op_offset12
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   invoke_optional_op_offset12              <= FUN_0007c3da @ 0x0007c3da
 */
/* Full reconstruction FUN_0007c3da @ 0x7c3da (exact extent 16 bytes). */
#include <stdint.h>
uint32_t invoke_optional_op_offset12(uint8_t *object)
{
    if (object == 0) return 7;
    uint32_t (*callback)(uint8_t *) = *(uint32_t (**)(uint8_t *))(object + 12);
    return callback != 0 ? callback(object) : 15;
}
