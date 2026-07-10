/* net-core FUN_01033ee4 @ 0x1033ee4  (parity 300 trials PROVEN) */

void FUN_01033ee4(void)
{
    unsigned int v;
    v = 1u << *(volatile unsigned char*)0x2100645b;
    v |= 1u << *(volatile unsigned char*)0x2100645f;
    v |= 1u << *(volatile unsigned char*)0x2100645d;
    v |= 1u << *(volatile unsigned char*)0x2100645c;
    v |= 1u << *(volatile unsigned char*)0x21006460;
    v |= 1;
    *(volatile unsigned int*)(0x4100f000 + 0x508) = v;
}

