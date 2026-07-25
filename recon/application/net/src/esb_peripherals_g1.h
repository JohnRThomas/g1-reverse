/* SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 *
 * P4 iteration 29 -- the ONE line in which the shipped G1 CPUNET firmware
 * diverges from the pinned NCS v2.5.1 `nrf/subsys/esb`.
 *
 * WHY THIS FILE EXISTS
 * --------------------
 * `nrf/subsys/esb/esb_peripherals.h` hardcodes
 *
 *     #define ESB_EVT_IRQ        SWI0_IRQn
 *     #define ESB_EVT_IRQHandler SWI0_IRQHandler
 *
 * but on the nRF5340 network core `nrf/subsys/mpsl/init/mpsl_init.c:38`
 * ALREADY owns SWI0 (`#define MPSL_LOW_PRIO_IRQn SWI0_IRQn`), and this
 * firmware runs ESB and MPSL/SDC on the same core.  The shipped image
 * therefore pends SWI3, not SWI0.  Measured, not assumed: the shipped bytes at
 * 0x01032e1c / 0x01032e30 (inside `on_radio_disabled_tx_noack`) and 0x01032fe0
 * (inside `on_radio_disabled_rx`) hold
 *
 *     f04f 5300   mov.w r3, #0x20000000   -> NVIC->ISPR[0] bit 29 = SWI3_IRQn
 *
 * where a stock SWI0 build emits
 *
 *     f04f 6380   mov.w r3, #0x04000000   -> NVIC->ISPR[0] bit 26 = SWI0_IRQn
 *
 * and those four bytes were the ONLY unmasked difference in the whole
 * 112-byte and 560-byte sections.  With this header (and
 * CONFIG_ESB_MAX_PAYLOAD_LENGTH=251) every esb.c section the shipped image
 * contains is relocation-masked byte-identical to the pinned stock source and
 * the 39 sections TILE 0x01032764..0x01033b18 with no gap and no overlap --
 * see recon/ownership/net_esb_core_singleton_adoption.json.
 *
 * The pinned SDK is NOT modified.  This file is force-included (`-include`)
 * into the `..__nrf__subsys__esb` library only; because it defines the SDK
 * header's own include guard, esb.c/esb_dppi.c/esb_ppi.c pick these
 * definitions up and the SDK body is skipped.
 */

#ifndef ESB_PERIPHERALS_H_
#define ESB_PERIPHERALS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <nrfx.h>
#include <nrfx_timer.h>

#include <hal/nrf_egu.h>

/** The ESB event IRQ number.  G1: SWI3, because MPSL owns SWI0 on CPUNET. */
#define ESB_EVT_IRQ        SWI3_IRQn
/** The handler for @ref ESB_EVT_IRQ. */
#define ESB_EVT_IRQHandler SWI3_IRQHandler

/** ESB timer instance number. */
#define ESB_TIMER_INSTANCE_NO CONFIG_ESB_SYS_TIMER_INSTANCE

#define ESB_TIMER_IRQ          NRFX_CONCAT_3(TIMER, ESB_TIMER_INSTANCE_NO, _IRQn)
#define ESB_TIMER_IRQ_HANDLER  NRFX_CONCAT_3(nrfx_timer_,		    \
					     ESB_TIMER_INSTANCE_NO, \
					     _irq_handler)

/** ESB nRF Timer instance */
#define ESB_NRF_TIMER_INSTANCE \
	NRFX_CONCAT_2(NRF_TIMER, ESB_TIMER_INSTANCE_NO)

/** ESB nrfx timer instance. */
#define ESB_TIMER_INSTANCE NRFX_TIMER_INSTANCE(ESB_TIMER_INSTANCE_NO)

/** ESB EGU instance, events and tasks configuration. */
#define ESB_EGU       NRF_EGU0
#define ESB_EGU_EVENT NRF_EGU_EVENT_TRIGGERED6
#define ESB_EGU_TASK  NRF_EGU_TASK_TRIGGER6

/** ESB additional EGU event and task for devices with DPPI. */
#define ESB_EGU_DPPI_EVENT NRF_EGU_EVENT_TRIGGERED7
#define ESB_EGU_DPPI_TASK  NRF_EGU_TASK_TRIGGER7

#ifdef __cplusplus
}
#endif

#endif /* ESB_PERIPHERALS_H_ */
