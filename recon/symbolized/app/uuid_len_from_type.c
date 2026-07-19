#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e98c @ 0x0004e98c
 * public-name: uuid_len_from_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_invalid_index_log               <= FUN_0004e8c0 @ 0x0004e8c0
 *   uuid_len_from_type                       <= FUN_0004e98c @ 0x0004e98c
 * address symbols (name @ address):
 *   rodata_f1590                             @ 0x000f1590
 */
/* Reconstructed FUN_0004e98c @ 0x4e98c, exact code extent 16 bytes. */
#include <stdint.h>

extern uint32_t settings_invalid_index_log(uint32_t index, uint32_t a1,
                            uint32_t a2, uint32_t a3);

uint32_t uuid_len_from_type(uint32_t index, uint32_t a1, uint32_t a2, uint32_t a3,
                      uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
    if (index > 2u) {
        (void)a4; (void)a5; (void)a6; (void)a7;
        return settings_invalid_index_log(index, a1, a2, a3);
    }
    return *(const uint8_t *)(((unsigned long)&rodata_f1590) /*=0xf1590*/ + index);
}
