#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102b900 @ 0x0102b900
 * public-name: FUN_0102b900
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_msgq_put                        <= FUN_01036198 @ 0x01036198
 *   printk                                   <= FUN_01039722 @ 0x01039722
 * address symbols (name @ address):
 *   rodata_103d23b                           @ 0x0103d23b
 *   g_zephyr_log_level                       @ 0x21000580
 */
/* net-core FUN_0102b900 @ 0x102b900 */
#include <stdint.h>

extern int z_impl_k_msgq_put(void *queue, const uint8_t *value,
                        unsigned flags, unsigned timeout);
extern void printk(const void *message, int status);

#define G1_ARCH_RUNTIME_EXCEPTION(reason) do { \
    __asm__ volatile("eors.n r0, r0\n\t" \
                     "msr basepri, r0\n\t" \
                     "mov r0, %0\n\t" \
                     "svc 2" \
                     : : "I"(reason) : "r0", "memory"); \
} while (0)

int FUN_0102b900(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    int status = z_impl_k_msgq_put((void *)0x210008e0u, &byte, 0, 0);
    register unsigned int exception_r1 __asm__("r1");

    if (status == 0)
        return 0;

    if (*(volatile int *)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/ > 0)
        printk((const void *)((unsigned long)&rodata_103d23b) /*=0x103d23b*/, status);

    exception_r1 = (unsigned int)status;
    __asm__ volatile("" : : "r"(exception_r1));
    G1_ARCH_RUNTIME_EXCEPTION(3);
    return status;
}
