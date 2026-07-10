/*
 * ancs_notify: phone-notification ingest, filtering, queueing and display.
 *
 * Pulls notifications from the phone and shows them on the glasses. On iOS this
 * is Apple Notification Center Service (ANCS) as a GATT client (ancs_c_init,
 * request_ancs_attr_ext, bt_ancs_data_source_handler); on both platforms the
 * Even app can also push notifications over the app BLE protocol
 * (post_notification_cmd_process). Incoming notifications are parsed
 * (parse_ncs_notification / parse_receiver_*_pkcs7), filtered against a
 * per-app whitelist (load_whitelist / is_on_whitelist_by_identifier), stored in
 * a fixed message pool/table (push_message), de-duplicated and expired
 * (is_msg_expiration / clear_timeout_message), and rendered via gui_text's
 * draw_message. Runs on its own work thread (ancs_main, prio -11) fed by the
 * ANCS message queue g_ancs_msgq (see wiring.md).
 *
 * PUBLIC/INTERNAL SPLIT
 *   Only the functions in the reference graph's `api` set (= symbols actually
 *   called from OTHER modules, or exported callbacks reached through data) are
 *   declared public below. Everything the module calls only from inside itself
 *   (ancs_c_init, the parse/store/whitelist helpers, the thread/msgq plumbing)
 *   is module-internal and is declared `static` in the .c translation units;
 *   the internal prototypes here are kept commented for reference only.
 *
 *   Caveat: the api set also drags in a few generic utilities that physically
 *   live in this module but are used engine-wide (random, debug_print,
 *   local_store_write, uart_callback) plus a large 0x4d000-0x5a000 spillover
 *   cluster of low-level list / critical-section / persistence helpers that are
 *   NOT part of the ANCS logic (see README "Spillover cluster"). They are
 *   exposed here because the graph marks them cross-module, but they are not the
 *   subsystem's real surface.
 *
 * Type notes: some signatures keep Ghidra aliases; see the typedef block.
 */
#ifndef G1_ANCS_NOTIFY_H
#define G1_ANCS_NOTIFY_H

#include <stdint.h>

typedef uint8_t  byte; typedef uint8_t undefined1; typedef uint8_t u8;
typedef uint32_t u32; typedef uint32_t undefined4;
typedef void    *codeptr;

/* =========================================================================
 * PUBLIC API  (graph `api` set, 60 symbols)  — callable from other modules.
 * ========================================================================= */

/* ---- Notification / message subsystem (the real ANCS surface) ------------- */
void          bt_ancs_data_source_handler(int conn, unsigned char *data, int len); /* 0x18c48 ANCS GATT data-source cb */
void          post_notification_cmd_process(int a, unsigned char *buf, int len);   /* 0x338ec app-BLE post-notification cmd */
void          get_notification_counts_cmd_process(unsigned char *a, unsigned char *b, unsigned char *c); /* 0x33abc */
void          clear_timeout_message(int arg);                                      /* 0x33d58 TTL sweep */
unsigned int  is_msg_expiration(unsigned int a, unsigned int b, unsigned int c);   /* 0x3444c TTL test */
void          confirm_message(int idx);                                            /* 0x34524 mark read/handled */
uint32_t      mobile_send_notification_to_ble_device_test(uint32_t a, uint32_t b, uint32_t c); /* 0x21c04 test injector */
void          simulator_ancs_calendar_schedule_trigger(void);                      /* 0x21cd8 calendar sim */

/* ---- Whitelist / advertising ---------------------------------------------- */
int           ble_whitelist_app(undefined4 a, undefined4 b, codeptr cb, undefined4 d); /* 0x22218 */

/* ---- Cross-module state / status helpers ---------------------------------- */
unsigned int  update_temp_task_status(int a, unsigned int b, unsigned int c);      /* 0x2bffc */

/* ---- Module-hosted generic utilities (used engine-wide, live here) -------- */
unsigned int  random(void);                                                        /* 0x17f70 */
void          debug_print(void);                                                   /* 0x19c70 alt log sink */
unsigned int  local_store_write(int a, unsigned char *buf, unsigned int len);      /* 0x22168 */
void          uart_callback(unsigned int a, unsigned int b);                       /* 0x33384 */

/* ---- Unnamed api entries (FUN_*) — deduced roles in comments --------------
 * Small BLE / accessor helpers reached from ble_proto / audio / battery / system:
 */
u32           FUN_0000d588(void);            /* size 4 : trivial state accessor, many callers  */
u32           FUN_00012c18(int a);           /* ble_proto : small record deserialize helper     */
u32           FUN_000181fc(void);            /* size 6 : tiny getter (audio/ble/system)          */
u32           FUN_00018334(int a, int b);    /* battery/ble : bt attr build (FUN_0007ddbe/86fee) */
void          FUN_000183ac(int a, int b);    /* logging wrapper around FUN_00018334              */
u32           FUN_0002c1fc(int a);           /* esb_sync : message-table op wrapper (FUN_33cf8)  */
u32           FUN_0002c30c(void);            /* size 18 : tiny accessor (system)                 */
u32           FUN_000336a0(int a);           /* system : notification helper (FUN_00071c20)      */
u32           FUN_00033b4c(int a);           /* system : small message helper                    */
u32           FUN_00033c4c(void);            /* size 12 : flag/accessor (system)                 */
u32           FUN_00035498(int a, int b);    /* ble_proto : whitelist/notify cmd (uses 0x352e8) */
/* 0x4d000-0x5a000 spillover cluster: generic list / critical-section /
 * persistence helpers, NOT ANCS logic (see README). Cross-module leaves. */
