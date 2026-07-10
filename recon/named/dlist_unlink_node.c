/* named: dlist_unlink_node */
/* Reconstructed dlist_unlink_node @ 0x73cdc  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern unsigned long long assert_post_action(unsigned int a,unsigned int b);

void dlist_unlink_node(unsigned int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
    int *base;
    if ((unsigned int)param_2 == 0x20006720UL) {
        unsigned long long r;
        printk(0x00099cbdUL, 0x000f84d6UL, 0x000f82f4UL, 0x484);
        r = assert_post_action(0x000f82f4UL, 0x484);
        base = (int*)(unsigned int)(r >> 32);
    } else {
        base = param_2;
    }
    {
        int iVar2 = *(volatile int*)base;
        int *piVar1 = *(volatile int**)((char*)base + 4);
        *(volatile int*)piVar1 = iVar2;
        *(volatile int**)((unsigned int)iVar2 + 4) = piVar1;
        *(volatile int*)base = 0;
        *(volatile int*)((char*)base + 4) = 0;
    }
}

