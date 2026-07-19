/* readable reconstruction; identity: FUN_00063b7c @ 0x00063b7c
 * public-name: fatal_log_and_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   nrf_cc3xx_platform_abort                 <= FUN_00050af8 @ 0x00050af8
 *   fatal_log_and_reset                      <= FUN_00063b7c @ 0x00063b7c
 * address symbols (name @ address):
 *   rodata_881a8                             @ 0x000881a8
 *   rodata_f66f9                             @ 0x000f66f9
 */
/* Full reconstruction FUN_00063b7c @ 0x00063b7c (44-byte exact extent). */
#include <stdint.h>

extern void g1_recon_z_impl_log_panic(void);
extern void z_log_msg_runtime_create(uintptr_t, uint32_t, const void *, uint32_t, ...);
extern void nrf_cc3xx_platform_abort(uint32_t) __attribute__((noreturn));

struct log_record2 { uint32_t count, format; };

void fatal_log_and_reset(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    struct log_record2 record = { 2, 0x000f66f9u };
    g1_recon_z_impl_log_panic();
    z_log_msg_runtime_create(0x000881a8u, 0x1040u, &record, 0, a, b, c, d);
    nrf_cc3xx_platform_abort(0);
}