u32           FUN_0004d508(int a);           /* thin wrapper -> FUN_0004bc28                      */
u32           FUN_0004ea78(void);            /* list/record builder (FUN_0007f4* helpers)         */
u32           FUN_0004ed8c(int a);           /* battery : record accessor                         */
u32           FUN_0004f518(int a);           /* flash_store : persistence helper                  */
u32           FUN_000507d4(void);            /* critical section (isCurrentModePrivileged/setBP)  */
u32           FUN_00051e9c(int a);           /* list op (FUN_0005160c/00080a4* series)            */
u32           FUN_00052180(int a);           /* list op                                           */
u32           FUN_000521fc(int a);           /* list op                                           */
u32           FUN_00052604(int a);           /* list op                                           */
u32           FUN_000526f4(void);            /* small helper                                      */
u32           FUN_000530c4(int a);           /* flash_store : persistence helper                  */
u32           FUN_000536b8(int a);           /* tree/list serialize (FUN_000566a4)                */
u32           FUN_00053bd8(int a);           /* tree/list op                                      */
u32           FUN_00054260(int a);           /* tree/list op                                      */
u32           FUN_00054308(int a);           /* tree/list op                                      */
u32           FUN_00054528(int a);           /* tree/list op                                      */
u32           FUN_00054828(int a);           /* tree/list op                                      */
u32           FUN_00054dd8(int a);           /* record helper                                     */
u32           FUN_000566a4(int a);           /* recursive tree walk (system callers)              */
u32           FUN_00056704(int a);           /* tree serialize (ble_proto/system)                 */
u32           FUN_000570a0(int a);           /* record op                                         */
u32           FUN_00057db0(int a);           /* large record/format builder (1184 bytes)          */
u32           FUN_000583d0(int a);           /* record op                                         */
u32           FUN_00058930(int a);           /* record op                                         */
u32           FUN_00058cfc(int a);           /* record op                                         */
u32           FUN_00058f80(int a);           /* record op                                         */
u32           FUN_000590bc(int a);           /* record op                                         */
u32           FUN_00059920(int a);           /* record op                                         */
u32           FUN_00059dec(int a);           /* small helper                                      */
u32           FUN_00059e78(int a);           /* battery : accessor                                */
u32           FUN_00059f04(int a);           /* record op                                         */
u32           FUN_0005a1b0(int a);           /* record op                                         */
u32           FUN_0005a28c(int a);           /* tiny helper (-> FUN_00082a42)                     */
u32           FUN_0005a3c4(int a);           /* record op                                         */
u32           FUN_0005a464(int a);           /* record op                                         */

/* =========================================================================
 * MODULE-INTERNAL  (NOT in api set) — declared `static` in the .c files.
 * Listed here for reference; do not link against these from other modules.
 * =========================================================================
 *  ANCS GATT client + link lifecycle:
 *    static int  ancs_c_init(int conn, unsigned,unsigned,unsigned);   0x1905c
 *    static int  request_ancs_attr_ext(unsigned,unsigned,unsigned);   0x191e4
 *    static void ancs_connected(int conn, int);                       0x1861c
 *    static void ancs_disconnected(unsigned,unsigned);                0x18adc
 *    static void ancs_security_changed(int,int,int);                  0x184f0
 *    static int  check_bind_status(int,int,int);                      0x26b88
 *  Worker thread + msgq plumbing:
 *    static void ancs_main(...);              (thread body)           0x19950
 *    static void start_ancs_work_thread(unsigned);                    0x198cc
 *    static int  init_msgq_ancs(void);                                0x18b6c
 *    static int  enqueue_ancs(unsigned);                              0x18bb4
 *    static int  dequeue_ancs(void*);                                 0x18d94
 *  Parse / store / expire:
 *    static void parse_ncs_notification(int,int*);                    0x34980
 *    static u32  parse_receiver_pack_pkcs7(int,uchar*,u32);           0x19cd0
 *    static u32  parse_receiver_msg_pack_pkcs7(int,uchar*,u32);       0x19da4
 *    static uchar push_message(int,int,int);                          0x33f54
 *    static int  post_notification_cmd_response(...);                 0x340c4
 *    static u32  process_for_new_message_come_on(byte*,int,char*,u32*);0x2c498
 *  Whitelist (flash-backed):
 *    static u32  load_whitelist(void);                                0x34b34
 *    static int  store_whitelist(void);                               0x35608
 *    static int  is_on_whitelist_by_identifier(int);                  0x34bd4
 *    static int  convert_app_whitelist_to_json(int,int,int);          0x352e8
 *    static void put_whitelist_app_from_app(u32,u32,u32,u32,u32);     0x35688
 *  Dashboard stocks/news feeds hosted here:
 *    static void cleanStocksIndex(void);                              0x37154
 *    static u32  handle_stocks_action(uchar,u32,u32,u32);             0x371e8
 *    static void cleanNewsIndex(void);                                0x37234
 *  Misc helpers:
 *    static int  le_adv_update(int,int,int,int,int,char,char);        0x811ce
 *    static u32  setDelayExitValue(u32);                              0x49000
 *    static u32  get_timestamp(void);                                 0x7d224
 *    static u32  uint32_to_little_endian(uchar*,u32,u32,u32);         0x4a568
 *    static void printf_like(...);                                    0x113a8
 *    static void memset_bytes(void*,int,int);                         0x86c78
 * ========================================================================= */

#endif /* G1_ANCS_NOTIFY_H */
