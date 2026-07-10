/* named: net_buf_frag_add */
/* Reconstructed net_buf_frag_add @ 0x5f390  (parity: 300/300 trials, PROVEN) */

extern int net_buf_ref(int a, int b, unsigned int c, unsigned int d);
extern unsigned int net_buf_frag_last(void);
extern void net_buf_frag_insert(unsigned int a, int b);
extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

int net_buf_frag_add(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;

    if (param_2 == 0) {
        printk(0x00099cbdUL, 0x000f542dUL, 0x000f539aUL, 0x24d);
        assert_post_action(0x000f539aUL, 0x24d);
    }
    if (param_1 == 0) {
        iVar1 = net_buf_ref(param_2, param_2, param_3, param_4);
        return iVar1;
    }
    uVar2 = net_buf_frag_last();
    net_buf_frag_insert(uVar2, param_2);
    return param_1;
}

