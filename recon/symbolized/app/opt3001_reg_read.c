#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002e594 @ 0x0002e594
 * public-name: opt3001_reg_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   opt3001_reg_read                         <= FUN_0002e594 @ 0x0002e594
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_a3af8                             @ 0x000a3af8   [INLINED -- G6 literal batch]
 *   rodata_a3b17                             @ 0x000a3b17   [INLINED -- G6 literal batch]
 *   rodata_a3d26                             @ 0x000a3d26   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_opt3007_bus_dev                        @ 0x200023fc
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002e594 @ 0x2e594 */
#include <stdint.h>

extern _Bool z_device_is_ready(const struct device *);
extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);

struct io_part { void *data; uint32_t length; uint8_t type; };
typedef int (*transfer_fn)(uint32_t, struct io_part *, uint32_t, uint32_t);

int opt3001_reg_read(uint8_t request, uint16_t *result)
{
    volatile uint32_t *device_slot = (volatile uint32_t *)((unsigned long)&g_opt3007_bus_dev) /*=0x200023fc*/;
    uint32_t device = *device_slot;
    uint16_t response = 0;
    if (z_device_is_ready(device) == 0) {
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): Bus device is not ready\n") /*=0xa3af8*/, ((unsigned long)"opt3001_reg_read") /*=0xa3d26*/);
            else
                debug_print(((unsigned long)"%s(): Bus device is not ready\n") /*=0xa3af8*/, ((unsigned long)"opt3001_reg_read") /*=0xa3d26*/);
        }
        return -19;
    }
    struct { struct io_part tx, rx; } parts = {
        { &request, 1, 0 }, { &response, 2, 7 }
    };
    transfer_fn transfer = *(transfer_fn *)(uintptr_t)(*(uint32_t *)(device + 8) + 8);
    int status = transfer(device, &parts.tx, 2, 0x45);
    if (status < 0) {
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): ERR: opt3007 i2c read addr=0x%x,\n") /*=0xa3b17*/, ((unsigned long)"opt3001_reg_read") /*=0xa3d26*/, 0x45);
            else
                debug_print(((unsigned long)"%s(): ERR: opt3007 i2c read addr=0x%x,\n") /*=0xa3b17*/, ((unsigned long)"opt3001_reg_read") /*=0xa3d26*/, 0x45);
        }
        return -2;
    }
    *result = (uint16_t)((response << 8) | (response >> 8));
    return 0;
}
