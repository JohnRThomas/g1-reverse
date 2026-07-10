/* net-core FUN_010344a8 @ 0x10344a8  (parity 300 trials PROVEN) */

unsigned int FUN_010344a8(unsigned int param_1)
{
    volatile unsigned char * const p = (volatile unsigned char * const)0x103e6e2;
    unsigned int r3 = p[param_1 >> 5];
    return ((param_1 & 0x1f) + r3) & 0xff;
}

