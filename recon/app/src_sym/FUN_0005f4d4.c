/* Reconstructed FUN_0005f4d4 @ 0x5f4d4  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned long, ...);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

static void merge_tail(unsigned int r0, unsigned int r1)
{
    unsigned short chk = *(volatile unsigned short*)((char*)r0 + 4);
    if (chk == 0) {
        unsigned int val8 = *(volatile unsigned int*)((char*)r0 + 8);
        unsigned int result = val8 + r1;
        *(volatile unsigned int*)r0 = result;
    }
}

void FUN_0005f4d4(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 == (int*)0) {
        printk(0x99cbdUL, 0xf45beUL, 0xf543aUL, 0x2bUL);
        unsigned long long rv = assert_post_action(0xf543aUL, 0x2bUL);
        merge_tail((unsigned int)rv, (unsigned int)(rv >> 32));
        return;
    }
    short shortval = *(volatile short*)((char*)param_1 + 4);
    if (shortval == 0) {
        *param_1 = param_1[2] + param_2;
        return;
    }
    printk(0x99cbdUL, 0xf5465UL, 0xf543aUL, 0x2cUL);
    unsigned long long rv = assert_post_action(0xf543aUL, 0x2cUL);
    merge_tail((unsigned int)rv, (unsigned int)(rv >> 32));
}

