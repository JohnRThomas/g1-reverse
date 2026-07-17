/* readable reconstruction; identity: FUN_00084e9a @ 0x00084e9a
 * public-name: hex4_to_uint
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hex4_to_uint                             <= FUN_00084e9a @ 0x00084e9a
 */
/* Reconstructed FUN_00084e9a @ 0x84e9a  (parity: 300/300 trials, PROVEN) */

int hex4_to_uint(unsigned char *param_1)
{
  int iVar1 = 0;
  int iVar2 = 0;
  unsigned int uVar3;
  while (1) {
    uVar3 = param_1[iVar1];
    if (uVar3 - 0x30 < 10) {
      iVar2 = iVar2 - 0x30;
    } else if (uVar3 - 0x41 < 6) {
      iVar2 = iVar2 - 0x37;
    } else if (uVar3 - 0x61 <= 5) {
      iVar2 = iVar2 - 0x57;
    } else {
      return 0;
    }
    if (iVar1 == 3) break;
    iVar2 = (uVar3 + iVar2) * 0x10;
    iVar1 = iVar1 + 1;
  }
  return uVar3 + iVar2;
}
