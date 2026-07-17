/* Reconstructed shm_size @ 0x7ebee  (CFG-directed candidate) */
/* Owner: Zephyr 3.4.99 ipc_rpmsg_static_vrings.h; raw backmap FUN_0007ebee@0x0007ebee. */
#include <stdint.h>
uint32_t shm_size(uint32_t descriptor_count, uint32_t buffer_size)
{
    uint32_t ring_bytes = (descriptor_count * 18u + 9u) & ~3u;
    uint32_t payload_bytes = (descriptor_count * buffer_size + 3u) & ~3u;
    return 2u * (ring_bytes + descriptor_count * 8u + 8u + payload_bytes);
}
