/* Reconstructed jbd_panel_suspend @ 0x475f0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0007d82e(unsigned int,const void *,unsigned int);

unsigned int jbd_panel_suspend(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        unsigned int sink = *(volatile unsigned int*)0x20007554UL;
        if (sink == 0) {
            DEBUG_PRINT(0x000d73a1,0x000d7409,param_3,sink,param_1,param_2);
        } else {
            FUN_00019c70(0x000d73a1,0x000d7409,param_3,sink,param_1,param_2);
        }
    }
    const unsigned char command = 0xff;
    FUN_0007d82e(0xb9,&command,1);
    return 0;
}
