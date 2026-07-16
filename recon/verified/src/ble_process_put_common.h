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
extern int FUN_00016568();
extern int FUN_000167a8();
extern int FUN_00019b38();
extern int FUN_00019b48();
extern int FUN_00019b54();
extern int FUN_00019c70();
extern int FUN_00047b1c();
extern int FUN_00023eec();
extern int FUN_00048a3c();
extern int FUN_0004a1b8();
extern int FUN_0004a46c();
extern int FUN_0004a4b4();
extern int FUN_000165a4();
extern int FUN_000165cc();
extern int FUN_00024420();
extern int FUN_000244a8();
extern int FUN_00037154();
extern int FUN_00037234();
extern int FUN_00086be4();
extern int FUN_00086c04();
extern int FUN_00086c1e();
extern int FUN_00086c78();
extern int DEBUG_PRINT();

#define BLE_LOG_LEVEL (*(volatile int32_t *)(uintptr_t)0x2000230c)
#define BLE_IS_DEBUG  (*(volatile uint32_t *)(uintptr_t)0x20007554)
#define BLE_LUMINANCE_SOURCE (*(volatile uint8_t *)(uintptr_t)0x20011d81)

enum ble_put_handler_result {
    BLE_PUT_HANDLER_BREAK = 0,
    BLE_PUT_HANDLER_RETURN = 1,
    BLE_PUT_HANDLER_UNHANDLED = 2
};

#endif
