/* net-core FUN_0102abac @ 0x0102abac
 * Readable identity: g1_ipc_endpoint_send.
 * Raw back-map: FUN_0102acb4 stores runtime Thumb pointer 0x0102b3ad.
 */
#include <stdint.h>

#define g1_ipc_endpoint_send FUN_0102abac

#ifdef G1_COHESIVE_BUILD
#include <zephyr/ipc/ipc_service.h>
#define FUN_0102d618(endpoint, data, size) \
    ipc_service_send((struct ipc_ept *)(endpoint), (data), (size))
#else
extern int FUN_0102d618(void *queue, const void *data, uint32_t size);
#endif
extern void FUN_01039722(const char *format, ...);

int g1_ipc_endpoint_send(const void *data, uint32_t size)
{
    if (*(volatile uint32_t *)0x21004600u == 1) {
        int status = FUN_0102d618((void *)0x210045f8u, data, size);
        if (status < 0 && *(volatile int32_t *)0x21000580u > 0)
            FUN_01039722((const char *)0x0103ce65u, status);
        return status;
    }

    if (*(volatile int32_t *)0x21000580u > 0)
        FUN_01039722((const char *)0x0103ce7au);
    return -1;
}
