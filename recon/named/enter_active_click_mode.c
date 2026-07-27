/* readable reconstruction; identity: FUN_00028964 @ 0x00028964
 * public-name: enter_active_click_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   change_work_mode_to                      <= FUN_0001694c @ 0x0001694c
 *   enter_active_click_mode                  <= FUN_00028964 @ 0x00028964
 *   active_mode_shutdown                     <= FUN_0002bdf0 @ 0x0002bdf0
 *   projector_reflash_and_release            <= FUN_0007d874 @ 0x0007d874
 * address symbols (name @ address):
 *   g_suspend_pending_flag                   @ 0x20018d8b
 *   g_display_page_dirty_flag                @ 0x2001b811
 */
/* Reconstructed FUN_00028964 @ 0x28964
 * CFG_VERIFY_CALL_ARITIES=1,0,0,0,0,0,1
 * Readable identity: enter_active_click_mode.
 * Raw/address backmap: enter_active_click_mode <= FUN_00028964 @ 0x00028964.
 */

#include <stdint.h>

extern unsigned int change_work_mode_to(unsigned int);
extern int get_device_info(void);
extern void active_mode_shutdown(void);
extern void projector_reflash_and_release(uint32_t mode);

void enter_active_click_mode(void)
{
    volatile uint8_t *const pending_reset =
        (volatile uint8_t *)0x2001b811UL;
    volatile uint8_t *const click_mode_active =
        (volatile uint8_t *)0x20018d8bUL;
    uint8_t *device_state;

    if (*pending_reset != 0U) {
        *pending_reset = 0U;
    }

    change_work_mode_to(2U);
    (void)get_device_info();
    active_mode_shutdown();

    device_state = get_device_info();
    device_state[0xee4] = 2U;
    device_state = get_device_info();
    device_state[0x0d5] = 3U;
    device_state = get_device_info();
    projector_reflash_and_release(device_state[0x0d5]);

    *click_mode_active = 1U;
}
