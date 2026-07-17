/* readable reconstruction; identity: FUN_000579b4 @ 0x000579b4
 * public-name: FUN_000579b4
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_2000ad2c                               @ 0x2000ad2c
 */
/* Reconstructed FUN_000579b4 @ 0x579b4  (parity: 300/300 trials, PROVEN) */

void FUN_000579b4(unsigned int param_1)
{
    int *piVar1 = *(volatile int**)0x2000ad2cUL;
    while (piVar1 != (int*)0 && *(volatile unsigned short*)((char*)piVar1 - 8) != param_1) {
        piVar1 = *(volatile int**)piVar1;
    }
}
