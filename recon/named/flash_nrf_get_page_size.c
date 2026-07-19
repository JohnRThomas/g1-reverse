/* readable reconstruction; identity: FUN_000851ee @ 0x000851ee
 * public-name: flash_nrf_get_page_size
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_nrf_get_page_size                  <= FUN_000851ee @ 0x000851ee
 */
/* Reconstructed FUN_000851ee @ 0x851ee  (parity: 300/300 trials, PROVEN) */

unsigned int flash_nrf_get_page_size(void)
{
    return 0x1000;
}
