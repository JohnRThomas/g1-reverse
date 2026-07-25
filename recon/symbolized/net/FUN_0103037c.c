#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103037c @ 0x0103037c
 * public-name: FUN_0103037c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103037c @ 0x103037c  (parity 300 trials PROVEN) */

/* P4 iteration 21 - `z_nrf_clock_control_get_onoff()`.
 *
 * The shipped body is `return 0x21004814 + (uint8_t)sys * 0x20`, which is
 * Zephyr's
 *     get_onoff_manager(CLOCK_DEVICE, type) = &((struct nrf_clock_control_data *)
 *                                               dev->data)->mgr[type]
 * with `struct onoff_manager` = 0x20 bytes and `mgr[]` first in the driver
 * data, so 0x21004814 is the SHIPPED image's `struct nrf_clock_control_data`.
 * Confirmed structurally in this link: the stock clock_control_nrf.c driver
 * data is `data` @ 0x21008414 (size 0x58 = 2 * 0x20 mgr + 2 * 0xc subsys) and
 * `z_nrf_clock_control_lf_on()` was measured requesting mgr @ 0x21008434 =
 * data + 0x20, i.e. exactly the same 0x20 stride.
 *
 * Left as the raw literal the recovered body returned a pointer INTO
 * `sdc_mempool`, so the ESB bring-up requested an uninitialised onoff manager.
 * In the cohesive link call the stock accessor so the LINKER supplies the real
 * manager (and roots the archive member); parity keeps the original literal. */
#ifdef G1_COHESIVE_BUILD
extern void *z_nrf_clock_control_get_onoff(void *subsystem);

int FUN_0103037c(unsigned int param_1)
{
  unsigned char b = (unsigned char)param_1;
  return (int)(unsigned long)z_nrf_clock_control_get_onoff((void *)(unsigned long)b);
}
#else
int FUN_0103037c(unsigned int param_1)
{
  unsigned int DAT_01030388 = 0x21004814;
  unsigned char b = (unsigned char)param_1;
  return DAT_01030388 + (unsigned int)b * 0x20;
}
#endif
