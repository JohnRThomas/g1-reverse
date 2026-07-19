#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000262ac @ 0x000262ac
 * public-name: spi_master_trans_data_tx_rx
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   nrfx_spim_xfer                           <= FUN_00067304 @ 0x00067304
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_9fb42                             @ 0x0009fb42
 *   rodata_9fb59                             @ 0x0009fb59
 *   rodata_9fc5d                             @ 0x0009fc5d
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed spi_master_trans_data_tx_rx @ 0x262ac  (parity: 300/300 trials, PROVEN) */

extern int nrfx_spim_xfer(void*, void*, int);
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, ...);

unsigned int spi_master_trans_data_tx_rx(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned int param_5)
{
    int iVar1;
    struct {
        unsigned int tx_buffer;
        unsigned int tx_length;
        unsigned int rx_buffer;
        unsigned int rx_length;
    } transfer = { param_2, param_3, param_4, param_5 };
    if (*(volatile int*)(param_1 + 0x14) == 0) {
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_9fb42) /*=0x9fb42*/, ((unsigned long)&rodata_9fc5d) /*=0x9fc5d*/);
            } else {
                debug_print(((unsigned long)&rodata_9fb42) /*=0x9fb42*/, ((unsigned long)&rodata_9fc5d) /*=0x9fc5d*/);
            }
        }
    } else {
        iVar1 = nrfx_spim_xfer((void*)(param_1+0xc), &transfer, 0);
        if ((unsigned int)iVar1 == 0x0bad0000) {
            return 0;
        }
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_9fb59) /*=0x9fb59*/, ((unsigned long)&rodata_9fc5d) /*=0x9fc5d*/, *(volatile unsigned char*)(param_1+0x18), iVar1, 0x0bad0000);
            } else {
                debug_print(((unsigned long)&rodata_9fb59) /*=0x9fb59*/, ((unsigned long)&rodata_9fc5d) /*=0x9fc5d*/, *(volatile unsigned char*)(param_1+0x18), iVar1, 0x0bad0000);
            }
        }
    }
    return 0xffffffff;
}
