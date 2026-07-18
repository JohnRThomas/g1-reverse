/* readable reconstruction; identity: FUN_00019950 @ 0x00019950
 * public-name: ancs_main
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   ADDR_check_bonded_addr_THUMB             @ 0x000183e5
 *   rodata_9af3b                             @ 0x0009af3b
 *   rodata_9af75                             @ 0x0009af75
 *   rodata_9afa1                             @ 0x0009afa1
 *   rodata_9afc3                             @ 0x0009afc3
 *   rodata_9afed                             @ 0x0009afed
 *   rodata_9b019                             @ 0x0009b019
 *   rodata_9b04b                             @ 0x0009b04b
 *   rodata_9b060                             @ 0x0009b060
 *   rodata_9b089                             @ 0x0009b089
 *   rodata_9b0ae                             @ 0x0009b0ae
 *   rodata_9b135                             @ 0x0009b135
 *   g_log_level                              @ 0x2000230c
 *   g_20002320                               @ 0x20002320
 *   g_20002328                               @ 0x20002328
 *   g_20002338                               @ 0x20002338
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2000ff87                               @ 0x2000ff87
 */
/* Readable reconstruction of FUN_00019950 @ 0x00019950. */
#include <stdint.h>

/* Callee back-map: every semantic alias retains the firmware identity used by
 * the parity linker. */
extern uintptr_t get_device_info(void);                 /* FUN_000167a8 @ 0x000167a8 */
extern int ancs_c_init(void *client);                   /* FUN_0001905c @ 0x0001905c */
extern int ancs_discover_params_reset(void);            /* FUN_000191d8 @ 0x000191d8 */
extern int bt_start(void);                              /* FUN_00019308 @ 0x00019308 */
extern void start_ancs_work_thread(uintptr_t context);  /* FUN_000198cc @ 0x000198cc */
extern void debug_print(void);                          /* FUN_00019c70 @ 0x00019c70 */
extern void sys_reboot(int type);                       /* FUN_0004c0a8 @ 0x0004c0a8 */
extern int bt_enable(int mode);                           /* FUN_00054a44 @ 0x00054a44 */
extern void bt_hci_driver_close(void);                  /* FUN_00054b70 @ 0x00054b70 */
extern int bt_conn_auth_info_cb_register(const void *); /* FUN_00057330 @ 0x00057330 */
extern void bt_gatt_cb_register(const void *);          /* FUN_0005a9d8 @ 0x0005a9d8 */
extern void bt_foreach_bond(unsigned int, const void *);/* FUN_0005e6d4 @ 0x0005e6d4 */
extern int settings_load(void);                         /* FUN_0007f192 @ 0x0007f192 */
extern int log_message(const char *format, ...);        /* FUN_0007dda4 @ 0x0007dda4 */

extern void FUN_0007c0a8(unsigned int milliseconds);
extern int FUN_000572fc(const void *callbacks);
extern int FUN_000181f0(void);

#define ancs_sleep_ms                 FUN_0007c0a8 /* k_msleep adapter @ 0x0007c0a8 */
#define bt_conn_auth_cb_register      FUN_000572fc /* FUN_000572fc @ 0x000572fc */
#define ancs_notify_sync_init         FUN_000181f0 /* FUN_000181f0 @ 0x000181f0 */

/* Absolute object and string identities are intentionally retained.  Their
 * names describe use here; the address is the durable back-map. */
#define ANCS_ACTIVE_CONTEXT       (*(volatile uintptr_t *)0x20006ab8u)
#define LOG_LEVEL                 (*(volatile int *)0x2000230cu)
#define LOG_USE_ALT_SINK          (*(volatile uint32_t *)0x20007554u)
#define ANCS_AUTH_CALLBACKS       ((const void *)0x20002338u)
#define ANCS_AUTH_INFO_CALLBACKS  ((const void *)0x20002328u)
#define ANCS_GATT_CALLBACKS       ((const void *)0x20002320u)
#define CHECK_BONDED_ADDR_CB      ((const void *)0x000183e5u) /* check_bonded_addr + Thumb bit */
#define ADVERTISING_KIND          ((const char *)0x2000ff87u)

