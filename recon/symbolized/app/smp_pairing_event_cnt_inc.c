#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057394 @ 0x00057394
 * public-name: smp_pairing_event_cnt_inc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_pairing_event_cnt_inc                <= FUN_00057394 @ 0x00057394
 * address symbols (name @ address):
 *   g_smp_pairing_event_cnt                  @ 0x2001d531
 */
/* Reconstructed FUN_00057394 @ 0x57394  (parity: 300/300 trials, PROVEN) */

int smp_pairing_event_cnt_inc(void) {
    unsigned char v = *(volatile unsigned char*)((unsigned long)&g_smp_pairing_event_cnt) /*=0x2001d531*/;
    v = v + 1;
    if (v < 1) v = 1;
    *(volatile unsigned char*)((unsigned long)&g_smp_pairing_event_cnt) /*=0x2001d531*/ = v;
}
