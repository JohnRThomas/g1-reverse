/* readable reconstruction; identity: FUN_000582b8 @ 0x000582b8
 * public-name: att_op_get_type
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed att_op_get_type @ 0x000582b8 (FUN_000582b8; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: subsys/bluetooth/host/att.c. */
#include <stdint.h>
uint32_t att_op_get_type(uint8_t op)
{
    switch (op) {
    case 0x02: case 0x04: case 0x06: case 0x08:
    case 0x0a: case 0x0c: case 0x0e: case 0x20:
    case 0x10: case 0x12: case 0x16: case 0x18:
        return 1;
    case 0x1e:
        return 4;
    case 0x52: case 0xd2:
        return 0;
    case 0x01: case 0x03: case 0x05: case 0x07:
    case 0x09: case 0x0b: case 0x0d: case 0x0f:
    case 0x21: case 0x11: case 0x13: case 0x17: case 0x19:
        return 2;
    case 0x1b: case 0x23:
        return 3;
    case 0x1d:
        return 5;
    }
    if (op & 0x40) return 0;
    return 6;
}
