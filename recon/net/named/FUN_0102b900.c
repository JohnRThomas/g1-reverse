/* readable reconstruction; identity: FUN_0102b900 @ 0x0102b900
 * public-name: FUN_0102b900
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d23b                           @ 0x0103d23b
 *   g_zephyr_log_level                       @ 0x21000580
 */
/* net-core FUN_0102b900 @ 0x102b900 */
#include <stdint.h>

extern int FUN_01036198(void *queue, const uint8_t *value,
                        unsigned flags, unsigned timeout);
extern void FUN_01039722(const void *message, int status);
/* Zephyr wiring (one out-of-line platform boundary shared with FUN_01031928):
 *   void g1_arch_runtime_exception(unsigned reason) { ARCH_EXCEPT(reason); }
 * ARCH_EXCEPT clears BASEPRI, places reason in r0, and raises runtime-exception
 * SVC 2. The function is noreturn; no ordinary C fallback is valid here. */
extern __attribute__((noreturn)) void g1_arch_runtime_exception(unsigned reason);

int FUN_0102b900(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    int status = FUN_01036198((void *)0x210008e0u, &byte, 0, 0);

    if (status == 0)
        return 0;

    if (*(volatile int *)0x21000580u > 0)
        FUN_01039722((const void *)0x0103d23bu, status);

    g1_arch_runtime_exception(3);
}
