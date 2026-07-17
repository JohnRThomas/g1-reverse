/* readable reconstruction; identity: FUN_000809b0 @ 0x000809b0
 * public-name: img_mgmt_get_next_boot_slot
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed img_mgmt_get_next_boot_slot @ 0x809b0 (raw FUN_000809b0).
 * Reviewed executable extent: 0x46 bytes, ending at the next entry 0x809f6. */
#include <stdint.h>

enum img_mgmt_next_boot_type {
    NEXT_BOOT_TYPE_NORMAL = 0,
    NEXT_BOOT_TYPE_TEST = 1,
    NEXT_BOOT_TYPE_REVERT = 2,
};

enum mcuboot_swap_type {
    BOOT_SWAP_TYPE_NONE = 1,
    BOOT_SWAP_TYPE_TEST = 2,
    BOOT_SWAP_TYPE_PERM = 3,
    BOOT_SWAP_TYPE_REVERT = 4,
};

extern int img_mgmt_active_slot(int image) __asm__("FUN_00080a46");
extern int mcuboot_swap_type_multi(int image) __asm__("FUN_000836d4");
extern void img_mgmt_assert_valid_slot(void) __asm__("FUN_00051c38")
    __attribute__((noreturn));

int img_mgmt_get_next_boot_slot(int image,
                                enum img_mgmt_next_boot_type *type)
{
    int active_slot = img_mgmt_active_slot(image);
    int swap_type = mcuboot_swap_type_multi(image);
    int next_slot;
    enum img_mgmt_next_boot_type next_type = NEXT_BOOT_TYPE_NORMAL;

    if ((unsigned int)active_slot >= 4u) {
        img_mgmt_assert_valid_slot();
    }
    next_slot = active_slot ^ 1;

    switch (swap_type) {
    case BOOT_SWAP_TYPE_NONE:
        next_slot = active_slot;
        break;
    case BOOT_SWAP_TYPE_PERM:
        break;
    case BOOT_SWAP_TYPE_REVERT:
        next_type = NEXT_BOOT_TYPE_REVERT;
        break;
    case BOOT_SWAP_TYPE_TEST:
        next_type = NEXT_BOOT_TYPE_TEST;
        break;
    default:
        return -1;
    }

    if (type != 0) {
        *type = next_type;
    }
    return next_slot;
}
