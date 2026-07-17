/* readable reconstruction; identity: FUN_00057394 @ 0x00057394
 * public-name: FUN_00057394
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_smp_pairing_event_cnt                  @ 0x2001d531
 */
/* Reconstructed FUN_00057394 @ 0x57394  (parity: 300/300 trials, PROVEN) */

void FUN_00057394(void)
{
    unsigned char v = *(volatile unsigned char*)0x2001d531UL;
    v = v + 1;
    if (v < 1) v = 1;
    *(volatile unsigned char*)0x2001d531UL = v;
}
