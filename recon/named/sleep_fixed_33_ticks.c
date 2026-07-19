/* readable reconstruction; identity: FUN_0007c87a @ 0x0007c87a
 * public-name: sleep_fixed_33_ticks
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 */
/* Reconstructed FUN_0007c87a @ 0x7c87a  (parity: 300/300 trials, PROVEN) */

extern void k_sleep(unsigned int, unsigned int);
void sleep_fixed_33_ticks(void)
{
    k_sleep(0x21, 0);
}
