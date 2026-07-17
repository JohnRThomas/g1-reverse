/* readable reconstruction; identity: FUN_000234e8 @ 0x000234e8
 * public-name: file_subsystem_queue_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   file_subsystem_queue_init                <= FUN_000234e8 @ 0x000234e8
 *   z_impl_k_msgq_alloc_init                 <= FUN_00086448 @ 0x00086448
 * address symbols (name @ address):
 *   rodata_9e7fd                             @ 0x0009e7fd
 *   rodata_9e810                             @ 0x0009e810
 *   g_file_msg_pipe                          @ 0x200079a0
 */
/* Reconstructed FUN_000234e8 @ 0x234e8 */
#include <stdint.h>

extern uint64_t z_impl_k_msgq_alloc_init(uint32_t, uint32_t, uint32_t, uint32_t);
extern void log_message(uint32_t, uint32_t, uint32_t, uint32_t);

int file_subsystem_queue_init(uint32_t inherited_r0, uint32_t inherited_r1,
                 uint32_t inherited_r2, uint32_t inherited_r3)
{
    uint64_t status = z_impl_k_msgq_alloc_init(0x200079a0u, 0xc9u, 0x1eu,
                                   inherited_r3);
    uint32_t format = (int32_t)status == 0 ? 0x0009e810u : 0x0009e7fdu;
    log_message(format, (uint32_t)(status >> 32), 0x1eu, inherited_r3);
    (void)inherited_r0;
    (void)inherited_r1;
    (void)inherited_r2;
    return (int32_t)status;
}
