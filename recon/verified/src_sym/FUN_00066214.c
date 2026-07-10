/* Reconstructed FUN_00066214 @ 0x66214  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void assert_post_action(unsigned int a0, unsigned int a1);

unsigned int FUN_00066214(void)
{
    unsigned int iVar1 = 0x2000b330UL;
    unsigned int uVar2;

    if (*(volatile unsigned char*)(0x2000b330UL + 0x10) != 0) {
        if (*(volatile unsigned char*)(0x2000b330UL + 0x11) == 0) {
            *(volatile unsigned char*)(0x2000b330UL + 0x11) = 2;
            *(volatile unsigned char*)(iVar1 + 0x14) = 1;
            *(volatile unsigned int*)(0xe000e100UL + 0x104) = 0x40;
            uVar2 = 0x0bad0000UL;
        } else {
            if (*(volatile unsigned char*)(0x2000b330UL + 0x11) != 1) {
                uVar2 = 0x0bad000bUL;
            } else {
                uVar2 = 0x0bad0000UL;
            }
        }
        return uVar2;
    }
    printk(0x00099cbdUL, 0x000f6d26UL, 0x000f6cebUL, 0xdd);
    assert_post_action(0x000f6cebUL, 0xdd);
    return 0;
}

