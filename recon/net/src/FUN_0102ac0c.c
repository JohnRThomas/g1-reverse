/* net-core FUN_0102ac0c @ 0x102ac0c */
#include <stdint.h>

extern void FUN_01039722(const void *message);
extern int FUN_0102d558(const void *path);
#ifdef G1_COHESIVE_BUILD
#include <zephyr/device.h>
#include <zephyr/ipc/ipc_service.h>
#define FUN_0102d5b4(instance, endpoint, config) \
    ipc_service_register_endpoint((const struct device *)(instance), \
                                  (struct ipc_ept *)(endpoint), \
                                  (const struct ipc_ept_cfg *)(config))
#else
extern int FUN_0102d5b4(const void *path, void *destination, void *metadata);
#endif
extern void FUN_0103689c(void *object, int ignored, int first, int second);

#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_ipc0_endpoint_config;
#define G1_IPC0_ENDPOINT_CONFIG ((void *)&g1_ipc0_endpoint_config) /*=0x21000584*/
/* 0x0103bfac is the shipped image's `struct device` "ipc0" (word0 -> 0x0103cf12
 * = "ipc0", api 0x0103c8a8).  Unrelocated in the cohesive build it lands in
 * plain text, so instance->api reads 0 and ipc_service_open_instance() /
 * ipc_service_register_endpoint() both return -EIO ("<err> ipc_service:
 * Invalid backend configuration" on the net UART), which is what kept the
 * app-core rpmsg endpoint bind from ever completing.  Parity builds (no
 * G1_COHESIVE_BUILD) keep the original literal. */
#include <zephyr/devicetree.h>
#define G1_IPC0_DEVICE ((const void *)DEVICE_DT_GET(DT_NODELABEL(ipc0)))
#else
#define G1_IPC0_ENDPOINT_CONFIG ((void *)UINT32_C(0x21000584))
#define G1_IPC0_DEVICE ((const void *)UINT32_C(0x0103bfac))
#endif

int FUN_0102ac0c(void)
{
    volatile int *const log_level = (volatile int *)UINT32_C(0x21000580);

    if (*log_level > 2)
        FUN_01039722((const void *)UINT32_C(0x0103ce92));

    int status = FUN_0102d558(G1_IPC0_DEVICE);
    if (status < 0 && status != -0x78) {
        if (*log_level > 0)
            FUN_01039722((const void *)UINT32_C(0x0103ceac));
        return -1;
    }

    if (*log_level > 2)
        FUN_01039722((const void *)UINT32_C(0x0103cec3));

    status = FUN_0102d5b4(G1_IPC0_DEVICE,
                          (void *)UINT32_C(0x210045f8),
                          G1_IPC0_ENDPOINT_CONFIG);
    if (status < 0) {
        if (*log_level > 0)
            FUN_01039722((const void *)UINT32_C(0x0103ced0));
        return -1;
    }

    FUN_0103689c((void *)UINT32_C(0x21000914), 0, -1, -1);
    *(volatile uint32_t *)UINT32_C(0x21004600) = 1;
    if (*log_level > 1)
        FUN_01039722((const void *)UINT32_C(0x0103cef6));
    return 0;
}
