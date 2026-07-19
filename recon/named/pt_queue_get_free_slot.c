/* readable reconstruction; identity: FUN_00033bc4 @ 0x00033bc4
 * public-name: pt_queue_get_free_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pt_queue_get_free_slot                   <= FUN_00033bc4 @ 0x00033bc4
 */
/* Reconstructed FUN_00033bc4 @ 0x33bc4  (parity: 300/300 trials, PROVEN) */

unsigned int pt_queue_get_free_slot(void)
{
  unsigned int uVar1;
  uVar1 = (unsigned int)*(volatile unsigned char *)(0x20008dacUL + 0x118);
  if (uVar1 != 0) {
    if (*(volatile unsigned char *)(0x20008dacUL + 0x116) == 0) {
      uVar1 = 0;
      if (*(volatile unsigned char *)(0x20008dacUL + 0x115) < 4) {
        uVar1 = 0x20008dacUL + 0x108;
        *(volatile unsigned char *)(0x20008dacUL + 0x114) = 10;
        return uVar1;
      }
    } else {
      uVar1 = 0;
    }
  }
  return uVar1;
}
