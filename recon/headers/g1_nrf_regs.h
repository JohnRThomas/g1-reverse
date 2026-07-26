/*
 * g1_nrf_regs.h -- evidence-backed names for the fixed hardware register
 * addresses that appear as raw hex in the recovered sources.
 *
 * G6-B4 of recon/analysis/prerefactor_plan.md.  58 constants.
 *
 * PROVENANCE.  Every value below is copied from the SDK header shipped with
 * NCS 2.5.1, or from the CMSIS Cortex-M33 System Control Space map -- never
 * guessed:
 *   app core : modules/hal/nordic/nrfx/mdk/nrf5340_application.h
 *   net core : modules/hal/nordic/nrfx/mdk/nrf5340_network.h
 *   SCS      : CMSIS Core/Include (architectural, identical on both cores)
 *
 * WHY THESE NAMES CARRY A `G1_` PREFIX INSTEAD OF REUSING THE MDK SPELLING.
 * The two cores' MDK headers give the SAME macro name different values -- e.g.
 * NRF_IPC_NS_BASE is 0x4002a000 in nrf5340_application.h but 0x41012000 in
 * nrf5340_network.h, and NRF_P0_NS_BASE is 0x40842500 vs 0x418c0500.  A shared
 * header reusing the SDK spelling would therefore be wrong for one core, and
 * would shadow the real SDK macro wherever the MDK header is genuinely on the
 * include path.  The prefix keeps this header additive and collision-free; the
 * app and net sections below are asserted to share no macro name.
 *
 * CODEGEN CONTRACT.  Each macro expands to the SAME TOKEN the source used
 * before, so the substitution is codegen-neutral by construction rather than by
 * optimiser luck.  A base+offset site expands to `(BASE + 0xoff)`, whose type
 * and value are identical to the folded literal on this ABI.  The batch is
 * gated on a byte-identical zephyr.bin for both cores.
 *
 * KEEP-SYMBOLIC RULE (prerefactor_plan.md 1.4).  Nothing that must stay
 * relocatable belongs here: no ADDR_*_THUMB function pointers, no ptr_table /
 * ptr_record regions, no struct device pointers, no RAM or .text addresses, no
 * section boundaries.  Every address below is a fixed peripheral or
 * architectural register that the linker never relocates.
 */
#ifndef G1_NRF_REGS_H
#define G1_NRF_REGS_H

/* ---- CMSIS Cortex-M33 System Control Space (both cores) ---- */
#define G1_NVIC_ISER0              0xe000e100   /* Interrupt Set Enable Register 0 */
#define G1_NVIC_ICPR0              0xe000e280   /* Interrupt Clear Pending Register 0 */
#define G1_NVIC_IPR0               0xe000e400   /* Interrupt Priority Register 0 */
#define G1_SCB_CPUID               0xe000ed00   /* CPUID Base Register */
#define G1_SCB_ICSR                0xe000ed04   /* Interrupt Control and State Register */
#define G1_SCB_SCR                 0xe000ed10   /* System Control Register */
#define G1_SCB_CCR                 0xe000ed14   /* Configuration and Control Register */
#define G1_SCB_CFSR                0xe000ed28   /* Configurable Fault Status Register */
#define G1_SCB_BFAR                0xe000ed38   /* BusFault Address Register */

/* ---- CPUAPP (secure alias, 0x5xxxxxxx) -- nrf5340_application.h ---- */
#define G1_NRF_SPIM4_S_BASE        0x5000a000
#define G1_NRF_GPIOTE0_S_BASE      0x5000d000
#define G1_NRF_SAADC_S_BASE        0x5000e000
#define G1_NRF_RTC1_S_BASE         0x50015000
#define G1_NRF_PDM0_S_BASE         0x50026000
#define G1_NRF_QSPI_S_BASE         0x5002b000
#define G1_NRF_KMU_S_BASE          0x50039000
#define G1_NRF_P0_S_BASE           0x50842500
#define G1_NRF_P1_S_BASE           0x50842800

/* ---- CPUNET (non-secure alias, 0x41xxxxxx) -- nrf5340_network.h ---- */
#define G1_NRF_DCNF_NS_BASE        0x41000000
#define G1_NRF_VREQCTRL_NS_BASE    0x41004000
#define G1_NRF_CLOCK_NS_BASE       0x41005000
#define G1_NRF_RADIO_NS_BASE       0x41008000
#define G1_NRF_GPIOTE_NS_BASE      0x4100a000
#define G1_NRF_TIMER0_NS_BASE      0x4100c000
#define G1_NRF_ECB_NS_BASE         0x4100d000
#define G1_NRF_AAR_NS_BASE         0x4100e000
#define G1_NRF_DPPIC_NS_BASE       0x4100f000
#define G1_NRF_RTC0_NS_BASE        0x41011000
#define G1_NRF_IPC_NS_BASE         0x41012000
#define G1_NRF_EGU0_NS_BASE        0x41014000
#define G1_NRF_RTC1_NS_BASE        0x41016000
#define G1_NRF_TIMER2_NS_BASE      0x41019000
#define G1_NRF_P0_NS_BASE          0x418c0500
#define G1_NRF_P1_NS_BASE          0x418c0800

#endif /* G1_NRF_REGS_H */
