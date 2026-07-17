/* readable reconstruction; identity: FUN_000852fe @ 0x000852fe
 * public-name: nrf_gpio_pin_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_set                         <= FUN_000852fe @ 0x000852fe
 */
/* Reconstructed FUN_000852fe @ 0x852fe  (parity: 300/300 trials, PROVEN) */

extern int FUN_00066d1c(unsigned int *p);
void nrf_gpio_pin_set(unsigned int param_1, int param_2, int param_3) {
    unsigned int local_c = param_1;
    int iVar1 = FUN_00066d1c(&local_c);
    *(int*)(iVar1 + 0xc) = (int)(1u << (local_c & 0xff));
}
