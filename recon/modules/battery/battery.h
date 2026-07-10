/*
 * battery: fuel gauge, charge state, critical/shutdown handling, ambient light,
 *          and the battery-gated peer-link (GATT) helpers.
 *
 * Core responsibility: track the pack's state-of-charge from the fuel gauge
 * (fuel_gauge_update), read the charging-case ("glass box") status/percent,
 * maintain the low-power / critical-shutdown flag (set at 0x20019ef3 by the
 * setter FUN_00032ef0, read by is_battery_critical, acted on by
 * check_battery_critical / set_shutdown_flag), and load/persist the user power
 * settings. It also owns the OPT3007 ambient-light sensor over I2C
 * (opt3007_chip_init / get_lux_info / opt3007_get_max_lux), whose lux reading
 * feeds the display auto-brightness path. SoC lands in the shared device_info
 * block, is reported to the phone and mirrored to the slave lens.
 *
 * NOTE ON SCOPE: the reference graph's "battery" unit also pulls in a set of
 * peer BLE-link / GATT-discovery helpers (the 0x187xx family, FUN_00059c70).
 * These are not battery-core; they are grouped here because every one of them
 * gates on is_battery_critical() before touching the radio. They are exported
 * because other modules call them, so they appear below, clearly separated.
 *
 * This module defines NO RTOS objects (no thread/msgq/sem/work/timer). It is a
 * passive library polled by other modules' threads -- see wiring.md.
 */
#ifndef G1_BATTERY_H
#define G1_BATTERY_H

#include <stdint.h>

/* ====================================================================== */
/* PUBLIC API  (exactly the reference graph's api set for unit "battery";  */
/*              functions called from outside the module)                  */
/* ====================================================================== */

/* ---- fuel gauge / state of charge ------------------------------------ */
int           fuel_gauge_update(unsigned int arg);          /* 0x10b18 */
unsigned char get_glassbox_charge_status(void);             /* 0x32784 */
unsigned char get_glassbox_charge_percent(void);            /* 0x327c4 */

/* ---- critical / low-power / shutdown ---------------------------------- */
unsigned int  check_battery_critical(int devinfo);          /* 0x2bed0: spin-wait
                                 guard on 0x20018d9c, returns devinfo+0xd5 > 1  */
unsigned char is_battery_critical(void);                    /* 0x32ee4: read flag
                                                               byte @0x20019ef3  */
void          set_battery_critical_flag(unsigned int v);    /* 0x32ef0 (FUN_00032ef0):
                                                write flag byte @0x20019ef3 + log */
void          set_shutdown_flag(int devinfo, int emit_evt); /* 0x7cbfe */

/* ---- user power settings (flash-backed) ------------------------------- */
int           load_usr_setting(int arg);                    /* 0x22e78 */
int           usr_setting_write_flash(int arg);             /* 0x7c28e (FUN_0007c28e):
                                          flash_settings_write_and_verify @0x134000 */
unsigned int  get_product_code_buf(void);                   /* 0x232b8 (FUN_000232b8):
                                             returns &g_product_code_buf 0x20002fe3 */

/* ---- charge-box BLE status report ------------------------------------- */
unsigned      ble_encode_charge_status_report(int ctx, unsigned short *req);
                                                            /* 0x21334 (FUN_00021334):
                                    builds 0xc9xx status packet incl. charge box  */

/* ---- OPT3007 ambient-light sensor (I2C) -> auto-brightness ------------ */
uint32_t      opt3007_chip_init(int arg);                   /* 0x2e67c */
void          opt3007_chip_deinit(unsigned int a, unsigned int b,
                                  unsigned int c, unsigned int d); /* 0x2e8b4 */
int           opt3007_get_max_lux(unsigned int a, unsigned int b,
                                  unsigned int c, unsigned int d); /* 0x10a68 */
uint32_t      get_lux_info(uint32_t a, uint32_t b,
                           uint32_t *out_lux, uint8_t *out_flag);  /* 0x10fc8 */
int           opt3007_read_lux_raw(unsigned int reg, unsigned int a,
                                   unsigned int b);         /* 0x2e648 (FUN_0002e648):
                                     I2C reg read + (mantissa<<exponent) convert  */

/* ---- battery-gated peer BLE-link / GATT helpers (topic-adjacent) ------ */
void          peer_device_info_refresh(unsigned a, unsigned b);    /* 0x18730 */
void          peer_gatt_subscribe_start(uint32_t conn, int retry); /* 0x187e8 */
void          gatt_dm_cb_a(unsigned int arg);               /* 0x18894 (log wrapper) */
void          gatt_dm_cb_b(unsigned int arg);               /* 0x188b0 (log wrapper) */
void          gatt_discovery_complete_cb(void *a, void *b); /* 0x188d8 */
void          gatt_dm_cb_c(unsigned int arg);               /* 0x18978 (log wrapper) */
void          gatt_discovery_not_found_cb(unsigned a, unsigned b); /* 0x189a0 */
void          gatt_dm_cb_d(unsigned int arg);               /* 0x18a1c (log wrapper) */
unsigned char *lookup_known_device(int conn);               /* 0x59c70 (FUN_00059c70):
                                     scan g_known_device_table 0x2000af18 (3x0x10) */

/* ====================================================================== */
/* INTERNAL (module-private; NOT in the graph api set -- keep static in .c) */
/*   FUN_0000e340  gauge-math helper (single caller: fuel_gauge_update)     */
/*   FUN_0002e988  opt3007 sample/state helper                              */
/*   FUN_0002ea28  opt3007 sample/ISR handler (entry point)                 */
/*   FUN_00030cac  trivial SoC accessor                                     */
/*   FUN_000330c4 / FUN_000330d8  -> FUN_0007c8b0/8c4 mutex thunks           */
/*   FUN_0004ee68 / FUN_0004f040 / FUN_0004f0ec / FUN_0004f418  GATT DM /    */
/*                 CCC-subscribe workers used by the 0x188xx callbacks       */
/*   FUN_0005420c  bond-clear (bt_foreach_bond / unpair)                     */
/*   FUN_0005c3c4  GATT notify to known device                              */
/*   FUN_0007c8b0 / FUN_0007c8c4  k_ thunks                                  */
/*   FUN_0007cef6 / FUN_0007cefc  flag helpers                              */
/*   FUN_0007f4c8 / FUN_0007f4cc / FUN_0007f4d2 / FUN_0007f8dc  atomic-flag  */
/*                 / GATT-DM leaf helpers                                    */
/* ====================================================================== */

#endif /* G1_BATTERY_H */