#define STR_ANCS_START            ((const char *)0x0009af3bu)
#define STR_ANCS_MAIN             ((const char *)0x0009b135u)
#define STR_BT_INIT_FAILED        ((const char *)0x0009af75u)
#define STR_ANCS_INIT_FAILED      ((const char *)0x0009afa1u)
#define STR_INIT_REBOOT           ((const char *)0x0009b089u)
#define STR_REBOOT_REASON         ((const char *)0x0009b0aeu)
#define STR_DISCOVERY_INIT_FAILED ((const char *)0x0009afc3u)
#define STR_AUTH_CB_FAILED        ((const char *)0x0009afedu)
#define STR_AUTH_INFO_FAILED      ((const char *)0x0009b019u)
#define STR_NOTIFY_INIT_FAILED    ((const char *)0x0009b04bu)
#define STR_ADVERTISING_FAILED    ((const char *)0x0009b060u)

struct device_info_view {
    uint8_t opaque[0x1058];
    uint8_t initialized;
};

static inline __attribute__((always_inline)) void log_start_if_enabled(void)
{
    if (LOG_LEVEL > 0) {
        if (LOG_USE_ALT_SINK == 0) {
            log_message(STR_ANCS_START, STR_ANCS_MAIN);
        } else {
            debug_print();
        }
    }
}

static inline __attribute__((always_inline)) void reboot_after_ancs_failure(void)
{
    log_message(STR_INIT_REBOOT);
    ancs_sleep_ms(1000);

    if (LOG_LEVEL > 0) {
        if (LOG_USE_ALT_SINK == 0) {
            log_message(STR_REBOOT_REASON, STR_ANCS_MAIN);
        } else {
            debug_print();
        }
    }

    ancs_sleep_ms(500);
    sys_reboot(1);
}

int ancs_main(uintptr_t context)
{
    int error;
    unsigned int ready_retries = 50;
    unsigned int send_retries = 5;

    ANCS_ACTIVE_CONTEXT = context;
    log_start_if_enabled();

    do {
        while (((const struct device_info_view *)get_device_info())->initialized == 0 &&
               ready_retries != 0) {
            --ready_retries;
            ancs_sleep_ms(100);
        }

        error = bt_enable(0);
        if (error == 0) {
            break;
        }

        bt_hci_driver_close();
        log_message(STR_BT_INIT_FAILED, error, send_retries);
        --send_retries;
        ancs_sleep_ms(1000);
    } while (send_retries != 0);

    bt_foreach_bond(0, CHECK_BONDED_ADDR_CB);
    settings_load();

    error = ancs_c_init((void *)(context + 0x34));
    if (error != 0) {
        log_message(STR_ANCS_INIT_FAILED, error);
        reboot_after_ancs_failure();
        return error;
    }

    error = ancs_discover_params_reset();
    if (error != 0) {
        log_message(STR_DISCOVERY_INIT_FAILED, error);
        reboot_after_ancs_failure();
        return error;
    }

    error = bt_conn_auth_cb_register(ANCS_AUTH_CALLBACKS);
    if (error != 0) {
        log_message(STR_AUTH_CB_FAILED);
        reboot_after_ancs_failure();
        return error;
    }

    error = bt_conn_auth_info_cb_register(ANCS_AUTH_INFO_CALLBACKS);
    if (error != 0) {
        log_message(STR_AUTH_INFO_FAILED);
        reboot_after_ancs_failure();
        return error;
    }

    bt_gatt_cb_register(ANCS_GATT_CALLBACKS);
    error = ancs_notify_sync_init();
    if (error != 0) {
        log_message(STR_NOTIFY_INIT_FAILED);
        reboot_after_ancs_failure();
        return error;
    }

    error = bt_start();
    if (error != 0) {
        log_message(STR_ADVERTISING_FAILED, ADVERTISING_KIND, error);
        reboot_after_ancs_failure();
        return error;
    }

    start_ancs_work_thread(context);
    return 0;
}
