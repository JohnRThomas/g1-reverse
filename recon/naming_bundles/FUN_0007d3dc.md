### FUN_0007d3dc  @ 0x0007d3dc  (size=76)

callers (3): ui_even_ai_task, ui_set_imu_pitch_task, ui_refalsh_warp
callees (2): debug_print, log_message
strings: "gui_utf_adv_draw_configure"

```c
/* readable reconstruction; identity: FUN_0007d3dc @ 0x0007d3dc
 * public-name: FUN_0007d3dc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_mode_globals_configure           <= FUN_0004372c @ 0x0004372c
 */
/* Full reconstruction FUN_0007d3dc @ 0x7d3dc (exact extent 18 bytes). */

extern unsigned int display_mode_globals_configure(unsigned int mode);

unsigned int FUN_0007d3dc(void)
{
    return display_mode_globals_configure(8);
}
```