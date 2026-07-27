/* readable reconstruction; identity: FUN_0002efe4 @ 0x0002efe4
 * public-name: set_box_link_state_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   set_box_link_state_flag                  <= FUN_0002efe4 @ 0x0002efe4
 * address symbols (name @ address):
 *   g_low_battery_sync_flag                  @ 0x2000302f
 */
/* Reconstructed FUN_0002efe4 @ 0x2efe4  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);

unsigned int set_box_link_state_flag(int param_1)
{
  unsigned char *pcVar1;

  pcVar1 = (unsigned char *)get_device_info();
  if (*pcVar1 == 1) {
    if (param_1 == 0) {
      *(volatile unsigned char*)0x2000302fUL = 0;
    }
    else {
      *(volatile unsigned char*)0x2000302fUL = 2;
    }
  }
  return 0;
}
