/* readable reconstruction; identity: FUN_0102da84 @ 0x0102da84
 * public-name: g1_ipc_rpmsg_register_ept
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   g1_ipc_rpmsg_register_ept                <= FUN_0102da84 @ 0x0102da84
 *   rpmsg_create_ept                         <= FUN_010354bc @ 0x010354bc
 */
/* Reconstructed G1 ipc_rpmsg_register_ept variant @ 0x0102da84.
 * Raw/address back-map: FUN_0102da84 / 0x0102da84.
 *
 * The instruction body matches Zephyr ipc_rpmsg_register_ept after masking
 * relocations, but the shipped image's unbind callback literal is
 * 0x0103a98f.  Keep this firmware variant separate from Zephyr's public
 * ipc_rpmsg_register_ept owner; the ownership receipt records the complete
 * ipc_rpmsg.c source-unit closure and this decisive relocation difference.
 */
#include <stdint.h>

extern int rpmsg_create_ept(void *endpoint, void *device, const char *name,
                        uint32_t source, uint32_t destination,
                        void *receive_callback, void *unbind_callback);

int g1_ipc_rpmsg_register_ept(uint8_t *instance, uint32_t role, uint8_t *endpoint)
{
    if ((instance == 0) || (endpoint == 0)) {
        return -22;
    }
    if (role == 1u) {
        return rpmsg_create_ept(endpoint, instance + 0xe0, (char *)endpoint + 0x40,
                            UINT32_MAX, UINT32_MAX,
                            *(void **)(instance + 0x1ac),
                            (void *)0x0103a98fu);
    }
    return 0;
}
