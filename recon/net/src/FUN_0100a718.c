/* net-core FUN_0100a718 @ 0x100a718  (parity 300 trials PROVEN) */

void FUN_0100a718(void)
{
    unsigned int base = 0x4100d000;
    *(volatile unsigned int*)(base+4) = 1;
    *(volatile unsigned int*)(base+0x308) = 0xffffffff;
    base += 0x1000;
    *(volatile unsigned int*)(base+8) = 1;
    *(volatile unsigned int*)(base+0x200) = 0;
    *(volatile unsigned int*)(base+0x308) = 0xffffffff;
    *(volatile unsigned int*)(base+0x500) = 0;
    *(volatile unsigned int*)(base+0x504) = 1;
    *(volatile unsigned int*)(base+8) = 1;
    *(volatile unsigned int*)(base+0x308) = 0xffffffff;
    *(volatile unsigned int*)(base+0x500) = 0;
    *(volatile unsigned int*)(base+0x504) = 1;
    base += 0x1000;
    *(volatile unsigned int*)(base+0x508) = 0x1ff8;
}

