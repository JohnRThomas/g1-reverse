/* readable reconstruction; identity: FUN_0102da84 @ 0x0102da84
 * public-name: ipc_rpmsg_register_ept
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ipc_rpmsg_register_ept                   <= FUN_0102da84 @ 0x0102da84
 */
/* Reconstructed ipc_rpmsg_register_ept @ 0x0102da84.
 * Raw/address back-map: FUN_0102da84 / 0x0102da84.
 */
#include <stdint.h>

extern int FUN_010354bc(void *endpoint, void *device, const char *name,
                        uint32_t source, uint32_t destination,
                        void *receive_callback, void *unbind_callback);

int ipc_rpmsg_register_ept(uint8_t *instance, uint32_t role, uint8_t *endpoint)
{
    if ((instance == 0) || (endpoint == 0)) {
        return -22;
    }
    if (role == 1u) {
        return FUN_010354bc(endpoint, instance + 0xe0, (char *)endpoint + 0x40,
                            UINT32_MAX, UINT32_MAX,
                            *(void **)(instance + 0x1ac),
                            (void *)0x0103cfa9u);
    }
    return 0;
}
