/* readable reconstruction; identity: FUN_0007d82e @ 0x0007d82e
 * public-name: projector_send_command
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_spi_write_chunked              <= FUN_0007d7b6 @ 0x0007d7b6
 *   projector_send_command                   <= FUN_0007d82e @ 0x0007d82e
 */
/* Reconstructed FUN_0007d82e @ 0x7d82e  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c1e(void *, const void *, unsigned int, unsigned int);
extern void projector_spi_write_chunked(const void *, unsigned int);

void projector_send_command(unsigned int opcode, const void *payload,
                  unsigned int payload_length)
{
  unsigned char command[8];

  command[0] = (unsigned char)opcode;
  FUN_00086c1e(command + 1, payload, payload_length, 5);
  projector_spi_write_chunked(command, payload_length + 1);
}
