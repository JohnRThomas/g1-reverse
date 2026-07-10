/* net-core FUN_01024aa8 @ 0x1024aa8  (parity 300 trials PROVEN) */

void FUN_01024aa8(void)
{
    volatile unsigned int * const p = (volatile unsigned int * const)0x41005000;
    volatile unsigned char * const q = (volatile unsigned char * const)0x21001bf7;
    p[1] = 1;
    p[0x40] = 0;
    q[0] = 0;
}

