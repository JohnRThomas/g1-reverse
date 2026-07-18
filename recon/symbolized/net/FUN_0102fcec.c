#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102fcec @ 0x0102fcec
 * public-name: FUN_0102fcec
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 * address symbols (name @ address):
 *   rodata_103c024                           @ 0x0103c024
 *   g_net_047fc                              @ 0x210047fc
 */
/* net-core entropy-device initialization adapter @ 0x0102fcec.
 * Raw/address back-map: FUN_0102fcec / 0x0102fcec.
 */
#include <stdint.h>

extern void z_impl_z_log_msg_static_create(const void *, uint32_t, void *, const void *);

typedef int (*init_fn_t)(void);
struct device_api_view { uint32_t reserved[3]; init_fn_t init; };
struct log_arg3 { uint32_t count; const void *message; int value; };

int FUN_0102fcec(uint32_t context)
{
    struct device_api_view *device = *(struct device_api_view **)((unsigned long)&g_210047f8) /*=0x210047f8*/;
    *(volatile uint32_t *)((unsigned long)&g_net_047fc) /*=0x210047fc*/ = context;
    if (device == 0) {
        struct log_arg3 record = {2, (const void *)((unsigned long)&rodata_103dde1) /*=0x103dde1*/, 0};
        z_impl_z_log_msg_static_create((const void *)((unsigned long)&rodata_103c024) /*=0x103c024*/, 0x1040, &record, 0);
        return -19;
    }
    int status = device->init();
    if (status == 0) {
        struct log_arg3 record = {2, (const void *)((unsigned long)&rodata_103de16) /*=0x103de16*/, 0};
        z_impl_z_log_msg_static_create((const void *)((unsigned long)&rodata_103c024) /*=0x103c024*/, 0x10c0, &record, 0);
    } else {
        struct log_arg3 record = {3, (const void *)((unsigned long)&rodata_103ddfa) /*=0x103ddfa*/, status};
        z_impl_z_log_msg_static_create((const void *)((unsigned long)&rodata_103c024) /*=0x103c024*/, 0x1840, &record, 0);
    }
    return status;
}
