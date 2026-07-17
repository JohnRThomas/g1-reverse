/* readable reconstruction; identity: FUN_00024684 @ 0x00024684
 * public-name: getQuickNoteBKPQueueCacheData
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   getQuickNoteBKPQueueCacheData            <= FUN_00024684 @ 0x00024684
 *   reset_touch_selection_state              <= FUN_00037098 @ 0x00037098
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9eba7                             @ 0x0009eba7
 *   rodata_9ebc6                             @ 0x0009ebc6
 *   rodata_9ee54                             @ 0x0009ee54
 *   rodata_9ef15                             @ 0x0009ef15
 *   rodata_9ef67                             @ 0x0009ef67
 *   rodata_9efaf                             @ 0x0009efaf
 *   rodata_9f010                             @ 0x0009f010
 *   rodata_9f032                             @ 0x0009f032
 *   rodata_9f050                             @ 0x0009f050
 *   g_log_level                              @ 0x2000230c
 *   g_quicknote_flash_msgq                   @ 0x20003960
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_quicknote_flash_page_buf               @ 0x20018465
 */
/* Reconstructed FUN_00024684 @ 0x24684. */
#include <stdint.h>

extern int k_msgq_get(void *queue, void *request, uint32_t timeout,
                        uint32_t flags);
extern void DEBUG_PRINT(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern int z_device_is_ready(const void *object);
extern void memset_bytes(void *destination, int value, uint32_t length);
extern int FUN_00086be4(const void *left, const void *right, uint32_t length);
extern void memcpy(void *destination, const void *source, uint32_t length);
extern uint8_t *get_device_info(void);
extern void reset_touch_selection_state(void);

typedef int (*flash_read_fn)(void *owner, uint32_t address,
                             void *destination, uint32_t length);
typedef int (*flash_write_fn)(void *owner, uint32_t address,
                              const void *source, uint32_t length);
typedef int (*flash_erase_fn)(void *owner, uint32_t address, uint32_t length);

struct flash_runtime {
    uint8_t reserved[0x20];
    const uint8_t *default_slots;
    uint8_t reserved_24[0x0c];
    flash_read_fn read;
    flash_write_fn write;
    flash_erase_fn erase;
};

struct slot_request {
    uint32_t operation;
    uint32_t slot;
    uint32_t value;
};

static volatile int *const log_level = (volatile int *)0x2000230cu;
static volatile int *const deferred_logger = (volatile int *)0x20007554u;
static uint8_t *const slot_image = (uint8_t *)0x20018465u;
static const uint32_t slot_flash_address = 0x00403000u;

static inline __attribute__((always_inline)) struct flash_runtime *runtime_ops(void)
{
    return (struct flash_runtime *)(get_device_info() + 0x1000);
}

static inline __attribute__((always_inline)) const uint8_t *default_record(uint8_t slot)
{
    return runtime_ops()->default_slots + slot * 0x143u;
}

static inline __attribute__((always_inline)) void copy_default_header(
    uint8_t *destination, const uint8_t *source)
{
    unsigned int index;

    for (index = 0; index < 10; ++index)
        ((uint32_t *)destination)[index] = ((const uint32_t *)source)[index];
    destination[40] = source[40];
}

static inline __attribute__((always_inline)) void log_fixed(uint32_t format)
{
    if (*deferred_logger == 0)
        DEBUG_PRINT(format, 0x0009f050u);
    else
        debug_print(format, 0x0009f050u);
}

static inline __attribute__((always_inline)) void log_value(uint32_t format,
                                                            uint32_t value)
{
    if (*deferred_logger == 0)
        DEBUG_PRINT(format, 0x0009f050u, value);
    else
        debug_print(format, 0x0009f050u, value);
}

static inline __attribute__((always_inline)) int read_slot_image(void)
{
    struct flash_runtime *ops;
    flash_read_fn read;

    memset_bytes(slot_image, 0, 0x800);
    ops = runtime_ops();
    read = ops->read;
    return read(get_device_info(), slot_flash_address, slot_image, 0x800);
}

static inline __attribute__((always_inline)) int flush_slot_image(void)
{
    struct flash_runtime *ops;
    flash_erase_fn erase;
    flash_write_fn write;
    int result;

    ops = runtime_ops();
    erase = ops->erase;
    result = erase(get_device_info(), slot_flash_address, 0x1000);
    if (result != 0)
        return result;

    ops = runtime_ops();
    write = ops->write;
    return write(get_device_info(), slot_flash_address, slot_image, 0x800);
}

int getQuickNoteBKPQueueCacheData(uint32_t operation, uint32_t slot, uint32_t value)
{
    struct slot_request request = { operation, slot, value };
    uint8_t slot_number;
    int result;

    result = k_msgq_get((void *)0x20003960u, &request, 0, 0);
    if (result != 0) {
        if (*log_level < 1)
            return -1;
        if (*deferred_logger == 0)
            DEBUG_PRINT(0x0009ef15u, 0x0009f032u);
        else
            debug_print(0x0009ef15u, 0x0009f032u);
        if (*log_level < 1)
            return -1;
        log_fixed(0x0009ef3fu);
        return -1;
    }

    operation = (uint8_t)request.operation;
    if (operation != 1 && operation != 2)
        return 0;

    slot_number = (uint8_t)request.slot;
    if (slot_number > 3) {
        if (*log_level < 1)
            return -1;
        log_fixed(0x0009ee54u);
        return -1;
    }

    if (*log_level > 2)
        log_fixed(0x0009ef67u);

    if (operation == 2)
        reset_touch_selection_state();

    if (z_device_is_ready((const void *)0x00087bf0u) == 0) {
        if (*log_level > 0)
            log_value(0x0009e9eau, *(volatile uint32_t *)0x00087bf0u);
        return -1;
    }

    result = read_slot_image();
    if (result != 0) {
        if (*log_level > 0)
            log_value(0x0009ea0au, slot_flash_address);
        return -1;
    }

    if (operation == 2) {
        memset_bytes(slot_image + slot_number * 0x200u, 0xff, 0x200);
    } else {
        uint8_t *record = slot_image + slot_number * 0x200u;
        int header_changed = 0;

        if (record[0] != 0xaa) {
            record[0] = 0xaa;
            memset_bytes(record + 1, 0, 0x29);
            copy_default_header(record + 1, default_record(slot_number) + 4);
            memset_bytes(record + 0x2a, 0, 0x119);
            memcpy(record + 0x2a, default_record(slot_number) + 0x2d,
                         0x119);
        } else {
            if (FUN_00086be4(record + 1, default_record(slot_number) + 4,
                             0x29) != 0) {
                memset_bytes(record + 1, 0, 0x29);
                copy_default_header(record + 1,
                                    default_record(slot_number) + 4);
                header_changed = 1;
            }
            if (FUN_00086be4(record + 0x2a,
                             default_record(slot_number) + 0x2d,
                             0x119) != 0) {
                memset_bytes(record + 0x2a, 0, 0x119);
                memcpy(record + 0x2a,
                             default_record(slot_number) + 0x2d, 0x119);
            } else if (!header_changed) {
                if (*log_level > 2)
                    log_fixed(0x0009efafu);
                return 0;
            }
        }
    }

    if (operation == 1)
        reset_touch_selection_state();
    result = flush_slot_image();
    if (result != 0) {
        if (*log_level > 0)
            log_value(result == -1 ? 0x0009ebc6u : 0x0009eba7u,
                      (uint32_t)result);
        return result;
    }

    if (*log_level > 2)
        log_value(operation == 1 ? 0x0009ef8eu : 0x0009f010u,
                  slot_number);
    return 0;
}
