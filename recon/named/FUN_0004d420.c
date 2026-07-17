/* readable reconstruction; identity: FUN_0004d420 @ 0x0004d420
 * public-name: FUN_0004d420
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_8acb4                             @ 0x0008acb4
 */
/* Reconstructed FUN_0004d420 @ 0x4d420  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0004d420(int param_1)
{
    return *(volatile unsigned int*)(0x8acb4UL + (unsigned int)param_1 * 4);
}
