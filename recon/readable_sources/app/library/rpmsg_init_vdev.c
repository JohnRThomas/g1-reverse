#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00071560 @ 0x00071560
 * public-name: rpmsg_init_vdev
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed rpmsg_init_vdev @ 0x00071560 from pinned OpenAMP rpmsg_virtio.c.
 * Raw backmap: FUN_00071560@0x00071560. */

#include <stdint.h>

struct rpmsg_virtio_config {
    uint32_t host_to_remote_buffer_size;
    uint32_t remote_to_host_buffer_size;
    uint32_t split_shared_pool;
};

extern int rpmsg_init_vdev_with_config(
    void *rpmsg_device, void *virtio_device, void *name_service_callback,
    void *shared_memory_io, void *shared_pool,
    const struct rpmsg_virtio_config *config) __asm__("FUN_00071358");

int rpmsg_init_vdev(void *rpmsg_device, void *virtio_device,
                    void *name_service_callback, void *shared_memory_io,
                    void *shared_pool)
{
    const struct rpmsg_virtio_config default_config = {512u, 512u, 0u};
    return rpmsg_init_vdev_with_config(
        rpmsg_device, virtio_device, name_service_callback, shared_memory_io,
        shared_pool, &default_config);
}
