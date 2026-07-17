/* Reconstructed FUN_0007d696 @ 0x7d696  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007d82e(unsigned int, const void *, unsigned int);

void FUN_0007d696(unsigned int value)
{
    unsigned short big_endian =
        (unsigned short)((value << 8) | ((value >> 8) & 0xffu));
    FUN_0007d82e(0x36, &big_endian, sizeof(big_endian));
}
