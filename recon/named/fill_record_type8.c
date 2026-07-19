/* readable reconstruction; identity: FUN_000250c4 @ 0x000250c4
 * public-name: fill_record_type8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fill_record_type8                        <= FUN_000250c4 @ 0x000250c4
 * address symbols (name @ address):
 *   rodata_24ad9                             @ 0x00024ad9
 *   rodata_25059                             @ 0x00025059
 *   rodata_7c39d                             @ 0x0007c39d
 */
/* Reconstructed FUN_000250c4 @ 0x250c4  (parity: 300/300 trials, PROVEN) */

unsigned int fill_record_type8(unsigned char *param_1, unsigned int *param_2)
{
  if (param_1 != 0 && param_2 != 0) {
    *param_1 = 8;
    *(unsigned int*)(param_1+4) = 0x7c39d;
    *(unsigned int*)(param_1+8) = 0x24ad9;
    *(unsigned int*)(param_1+0xc) = 0x25059;
    *(unsigned int*)(param_1+0x10) = param_2[0];
    *(unsigned int*)(param_1+0x14) = param_2[1];
    param_1[0x18] = *((unsigned char*)param_2+8);
    return 0;
  }
  return 7;
}
