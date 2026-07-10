/* Reconstructed FUN_0002953c @ 0x2953c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int z_impl_k_sem_init(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_0002953c(void)
{
    int iVar1 = z_impl_k_sem_init(0x20007b1cU /* device_info.gap_10E0+64 */, 0, 5, 0, 0);
    if (iVar1 == 0) {
        *(volatile uint8_t *)0x20018d8aUL = 1;
    }
}

