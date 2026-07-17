#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018334 @ 0x00018334
 * public-name: format_bt_addr_str
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_9a1c8                             @ 0x0009a1c8
 *   rodata_9a1cf                             @ 0x0009a1cf
 *   rodata_9a1d6                             @ 0x0009a1d6
 *   rodata_9a1e0                             @ 0x0009a1e0
 *   rodata_9a1ea                             @ 0x0009a1ea
 *   rodata_f5071                             @ 0x000f5071
 */
/* Reconstructed format_bt_addr_str @ 0x18334 (raw FUN_00018334).
 * Reviewed executable extent: 0x5e bytes; literals begin at 0x18394. */
#include <stdint.h>

typedef struct {
    uint8_t type;
    uint8_t address[6];
} bt_addr_le_wire_t;

enum {
    BT_ADDR_LE_PUBLIC = 0,
    BT_ADDR_LE_RANDOM = 1,
    BT_ADDR_LE_PUBLIC_ID = 2,
    BT_ADDR_LE_RANDOM_ID = 3,
};

#define BT_ADDR_PUBLIC_NAME    ((const char *)((unsigned long)&rodata_9a1c8) /*=0x9a1c8*/) /* "public" */
#define BT_ADDR_RANDOM_NAME    ((const char *)((unsigned long)&rodata_9a1cf) /*=0x9a1cf*/) /* "random" */
#define BT_ADDR_PUBLIC_ID_NAME ((const char *)((unsigned long)&rodata_9a1d6) /*=0x9a1d6*/) /* "public-id" */
#define BT_ADDR_RANDOM_ID_NAME ((const char *)((unsigned long)&rodata_9a1e0) /*=0x9a1e0*/) /* "random-id" */
#define BT_ADDR_STRING_FORMAT  ((const char *)((unsigned long)&rodata_9a1ea) /*=0x9a1ea*/)
#define BT_ADDR_UNKNOWN_FORMAT ((const char *)((unsigned long)&rodata_f5071) /*=0xf5071*/)

extern int snprintk(char *destination, uint32_t capacity,
                    const char *format, ...);
extern char *copy_c_string(char *destination, const char *source)
    __asm__("FUN_00086fee");

void format_bt_addr_str(const bt_addr_le_wire_t *address, char output[30])
{
    const char *type_name;
    char type_description[12];

    switch (address->type) {
    case BT_ADDR_LE_PUBLIC:
        type_name = BT_ADDR_PUBLIC_NAME;
        break;
    case BT_ADDR_LE_RANDOM:
        type_name = BT_ADDR_RANDOM_NAME;
        break;
    case BT_ADDR_LE_PUBLIC_ID:
        type_name = BT_ADDR_PUBLIC_ID_NAME;
        break;
    case BT_ADDR_LE_RANDOM_ID:
        type_name = BT_ADDR_RANDOM_ID_NAME;
        break;
    default:
        snprintk(type_description, 10, BT_ADDR_UNKNOWN_FORMAT, address->type);
        goto format_address;
    }

    copy_c_string(type_description, type_name);

format_address:
    snprintk(output, 30, BT_ADDR_STRING_FORMAT,
             address->address[5], address->address[4], address->address[3],
             address->address[2], address->address[1], address->address[0],
             type_description);
}
