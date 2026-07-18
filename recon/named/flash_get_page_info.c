/* readable reconstruction; identity: FUN_00083a2c @ 0x00083a2c
 * public-name: flash_get_page_info
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed Zephyr flash_get_page_info helper @ 0x00083a2c.
 * Raw/address back-map: FUN_00083a2c / 0x00083a2c.
 */
#include <stdint.h>

struct device_raw {
    const char *name;
    const void *config;
    const void *api;
};

struct flash_pages_layout_raw {
    uint32_t pages_count;
    uint32_t pages_size;
};

struct flash_pages_info_raw {
    uint32_t start_offset;
    uint32_t size;
    uint32_t index;
};

struct flash_driver_api_raw {
    uint8_t reserved[0x10];
    void (*page_layout)(const struct device_raw *,
                        const struct flash_pages_layout_raw **, uint32_t *);
};

int flash_get_page_info(const struct device_raw *device, uint32_t offset,
                        uint32_t index, struct flash_pages_info_raw *info)
{
    const struct flash_driver_api_raw *api =
        (const struct flash_driver_api_raw *)device->api;
    const struct flash_pages_layout_raw *layout;
    uint32_t layout_count;

    info->start_offset = 0;
    info->index = 0;
    api->page_layout(device, &layout, &layout_count);

    while (layout_count-- != 0u) {
        info->size = layout->pages_size;
        uint32_t jump = offset == 0u
            ? index - info->index
            : (offset - info->start_offset) / info->size;
        if (jump > layout->pages_count) {
            jump = layout->pages_count;
        }
        info->start_offset += jump * info->size;
        info->index += jump;
        if (jump < layout->pages_count) {
            return 0;
        }
        layout++;
    }
    return -22;
}
