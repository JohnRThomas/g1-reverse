/* readable reconstruction; identity: FUN_0102fcec @ 0x0102fcec
 * public-name: FUN_0102fcec
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 * address symbols (name @ address):
 *   rodata_103c024                           @ 0x0103c024
 *   rodata_103dde1                           @ 0x0103dde1
 *   rodata_103ddfa                           @ 0x0103ddfa
 *   rodata_103de16                           @ 0x0103de16
 *   g_210047f8                               @ 0x210047f8
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
    struct device_api_view *device = *(struct device_api_view **)0x210047f8u;
    *(volatile uint32_t *)0x210047fcu = context;
    if (device == 0) {
        struct log_arg3 record = {2, (const void *)0x0103dde1u, 0};
        z_impl_z_log_msg_static_create((const void *)0x0103c024u, 0x1040, &record, 0);
        return -19;
    }
    int status = device->init();
    if (status == 0) {
        struct log_arg3 record = {2, (const void *)0x0103de16u, 0};
        z_impl_z_log_msg_static_create((const void *)0x0103c024u, 0x10c0, &record, 0);
    } else {
        struct log_arg3 record = {3, (const void *)0x0103ddfau, status};
        z_impl_z_log_msg_static_create((const void *)0x0103c024u, 0x1840, &record, 0);
    }
    return status;
}
