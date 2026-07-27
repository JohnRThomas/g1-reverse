/* Reconstructed FUN_0007d82e @ 0x7d82e  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c1e(void *, const void *, unsigned int, unsigned int);
extern void FUN_0007d7b6(int, unsigned int);

void FUN_0007d82e(unsigned int opcode, const void *payload,
                  unsigned int payload_length)
{
  unsigned char command[8];

  command[0] = (unsigned char)opcode;
  FUN_00086c1e(command + 1, payload, payload_length, 5);
  FUN_0007d7b6(command, payload_length + 1);
}
