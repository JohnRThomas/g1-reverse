#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004df34 @ 0x0004df34
 * public-name: log_backend_uart_dropped
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_output_dropped_process               <= FUN_0004de68 @ 0x0004de68
 *   log_backend_uart_dropped                 <= FUN_0004df34 @ 0x0004df34
 * address symbols (name @ address):
 *   rodata_8ad08                             @ 0x0008ad08
 */
/* Reconstructed FUN_0004df34 @ 0x4df34  owned extent: 0x8 bytes */

extern void log_output_dropped_process(void *stream);

void log_backend_uart_dropped(void)
{
    log_output_dropped_process((void *)((unsigned long)&rodata_8ad08) /*=0x8ad08*/);
}
