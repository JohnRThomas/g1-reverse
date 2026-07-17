/* readable reconstruction; identity: FUN_0102ac0c @ 0x0102ac0c
 * public-name: FUN_0102ac0c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103bfac                           @ 0x0103bfac
 *   rodata_103ce92                           @ 0x0103ce92
 *   rodata_103ceac                           @ 0x0103ceac
 *   rodata_103cec3                           @ 0x0103cec3
 *   rodata_103ced0                           @ 0x0103ced0
 *   rodata_103cef6                           @ 0x0103cef6
 *   g_zephyr_log_level                       @ 0x21000580
 *   g_net_radio_dev_ready_flag               @ 0x21004600
 */
/* net-core FUN_0102ac0c @ 0x102ac0c */
#include <stdint.h>

extern void FUN_01039722(const void *message);
extern int FUN_0102d558(const void *path);
extern int FUN_0102d5b4(const void *path, void *destination, void *metadata);
extern void FUN_0103689c(void *object, int ignored, int first, int second);

int FUN_0102ac0c(void)
{
    volatile int *const log_level = (volatile int *)UINT32_C(0x21000580);

    if (*log_level > 2)
        FUN_01039722((const void *)UINT32_C(0x0103ce92));

    int status = FUN_0102d558((const void *)UINT32_C(0x0103bfac));
    if (status < 0 && status != -0x78) {
        if (*log_level > 0)
            FUN_01039722((const void *)UINT32_C(0x0103ceac));
        return -1;
    }

    if (*log_level > 2)
        FUN_01039722((const void *)UINT32_C(0x0103cec3));

    status = FUN_0102d5b4((const void *)UINT32_C(0x0103bfac),
                          (void *)UINT32_C(0x210045f8),
                          (void *)UINT32_C(0x21000584));
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
