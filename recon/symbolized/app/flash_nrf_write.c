#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00061310 @ 0x00061310
 * public-name: flash_nrf_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   flash_nrf_write                          <= FUN_00061310 @ 0x00061310
 *   nrfx_nvmc_word_write                     <= FUN_00065f80 @ 0x00065f80
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   is_regular_addr_valid                    <= FUN_000839dc @ 0x000839dc
 * address symbols (name @ address):
 *   rodata_881b0                             @ 0x000881b0
 *   rodata_f5d81                             @ 0x000f5d81
 *   rodata_f5dbd                             @ 0x000f5dbd
 *   g_2000b154                               @ 0x2000b154
 *   REG_50039400                             @ 0x50039400
 */
/* Reconstructed FUN_00061310 @ 0x61310 */
#include <stdint.h>

extern unsigned long long is_regular_addr_valid(unsigned int address,
                                       unsigned int length);
extern void z_log_msg_runtime_create(unsigned int source, unsigned int level,
                         const unsigned int *arguments, unsigned int flags);
extern void z_impl_k_sem_take(unsigned int lock, unsigned int context,
                         unsigned int timeout_low,
                         unsigned int timeout_high);
extern void k_sem_give(unsigned int lock);
extern void nrfx_nvmc_word_write(unsigned int address, unsigned int value);

unsigned int flash_nrf_write(unsigned int unused, unsigned int address,
                          const unsigned int *source, unsigned int length)
{
    unsigned long long range = is_regular_addr_valid(address, length);

    if ((unsigned int)range == 0) {
        unsigned int arguments[4] = {4, ((unsigned long)&rodata_f5d81) /*=0xf5d81*/, address, length};
        z_log_msg_runtime_create(((unsigned long)&rodata_881b0) /*=0x881b0*/, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if (((address | length) & 3) != 0) {
        unsigned int arguments[4] = {4, ((unsigned long)&rodata_f5dbd) /*=0xf5dbd*/, address, length};
        z_log_msg_runtime_create(((unsigned long)&rodata_881b0) /*=0x881b0*/, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if (length != 0) {
        unsigned int offset = 0;
        unsigned int rounded_length = length & ~3u;
        z_impl_k_sem_take(((unsigned long)&g_2000b154) /*=0x2000b154*/, (unsigned int)(range >> 32),
                     (unsigned int)-1, (unsigned int)-1);
        while (offset != rounded_length) {
            nrfx_nvmc_word_write(address + offset, source[offset / 4]);
            offset += 4;
        }
        while ((*(volatile unsigned int *)REG_50039400 /*=0x50039400*/ & 1) == 0) {}
        k_sem_give(((unsigned long)&g_2000b154) /*=0x2000b154*/);
    }
    return 0;
}
