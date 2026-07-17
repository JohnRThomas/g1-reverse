/* readable reconstruction; identity: FUN_0003cebc @ 0x0003cebc
 * public-name: not_disturb_disable_pending
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_even_ai_mic_icon_visible               @ 0x2001b9ab
 */
/* Reconstructed ext3cebc @ 0x3cebc.
 * Readable identity: not_disturb_disable_pending.
 * Exact standalone extent: 0x72 bytes; 0x3cf2e is alignment.
 */

#include <stdint.h>

extern uint8_t *get_device_info(void);
extern int not_disturb_sync_data(const uint8_t *value, uint32_t length);
extern void update_not_disturb_settings(void);
extern void update_persist_task_status(void *device, uint32_t kind,
                                       uint32_t state);

int not_disturb_disable_pending(uint8_t value)
{
    uint8_t *device = get_device_info();
    uint8_t *state = *(uint8_t **)(device + 0x1010);
    int result;

    if (state[1] == 0U) {
        return 0;
    }
    result = not_disturb_sync_data(&value, 1U);
    if (result != 0) {
        return result;
    }
    device = get_device_info();
    state = *(uint8_t **)(device + 0x1010);
    state[1] = 0U;
    device = get_device_info();
    if (device[0] != 1U) {
        return 0;
    }

    update_not_disturb_settings();
    *(volatile uint8_t *)0x2001b9abUL = value;
    device = get_device_info();
    device[0xcd] = *(volatile uint8_t *)0x2001b9abUL;
    device = get_device_info();
    state = *(uint8_t **)(device + 0x1010);
    state[0] = 1U;
    device = get_device_info();
    update_persist_task_status(device, 7U, 2U);
    return 0;
}
