/* readable reconstruction; identity: FUN_00043324 @ 0x00043324
 * public-name: gui_clear_icon_box_40
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gui_clear_icon_box_40                    <= FUN_00043324 @ 0x00043324
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 * address symbols (name @ address):
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_00043324 @ 0x43324  (parity: 300/300 trials, PROVEN) */

extern void clean_fb_data(int a, int b, int c, int d, int e, int f, int g);
unsigned int gui_clear_icon_box_40(int param_1, int param_2, unsigned int param_3)
{
  clean_fb_data(*(volatile int *)0x2000a034UL, 0, param_1, param_2, param_1 + 0x28, param_2 + 0x28, param_3);
  return 0;
}
