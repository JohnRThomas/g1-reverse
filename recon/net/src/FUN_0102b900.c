/* net-core FUN_0102b900 @ 0x102b900 */
#include <stdint.h>

extern int FUN_01036198(void *queue, const uint8_t *value,
                        unsigned flags, unsigned timeout);
extern void FUN_01039722(const void *message, int status);

int FUN_0102b900(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    int status = FUN_01036198((void *)0x210008e0u, &byte, 0, 0);

    if (status == 0)
        return 0;

    if (*(volatile int *)0x21000580u > 0)
        FUN_01039722((const void *)0x0103d23bu, status);

    /* The original requests supervisor service 2 with operation 3 and does not
     * resume in this function.  Keep that non-returning contract explicit; the
     * integrated Zephyr wrapper replaces the trap with the real syscall. */
    __builtin_trap();
}
