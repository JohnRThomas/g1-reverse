/* readable reconstruction; identity: FUN_0003707c @ 0x0003707c
 * public-name: handle_touch_single_click
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_startup_default_language   <= FUN_0001672c @ 0x0001672c
 * address symbols (name @ address):
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_widget0_index_raw                      @ 0x2001b816
 */
/* Reconstructed handle_touch_single_click @ 0x3707c  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;

extern void set_dashboard_startup_default_language(unsigned char);

int handle_touch_single_click(unsigned int param_1)
{
    unsigned int action = param_1 & 0xffu;
    *(volatile u8 *)(0x20004950UL + 1) = action;
    *(volatile u8 *)0x2001b816UL = action;
    set_dashboard_startup_default_language(action);
    return 0;
}
