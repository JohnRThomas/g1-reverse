/* Reconstructed handle_stocks_action @ 0x371e8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

unsigned int handle_stocks_action(unsigned char param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *(volatile unsigned char*)(0x20004950UL+5) = param_1;
    *(volatile unsigned char*)0x2001b814UL = param_1;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    return 0;
}

