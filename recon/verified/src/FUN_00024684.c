/* Reconstructed FUN_00024684 @ 0x24684. */
#include <stdint.h>

extern int FUN_00072240(void *queue, void *request, uint32_t timeout,
                        uint32_t flags);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0008638c(const void *object);
extern void FUN_00086c78(void *destination, int value, uint32_t length);
extern int FUN_00086be4(const void *left, const void *right, uint32_t length);
extern void FUN_00086c04(void *destination, const void *source, uint32_t length);
extern uint8_t *FUN_000167a8(void);
extern void FUN_00037098(void);

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
    return (struct flash_runtime *)(FUN_000167a8() + 0x1000);
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
        FUN_00019c70(format, 0x0009f050u);
}

static inline __attribute__((always_inline)) void log_value(uint32_t format,
                                                            uint32_t value)
{
    if (*deferred_logger == 0)
        DEBUG_PRINT(format, 0x0009f050u, value);
    else
        FUN_00019c70(format, 0x0009f050u, value);
}

static inline __attribute__((always_inline)) int read_slot_image(void)
{
    struct flash_runtime *ops;
    flash_read_fn read;

    FUN_00086c78(slot_image, 0, 0x800);
    ops = runtime_ops();
    read = ops->read;
    return read(FUN_000167a8(), slot_flash_address, slot_image, 0x800);
}

static inline __attribute__((always_inline)) int flush_slot_image(void)
{
    struct flash_runtime *ops;
    flash_erase_fn erase;
    flash_write_fn write;
    int result;

    ops = runtime_ops();
    erase = ops->erase;
    result = erase(FUN_000167a8(), slot_flash_address, 0x1000);
    if (result != 0)
        return result;

    ops = runtime_ops();
    write = ops->write;
    return write(FUN_000167a8(), slot_flash_address, slot_image, 0x800);
}

int FUN_00024684(uint32_t operation, uint32_t slot, uint32_t value)
{
    struct slot_request request = { operation, slot, value };
    uint8_t slot_number;
    int result;

    result = FUN_00072240((void *)0x20003960u, &request, 0, 0);
    if (result != 0) {
        if (*log_level < 1)
            return -1;
        if (*deferred_logger == 0)
            DEBUG_PRINT(0x0009ef15u, 0x0009f032u);
        else
            FUN_00019c70(0x0009ef15u, 0x0009f032u);
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
        FUN_00037098();

    if (FUN_0008638c((const void *)0x00087bf0u) == 0) {
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
        FUN_00086c78(slot_image + slot_number * 0x200u, 0xff, 0x200);
    } else {
        uint8_t *record = slot_image + slot_number * 0x200u;
        int header_changed = 0;

        if (record[0] != 0xaa) {
            record[0] = 0xaa;
            FUN_00086c78(record + 1, 0, 0x29);
            copy_default_header(record + 1, default_record(slot_number) + 4);
            FUN_00086c78(record + 0x2a, 0, 0x119);
            FUN_00086c04(record + 0x2a, default_record(slot_number) + 0x2d,
                         0x119);
        } else {
            if (FUN_00086be4(record + 1, default_record(slot_number) + 4,
                             0x29) != 0) {
                FUN_00086c78(record + 1, 0, 0x29);
                copy_default_header(record + 1,
                                    default_record(slot_number) + 4);
                header_changed = 1;
            }
            if (FUN_00086be4(record + 0x2a,
                             default_record(slot_number) + 0x2d,
                             0x119) != 0) {
                FUN_00086c78(record + 0x2a, 0, 0x119);
                FUN_00086c04(record + 0x2a,
                             default_record(slot_number) + 0x2d, 0x119);
            } else if (!header_changed) {
                if (*log_level > 2)
                    log_fixed(0x0009efafu);
                return 0;
            }
        }
    }

    if (operation == 1)
        FUN_00037098();
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
