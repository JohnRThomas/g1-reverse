/* readable reconstruction; identity: FUN_0006125c @ 0x0006125c
 * public-name: flash_nrf_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   flash_nrf_erase                          <= FUN_0006125c @ 0x0006125c
 *   nrfx_nvmc_page_erase                     <= FUN_00065f1c @ 0x00065f1c
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   is_regular_addr_valid                    <= FUN_000839dc @ 0x000839dc
 *   flash_nrf_get_page_size                  <= FUN_000851ee @ 0x000851ee
 * address symbols (name @ address):
 *   rodata_881b0                             @ 0x000881b0
 *   rodata_f5d81                             @ 0x000f5d81
 *   rodata_f5d9e                             @ 0x000f5d9e
 *   g_2000b154                               @ 0x2000b154
 */
/* Reconstructed FUN_0006125c @ 0x6125c */
#include <stdint.h>

extern unsigned int flash_nrf_get_page_size(void);
extern unsigned long long is_regular_addr_valid(unsigned int address,
                                       unsigned int length);
extern void z_log_msg_runtime_create(unsigned int source, unsigned int level,
                         const unsigned int *arguments, unsigned int flags);
extern void z_impl_k_sem_take(unsigned int lock, unsigned int context,
                         unsigned int timeout_low,
                         unsigned int timeout_high);
extern void k_sem_give(unsigned int lock);
extern unsigned int nrfx_nvmc_page_erase(unsigned int address);

unsigned int flash_nrf_erase(unsigned int unused, unsigned int address,
                          unsigned int length)
{
    unsigned int page_size = flash_nrf_get_page_size();
    unsigned long long range = is_regular_addr_valid(address, length);

    if ((unsigned int)range == 0) {
        unsigned int arguments[4] = {4, 0x000f5d81, address, length};
        z_log_msg_runtime_create(0x000881b0, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if ((address % page_size) != 0 || (length % page_size) != 0) {
        unsigned int arguments[4] = {4, 0x000f5d9e, address, length};
        z_log_msg_runtime_create(0x000881b0, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if (page_size <= length) {
        z_impl_k_sem_take(0x2000b154, (unsigned int)(range >> 32),
                     (unsigned int)-1, (unsigned int)-1);
        page_size = flash_nrf_get_page_size();
        do {
            nrfx_nvmc_page_erase(address);
            length -= page_size;
            address += page_size;
        } while (length != 0);
        k_sem_give(0x2000b154);
    }
    return 0;
}
