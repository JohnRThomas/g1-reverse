/* readable reconstruction; identity: FUN_000809f6 @ 0x000809f6
 * public-name: img_mgmt_slot_in_use
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_slot_to_image                   <= FUN_00051c68 @ 0x00051c68
 *   img_mgmt_get_next_boot_slot              <= FUN_000809b0 @ 0x000809b0
 *   img_mgmt_slot_in_use                     <= FUN_000809f6 @ 0x000809f6
 *   img_mgmt_active_slot                     <= FUN_00080a46 @ 0x00080a46
 */
/* Reconstructed FUN_000809f6 @ 0x809f6  (parity: 300/300 trials, PROVEN) */

extern unsigned int img_mgmt_slot_to_image(void);
extern unsigned int img_mgmt_active_slot(int a);
extern unsigned int img_mgmt_get_next_boot_slot(int a, void *b, unsigned int c, unsigned int d, unsigned int e);

int img_mgmt_slot_in_use(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  unsigned int uVar2;
  int bVar3;
  unsigned int uVar4;
  unsigned int uStack_14;
  unsigned char byte3;

  uVar1 = param_1;
  uVar4 = param_1;
  uStack_14 = param_2;
  if (3 < param_1) {
    uVar1 = img_mgmt_slot_to_image();
  }
  uVar2 = img_mgmt_active_slot((int)uVar1 >> 1);
  uStack_14 = uStack_14 & 0xffffff;
  uVar1 = img_mgmt_get_next_boot_slot((int)uVar1 >> 1, (char*)&uStack_14 + 3, param_3, 0, uVar4);
  byte3 = ((unsigned char*)&uStack_14)[3];
  if (((uVar1 == param_1) && (unsigned char)(byte3 - 1) < 2) ||
      ((uVar1 != uVar2) && (byte3 == 0))) {
    bVar3 = 1;
  } else {
    bVar3 = (uVar2 == param_1);
  }
  return bVar3;
}
