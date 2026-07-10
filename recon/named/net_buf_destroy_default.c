/* named: net_buf_destroy_default */
/* Reconstructed net_buf_destroy_default @ 0x5f200  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void net_pkt_skip(void);

void net_buf_destroy_default(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        printk(0x00099cbdUL, 0x000f5402UL, 0x000f539aUL, 0x1c7, param_4);
        uVar1 = 0x1c7;
    } else {
        if (param_2 != 0) {
            net_pkt_skip();
            return;
        }
        printk(0x00099cbdUL, 0x000f45beUL, 0x000f539aUL, 0x1c8, param_4);
        uVar1 = 0x1c8;
    }
    assert_post_action(0x000f539aUL, uVar1);
}

