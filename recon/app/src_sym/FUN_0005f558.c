/* Reconstructed FUN_0005f558 @ 0x5f558  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void FUN_0005f558(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned short ushort_val = *(unsigned short*)((char*)param_1 + 4);
    if (ushort_val < param_2) {
        printk(0x99cbdU, 0xf5474U, 0xf543aU, 0x18dU, param_4);
        unsigned long long rv = assert_post_action(0xf543aU, 0x18dU);
        unsigned int r0v = (unsigned int)rv;
        unsigned int r1v = (unsigned int)(rv >> 32);
        unsigned int r2v = 0xf543aU - r1v;
        *(volatile unsigned short*)(r0v + 4) = (unsigned short)r2v;
        unsigned int memv = *(volatile unsigned int*)r0v;
        unsigned int finalv = memv + r1v;
        *(volatile unsigned int*)0x18dUL = finalv;
        return;
    }
    *(unsigned short*)((char*)param_1 + 4) = (unsigned short)(ushort_val - param_2);
    *param_1 = *param_1 + param_2;
    return;
}

