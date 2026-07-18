/* readable reconstruction; identity: FUN_00051d8c @ 0x00051d8c
 * public-name: img_mgmt_set_next_boot_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   img_mgmt_flash_area_id                   <= FUN_0005169c @ 0x0005169c
 *   img_mgmt_slot_to_image                   <= FUN_00051c68 @ 0x00051c68
 *   img_mgmt_set_next_boot_slot              <= FUN_00051d8c @ 0x00051d8c
 *   boot_set_next                            <= FUN_000641e4 @ 0x000641e4
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   img_mgmt_get_next_boot_slot              <= FUN_000809b0 @ 0x000809b0
 * address symbols (name @ address):
 *   rodata_88208                             @ 0x00088208
 *   rodata_f2772                             @ 0x000f2772
 */
/* Reconstructed FUN_00051d8c @ 0x51d8c. */
#include <stdint.h>

extern void FUN_0004d944(uint32_t channel, uint32_t flags,
                         const void *record, int context);
extern int flash_area_open(unsigned int selector, uint32_t *handle);
extern unsigned int img_mgmt_flash_area_id(unsigned int request);
extern unsigned int img_mgmt_slot_to_image(void);
extern int boot_set_next(uint32_t handle, unsigned int is_selected, int mode);
extern void nullsub_3(uint32_t handle);
extern unsigned int img_mgmt_get_next_boot_slot(int group, uint8_t *state);
extern unsigned int FUN_00080a46(int group);
extern int FUN_00080a4a(void);

struct failure_record {
    uint32_t count;
    uint32_t format;
    int error;
    uint32_t requested;
    uint32_t selected;
    int mode;
};

int img_mgmt_set_next_boot_slot(unsigned int request, int mode)
{
    unsigned int selected = request;
    if (request > 3u)
        selected = img_mgmt_slot_to_image();

    int group = (int)selected >> 1;
    unsigned int primary = FUN_00080a46(group);
    uint8_t state = 0;
    unsigned int secondary = img_mgmt_get_next_boot_slot(group, &state);

    if (mode == 0) {
        if (primary == request)
            return 0x21;
        if (state == 1)
            return secondary == request ? 0 : 0x1c;
        if ((state == 0 && secondary == request) || state == 2)
            return 0x1c;
    } else {
        if (FUN_00080a4a() == group) {
            if (state == 1)
                return 0x1c;
            if (state == 0) {
                if (secondary == request)
                    return 0;
                if (primary == request)
                    return 0x1c;
            } else if (state == 2 && secondary == request) {
                return 0;
            }
        } else {
            if (primary == request)
                return 0x20;
            if (state == 1)
                return 0x1c;
            if ((state == 0 || state == 2) && secondary == request)
                return 0;
        }
    }

    uint32_t handle;
    unsigned int selector = img_mgmt_flash_area_id(request) & 0xffu;
    if (flash_area_open(selector, &handle) != 0)
        return 10;

    int status = boot_set_next(handle, primary == request, mode);
    if (status != 0) {
        struct failure_record failure = {
            6, 0x000f2772, status, request, primary, mode
        };
        FUN_0004d944(0x00088208, 0x3040, &failure, 0);
        if (status == 1)
            status = 0x0c;
        else if (status == 4)
            status = 0x1d;
        else if (status == 3)
            status = 0x17;
        else
            status = 1;
    }
    nullsub_3(handle);
    return status;
}
