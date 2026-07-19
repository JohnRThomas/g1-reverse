/* readable reconstruction; identity: FUN_00025090 @ 0x00025090
 * public-name: event_record_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   event_record_init                        <= FUN_00025090 @ 0x00025090
 * address symbols (name @ address):
 *   rodata_24a41                             @ 0x00024a41
 *   rodata_25021                             @ 0x00025021
 *   rodata_7c38b                             @ 0x0007c38b
 */
/* Reconstructed FUN_00025090 @ 0x25090  (parity: 300/300 trials, PROVEN) */

unsigned int event_record_init(unsigned char *param_1, unsigned int *param_2)
{
  unsigned int uVar1 = 7;
  if (param_1 != 0 && param_2 != 0) {
    *param_1 = 7;
    uVar1 = 0;
    *(unsigned int *)(param_1 + 4) = 0x0007c38b;
    *(unsigned int *)(param_1 + 8) = 0x00024a41;
    *(unsigned int *)(param_1 + 0xc) = 0x00025021;
    *(unsigned int *)(param_1 + 0x10) = *param_2;
    *(unsigned int *)(param_1 + 0x14) = param_2[1];
    *(unsigned short *)(param_1 + 0x18) = *(unsigned short *)(param_2 + 2);
  }
  return uVar1;
}
