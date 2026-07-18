/* readable reconstruction; identity: FUN_0008520c @ 0x0008520c
 * public-name: nrfx_qspi_chip_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_qspi_erase                          <= FUN_00066bc4 @ 0x00066bc4
 *   nrfx_qspi_chip_erase                     <= FUN_0008520c @ 0x0008520c
 */
/* Reconstructed FUN_0008520c @ 0x8520c  (parity: 300/300 trials, PROVEN) */

#define g1_recon_nrfx_qspi_erase nrfx_qspi_erase
extern void g1_recon_nrfx_qspi_erase(unsigned int, unsigned int);
#define g1_recon_nrfx_qspi_chip_erase nrfx_qspi_chip_erase
void g1_recon_nrfx_qspi_chip_erase(void)
{
    g1_recon_nrfx_qspi_erase(2, 0);
}
