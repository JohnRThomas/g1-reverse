/* readable reconstruction; identity: FUN_0102a1ea @ 0x0102a1ea
 * public-name: sdc_byte_lock_try_acquire
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private byte-lock acquisition @ 0x0102a1ea.
 * Raw back-map: FUN_0102a1ea@0x0102a1ea; extent 0x1e. */
#include <stdint.h>
#include <cmsis_gcc.h>

int sdc_byte_lock_try_acquire(volatile uint8_t *lock)
{
    uint32_t key = __get_PRIMASK();
    uint8_t previous;
    __disable_irq();
    previous = *lock;
    *lock = 1;
    if (key == 0)
        __enable_irq();
    return previous == 1 ? -35 : 0;
}
