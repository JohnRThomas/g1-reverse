/* readable reconstruction; identity: FUN_000852e6 @ 0x000852e6
 * public-name: nrf_gpio_pin_outset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_port_base_get               <= FUN_00066d1c @ 0x00066d1c
 *   nrf_gpio_pin_outset                      <= FUN_000852e6 @ 0x000852e6
 */
/* Reconstructed FUN_000852e6 @ 0x852e6  (parity: 300/300 trials, PROVEN) */

extern int nrf_gpio_pin_port_base_get(unsigned int *p);
void nrf_gpio_pin_outset(unsigned int param_1, int param_2, int param_3) {
    unsigned int local_c = param_1;
    int iVar1 = nrf_gpio_pin_port_base_get(&local_c);
    *(int*)(iVar1 + 8) = (int)(1u << (local_c & 0xff));
}
