/* readable reconstruction; identity: FUN_00048b44 @ 0x00048b44
 * public-name: FUN_00048b44
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_dashboard_display_level                @ 0x20002544
 */
/* Reconstructed FUN_00048b44 @ 0x48b44  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00048b44(int param_1)
{
    if (param_1 >= 0x7d) {
        param_1 = 0x7d;
    }
    if (param_1 < 0x21) {
        param_1 = 0x21;
    }
    *(volatile unsigned int*)0x20002544UL = param_1;
    return 0;
}
