#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003016c @ 0x0003016c
 * public-name: attr_store_retry_delay
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 * address symbols (name @ address):
 *   g_pt_nfc_link_cfg                        @ 0x20007bc0
 */
/* Reconstructed FUN_0003016c @ 0x3016c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(void);
void attr_store_retry_delay(void)
{
    unsigned int base = *(volatile unsigned int *)((unsigned long)&g_pt_nfc_link_cfg) /*=0x20007bc0*/;
    fn_t f = *(volatile fn_t *)(base + 0xc);
    f();
}
