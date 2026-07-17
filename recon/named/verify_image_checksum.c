/* readable reconstruction; identity: FUN_000302cc @ 0x000302cc
 * public-name: verify_image_checksum
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   verify_image_checksum                    <= FUN_000302cc @ 0x000302cc
 */
/* Reconstructed FUN_000302cc @ 0x302cc  (parity: 300/300 trials, PROVEN) */

int verify_image_checksum(void)
{
  unsigned char *pbVar1;
  int iVar2;
  int iVar3;

  iVar2 = 0;
  iVar3 = 4;
  do {
    pbVar1 = (unsigned char *)(0x000a49a5UL + iVar3);
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + (unsigned int)*(volatile unsigned char*)pbVar1;
  } while (iVar3 != 0x1be4);
  iVar2 = iVar2 - 0x0009244d;
  if (iVar2 != 0) {
    iVar2 = -1;
  }
  return iVar2;
}
