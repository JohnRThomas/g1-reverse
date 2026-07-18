/*
 * misc — cross-module shared runtime (the "everything the whole image calls"
 * layer), NOT a coherent feature subsystem.
 *
 * This bucket is the residue the topic classifier could not attribute to a
 * feature module (181 functions). Reconstruction of the reference graph shows
 * what it actually is: the low-level substrate that EVERY feature module reaches
 * into — Zephyr kernel-object primitives (k_msgq/k_sem/k_timer/k_work impls),
 * ARM MPU configuration, nrfx/nRF peripheral + sensor driver init/config,
 * BLE/settings/SMP glue, and libc/math runtime (out/printf sink, __errno,
 * atan2f, strtod/dtoa, crc32). It owns 722 data objects.
 *
 * PUBLIC API (below) = exactly the graph's `api` set: the 55 functions reached
 * from OTHER modules. Everything else in the group (~126 FUN_*) is internal
 * (leaf helpers, jump-table targets, or thread/callback entry points invoked
 * only via pointer) and is NOT declared here — treat it as static to the image.
 *
 * As functions here get named and understood they should migrate OUT into the
 * owning real module (display, ble_proto, battery/sensors, libc-runtime, ...).
 */
#ifndef G1_MISC_H
#define G1_MISC_H

#include <stdint.h>
typedef unsigned char byte;

/* ---- ARM MPU / memory protection --------------------------------------- */
unsigned arm_core_mpu_configure(unsigned *cfg, int part, unsigned n);        /* 0x50c54 */
void mpu_partition_sanity_check_assert(int *p, int a, uint32_t b);           /* 0x50e64 */

/* ---- Zephyr device-driver / timer core --------------------------------- */
uint32_t driver_register_callback_locked(int *dev, uint32_t cb, uint32_t d); /* 0x848d2 */
int      driver_stop_active_timer(int dev);                                  /* 0x84c2c */
unsigned FUN_00084516(int a, unsigned b, int c, unsigned d);                 /* 0x84516 us->ticks scaling */
int      FUN_0008493a(int dev, unsigned char *out);                          /* 0x8493a driver query */
unsigned int FUN_000851f4(void);                                             /* 0x851f4 */

/* ---- nrfx / nRF peripheral + sensor driver init & config --------------- */
int      FUN_000620cc(int dev);                                              /* 0x620cc */
uint32_t FUN_00062930(int dev);                                              /* 0x62930 i2c_read_reg16 sensor probe */
unsigned int FUN_00062c54(int dev, int cfg);                                 /* 0x62c54 pinctrl_apply_state */
void     FUN_00063898(int a, unsigned b, unsigned c, unsigned d);            /* 0x63898 */
unsigned FUN_000639d4(int dev);                                             /* 0x639d4 */
void     FUN_00064fa8(unsigned a, int b, unsigned c, unsigned d);            /* 0x64fa8 */
void     FUN_00065324(int a, int b);                                         /* 0x65324 */
unsigned int FUN_00065d3c(unsigned a, int b, int c);                         /* 0x65d3c */
void     FUN_00065d8c(int a, uint32_t b, uint32_t c, uint32_t d);            /* 0x65d8c */
void     FUN_00067600(int a, int *b);                                        /* 0x67600 */
uint32_t FUN_00067794(int a, int *b, uint32_t c, uint32_t d);                /* 0x67794 nrf_gpio reconfigure */
uint32_t g1_recon_nrfx_wdt_channel_alloc(int *inst, uint8_t *chan);          /* FUN_00067e8c @ 0x67e8c */
void     FUN_00083778(int a);                                                /* 0x83778 adc_context_start_sampling */

/* ---- Display page state ------------------------------------------------- */
void set_display_page_index(unsigned idx);                                   /* 0x369dc */
void advance_display_page_index(void);                                       /* 0x369f8 */

/* ---- BLE / settings / SMP glue ----------------------------------------- */
void bt_le_adv_clear_pending_flag(int adv);                                  /* 0x81080 */
void FUN_00052f68(void);                                                     /* 0x52f68 bt_settings_store */
unsigned smp_process_request_packet(int *hdr, int req);                      /* 0x85cf2 mcumgr/SMP */

/* ---- libc / math runtime ------------------------------------------------ */
void  out(unsigned char c, int *ctx);      /* 0x7dd7e printf/snprintf putc sink */
int   __errno_location(void);              /* 0x71678 */
float atan2f(float y, float x);            /* 0x76154 */

/* ---- DSP / int16 sample buffer transforms ------------------------------ */
void FUN_0006a700(long long *acc, int n, short *in, int stride);             /* 0x6a700 */
void FUN_0006aa98(int64_t *acc, int n, int16_t *in, int stride);             /* 0x6aa98 */

/* ---- byte/word buffer + integer helpers -------------------------------- */
void     FUN_000844a8(int *dst, unsigned char v, unsigned len, unsigned d);  /* 0x844a8 fill */
void     FUN_000844e0(int *dst, unsigned char v, unsigned len, unsigned d);  /* 0x844e0 fill */
unsigned FUN_000839fe(int a, int b, int c, int d);                           /* 0x839fe memcpy wrapper */
int      FUN_00083cfc(int a, int b, unsigned c, unsigned d);                 /* 0x83cfc */
unsigned FUN_0007f894(unsigned a, unsigned b, unsigned short *c, unsigned d);/* 0x7f894 */
void     FUN_0007faa8(unsigned a, unsigned short *b);                        /* 0x7faa8 */
void     FUN_0007fae4(unsigned a, unsigned short *b);                        /* 0x7fae4 */
void     FUN_00079780(uint32_t *a, uint32_t *b);                             /* 0x79780 */
void     FUN_00082fa6(int a);                                                /* 0x82fa6 */
void     FUN_0007e526(void);                                                 /* 0x7e526 */
unsigned int FUN_0007ca54(int a, unsigned b, unsigned c);                    /* 0x7ca54 */
unsigned int FUN_00086b40(int a, float b, unsigned c, unsigned d);           /* 0x86b40 */

/* ---- unclassified integer/state routines (proven bodies, role TBD) ----- */
void         FUN_0002a4c0(void);                                             /* 0x2a4c0 */
int          FUN_00030c24(unsigned a, unsigned b, unsigned c, unsigned d);   /* 0x30c24 */
unsigned int FUN_00033bc4(void);                                             /* 0x33bc4 */
void         FUN_0004b1c0(uint32_t a);                                       /* 0x4b1c0 */
void         FUN_0004f1d0(int a, int b, unsigned c);                         /* 0x4f1d0 */
void         FUN_00051038(uint32_t a);                                       /* 0x51038 */
int          FUN_00052854(int a, int b);                                     /* 0x52854 */
unsigned int FUN_00052d58(int a, int b, void *cb, int d);                    /* 0x52d58 */
void         FUN_0005edac(int a, int b, int c, int d, int *e);               /* 0x5edac */
void         FUN_00060564(int a, void *jt);                                  /* 0x60564 */
unsigned int FUN_00060778(unsigned a);                                       /* 0x60778 */
unsigned int FUN_00061c40(int a, unsigned b, int c);                         /* 0x61c40 */
void         FUN_000658dc(unsigned a, unsigned b);                           /* 0x658dc */

#endif /* G1_MISC_H */
