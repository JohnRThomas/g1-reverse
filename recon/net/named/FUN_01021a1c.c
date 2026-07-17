/* readable reconstruction; identity: FUN_01021a1c @ 0x01021a1c
 * public-name: FUN_01021a1c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_deferred_cb_fn                     @ 0x210016e0
 */
/* net-core FUN_01021a1c @ 0x1021a1c  (parity 300 trials PROVEN) */

extern void FUN_01022a84(void);
#define DAT_01021a34 ((unsigned int *)0x210016e0)

void FUN_01021a1c(void)
{
    unsigned int *puVar1 = DAT_01021a34;
    unsigned int fp = *puVar1;
    if (fp != 0) {
        ((void (*)(void))fp)();
        *puVar1 = 0;
    }
    FUN_01022a84();
    return;
}
