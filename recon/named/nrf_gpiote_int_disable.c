/* named: nrf_gpiote_int_disable */
/* Reconstructed nrf_gpiote_int_disable @ 0x65e4c  (parity: 300/300 trials, PROVEN) */

extern unsigned int assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void nrf_gpiote_int_disable(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = param_1;
    if (*(volatile unsigned char*)0x2000b328UL != 1) {
        printk(0x00099cbdUL, 0x000f6c09UL, 0x000f6bc5UL, 0x72, param_4);
        r0 = assert_post_action(0x000f6bc5UL, 0x72);
    }
    *(volatile int*)0x5002a308UL = 1 << (r0 & 0xff);
}

