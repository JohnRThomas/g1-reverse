/* readable reconstruction; identity: FUN_0007c842 @ 0x0007c842
 * public-name: box_field_state_to_display_code
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_box_field_state                      <= FUN_00025364 @ 0x00025364
 *   box_field_state_to_display_code          <= FUN_0007c842 @ 0x0007c842
 */
/* Reconstructed FUN_0007c842 @ 0x7c842  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_box_field_state(void);
void box_field_state_to_display_code(int param_1)
{
  int iVar1 = get_box_field_state();
  unsigned char uVar2;
  if (iVar1 == 1) { uVar2 = 4; }
  else if (iVar1 == 0) { uVar2 = 1; }
  else { uVar2 = 2; }
  *(volatile unsigned char *)(param_1 + 2) = uVar2;
}
