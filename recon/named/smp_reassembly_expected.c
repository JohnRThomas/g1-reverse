/* readable reconstruction; identity: FUN_00080b32 @ 0x00080b32
 * public-name: smp_reassembly_expected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_reassembly_expected                  <= FUN_00080b32 @ 0x00080b32
 */
/* Reconstructed FUN_00080b32 @ 0x80b32  (parity: 300/300 trials, PROVEN) */

unsigned int smp_reassembly_expected(unsigned char *param_1) {
  if (*(unsigned int*)(param_1 + 0x40) != 0) {
    return (unsigned int)*(unsigned short*)(param_1 + 0x44);
  }
  return 0xffffffea;
}
