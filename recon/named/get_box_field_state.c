/* readable reconstruction; identity: FUN_00025364 @ 0x00025364
 * public-name: get_box_field_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_box_field_state                      <= FUN_00025364 @ 0x00025364
 * address symbols (name @ address):
 *   g_box_field_timer                        @ 0x20007a24
 */
/* Reconstructed FUN_00025364 @ 0x25364  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
unsigned int get_box_field_state(void)
{
  unsigned int uVar2;
  if (*(volatile unsigned int *)0x20007a24UL <= 0x13ec) {
    uVar2 = 2;
  } else {
    int iVar1 = get_device_info();
    if (*(volatile unsigned char *)(iVar1 + 0xfc0) < 100) {
      uVar2 = 0;
    } else {
      uVar2 = 1;
    }
  }
  return uVar2;
}
