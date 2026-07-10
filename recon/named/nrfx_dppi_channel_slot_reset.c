/* named: nrfx_dppi_channel_slot_reset */
/* Reconstructed nrfx_dppi_channel_slot_reset @ 0x67f1c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int a,unsigned int b);
extern void printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);

void nrfx_dppi_channel_slot_reset(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char idx = *(volatile unsigned char*)((char*)param_1+4);
    volatile unsigned char *tbl = (volatile unsigned char*)0x2000b41cUL;
    int *basePtr;
    int idxVal;
    if (*(volatile char*)(tbl+idx*8) != 2) {
        unsigned long long r;
        printk(0x00099cbdUL,0x000f7a3fUL,0x000f79c8UL,0xb8);
        r = assert_post_action(0x000f79c8UL,0xb8);
        basePtr = (int*)(unsigned int)(r & 0xffffffffUL);
        idxVal = (int)(unsigned int)(r >> 32);
    } else {
        basePtr = param_1;
        idxVal = param_2;
    }
    {
        int base = *(volatile int*)basePtr;
        *(volatile unsigned int*)(base + (idxVal+0x180)*4) = 0x6e524635UL;
    }
}

