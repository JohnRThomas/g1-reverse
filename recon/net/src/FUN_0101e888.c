/* net-core FUN_0101e888 @ 0x101e888  (parity 300 trials PROVEN) */

extern void FUN_0101e828(void);
void FUN_0101e888(void)
{
    volatile unsigned int * const p = (volatile unsigned int * const)0x21000eac;
    p[2] = 0xea6;
    p[3] = 0x1d4c;
    FUN_0101e828();
}

