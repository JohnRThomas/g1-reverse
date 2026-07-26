/* readable reconstruction; identity: FUN_000471cc @ 0x000471cc
 * public-name: clean_fb_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_d7347                             @ 0x000d7347   [INLINED -- G6 literal batch]
 *   rodata_d7374                             @ 0x000d7374   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed clean_fb_data @ 0x471cc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../headers/g1_log.h"
extern void memset_bytes(int, void*, int);

int clean_fb_data(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    uintptr_t row;
    uintptr_t end;
    if (0x27f < param_5) param_5 = 0x280;
    if (199 < param_6) param_6 = 200;
    if ((param_5 < param_3) || (param_6 < param_4)) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0xd7347U, 0xd7374U);
            } else {
                debug_print(0xd7347U, 0xd7374U);
            }
        }
        iVar1 = -1;
    } else {
        param_3 = param_3/2;
        /* Firmware address arithmetic is 32-bit modular arithmetic.  Spell it
           through uintptr_t/uint32_t so negative row indices and wraparound do
           not invoke signed-overflow or out-of-object pointer arithmetic UB. */
        row = (uintptr_t)(uint32_t)param_1 +
              ((uint32_t)param_4 - 1u) * sizeof(uint32_t);
        end = (uintptr_t)(uint32_t)param_1 +
              (uint32_t)param_6 * sizeof(uint32_t);
        while (end != row) {
            row += sizeof(uint32_t);
            uintptr_t clear = (uintptr_t)*(uint32_t*)row +
                              (uint32_t)param_3;
            uint32_t count = 1u - (uint32_t)param_3 +
                             (uint32_t)(param_5/2);
            memset_bytes((int)(uint32_t)clear, param_2, (int)count);
        }
        iVar1 = (int)((uint32_t)(param_5/2) - (uint32_t)param_3 + 1u);
    }
    return iVar1;
}
