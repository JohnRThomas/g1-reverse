/* readable reconstruction; identity: FUN_0008520c @ 0x0008520c
 * public-name: FUN_0008520c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_qspi_read                           <= FUN_00066bc4 @ 0x00066bc4
 */
/* Reconstructed FUN_0008520c @ 0x8520c  (parity: 300/300 trials, PROVEN) */

extern void nrfx_qspi_read(unsigned int, unsigned int);
void FUN_0008520c(void)
{
    nrfx_qspi_read(2, 0);
}
