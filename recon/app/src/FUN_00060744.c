/* Reconstructed FUN_00060744 @ 0x60744.
 * BASEPRI-guarded HFCLK release caller; raw/address back-map is preserved.
 */
#include <stdint.h>

extern void FUN_00065324(int domain);

void FUN_00060744(void)
{
    uint32_t saved_basepri;
    __asm volatile("mrs %0, basepri" : "=r"(saved_basepri));
    __asm volatile("msr basepri_max, %0\n\tisb sy" :: "r"((uint32_t)0x20) : "memory");

    volatile uint32_t *state = (volatile uint32_t *)0x2000b148UL;
    uint32_t previous = *state;
    *state = previous & ~2u;
    if ((previous & 1u) == 0u) {
        FUN_00065324(1);
    }

    __asm volatile("msr basepri, %0\n\tisb sy" :: "r"(saved_basepri) : "memory");
}
