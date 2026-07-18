/* readable reconstruction; identity: FUN_00066478 @ 0x00066478
 * public-name: qspi_deactivate
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_qspi_skip_activate_flag                @ 0x2000b380
 *   REG_5002b010                             @ 0x5002b010
 *   REG_5002b100                             @ 0x5002b100
 *   REG_5002b308                             @ 0x5002b308
 *   REG_5002b500                             @ 0x5002b500
 */
/* qspi_deactivate @ 0x00066478; raw FUN_00066478.
 * NCS 2.5.1 nrfx_qspi.c private peripheral shutdown helper. */
#include <stdint.h>
void qspi_deactivate(void)
{
    *(volatile uint8_t *)0x2000b380u = 0u;    /* m_cb.activated */
    *(volatile uint32_t *)0x5002b308u = 1u;  /* NRF_QSPI->INTENCLR READY */
    *(volatile uint32_t *)0x5002b010u = 1u;  /* TASKS_DEACTIVATE */
    *(volatile uint32_t *)0x5002b500u = 0u;  /* ENABLE */
    *(volatile uint32_t *)0x5002b100u = 0u;  /* EVENTS_READY */
}
