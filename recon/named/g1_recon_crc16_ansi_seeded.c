/* readable reconstruction; identity: FUN_0007da4a @ 0x0007da4a
 * public-name: g1_recon_crc16_ansi_seeded
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_crc16_configurable              <= FUN_0007d9c0 @ 0x0007d9c0
 *   g1_recon_crc16_ansi_seeded               <= FUN_0007da4a @ 0x0007da4a
 */
/* Reconstructed FUN_0007da4a @ 0x7da4a  (parity: 300/300 trials, PROVEN) */

extern unsigned int g1_recon_crc16_configurable(unsigned int seed, unsigned int polynomial,
        unsigned int xor_out, int reflect_input, char reflect_output,
        const unsigned char *src, int len);

unsigned int g1_recon_crc16_ansi_seeded(unsigned int seed, const unsigned char *src, int len)
{
  unsigned int uVar1;
  if (src == 0 || len < 1) {
    uVar1 = 0;
  } else {
    uVar1 = g1_recon_crc16_configurable(seed, 0x8005, 0xffff, 1, 1, src, len);
  }
  return uVar1;
}
