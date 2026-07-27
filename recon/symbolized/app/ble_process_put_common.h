#ifndef G1_BLE_PROCESS_PUT_COMMON_H
#define G1_BLE_PROCESS_PUT_COMMON_H

#include <stdint.h>
#include <stddef.h>

#define BLE_PUT_ALWAYS_INLINE static inline __attribute__((always_inline))

typedef int (*ble_put_post_fn)(const void *message, uint32_t length);

/* Only the stable prefix shared by every PUT handler is named here.  Handler
 * families use byte-addressed accessors for their independently reviewed tail
 * fields so an inferred aggregate layout cannot change an access width. */
struct ble_put_context {
    uint8_t reserved_00[0x0c];
    ble_put_post_fn post_to_host; /* +0x0c */
    uint8_t *transfer;            /* +0x10 */
    uint32_t transfer_length;     /* +0x14 */
};

BLE_PUT_ALWAYS_INLINE uint16_t ble_put_le16(const void *p)
{
    const uint8_t *b = (const uint8_t *)p;
    return (uint16_t)b[0] | (uint16_t)((uint16_t)b[1] << 8);
}

BLE_PUT_ALWAYS_INLINE uint32_t ble_put_le32(const void *p)
{
    const uint8_t *b = (const uint8_t *)p;
    return (uint32_t)b[0] | ((uint32_t)b[1] << 8) |
           ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

BLE_PUT_ALWAYS_INLINE void ble_put_store16(void *p, uint16_t v)
{
    *(uint16_t *)p = v;
}

/* Firmware symbols retain unprototyped declarations until each reviewed call
 * site has been reconciled; this preserves the recovered integer ABI without
 * inventing cross-core/shared structure types. */
extern int get_device_type();
extern int get_device_info();
extern int ble_work_queue_lock();
extern int ble_work_queue_unlock();
extern int audio_fw_load_get_wrapper();
extern void debug_print(unsigned long, ...);
extern int send_response_data_to_msgqueue();
extern int get_ui_mode_flag2();
extern int SendDashBoardStartupModeInfoToSlave();
extern int unix_timestamp_to_datetime();
extern int rate_limited_elapsed_seconds_tick();
extern int record_dashboard_startup_snapshot();
extern int dashboard_startup_info_write_magic();
extern int device_info_copy_record_fields();
extern int upgradeQuickNoteDataToFlash();
extern int deleteQuickNoteData();
extern int cleanStocksIndex();
extern int cleanNewsIndex();
extern int memcmp();
extern int memcpy();
extern int safe_memcpy_checked();
extern int memset_bytes();
extern void log_message(unsigned long, ...);

#define BLE_LOG_LEVEL (*(volatile int32_t *)(uintptr_t)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define BLE_IS_DEBUG  (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define BLE_LUMINANCE_SOURCE (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_20011d81) /*=0x20011d81*/)

enum ble_put_handler_result {
    BLE_PUT_HANDLER_BREAK = 0,
    BLE_PUT_HANDLER_RETURN = 1,
    BLE_PUT_HANDLER_UNHANDLED = 2
};

#endif
