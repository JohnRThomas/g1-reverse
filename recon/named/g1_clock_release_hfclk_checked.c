/* readable reconstruction; identity: FUN_00060744 @ 0x00060744
 * public-name: g1_clock_release_hfclk_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_clock_release_hfclk_checked           <= FUN_00060744 @ 0x00060744
 *   nrfx_clock_stop                          <= FUN_00065324 @ 0x00065324
 */
/* Reconstructed FUN_00060744 @ 0x60744.
 * BASEPRI-guarded HFCLK release caller; raw/address back-map is preserved.
 */
#include <stdint.h>

extern void nrfx_clock_stop(int domain);

void g1_clock_release_hfclk_checked(void)
{
    uint32_t saved_basepri;
    __asm volatile("mrs %0, basepri" : "=r"(saved_basepri));
    __asm volatile("msr basepri_max, %0\n\tisb sy" :: "r"((uint32_t)0x20) : "memory");

    volatile uint32_t *state = (volatile uint32_t *)0x2000b148UL;
    uint32_t previous = *state;
    *state = previous & ~2u;
    if ((previous & 1u) == 0u) {
        nrfx_clock_stop(1);
    }

    __asm volatile("msr basepri, %0\n\tisb sy" :: "r"(saved_basepri) : "memory");
}
