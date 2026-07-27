/* Reconstructed handle_stocks_action @ 0x371e8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int handle_stocks_action(unsigned int param_1, unsigned int param_2,
                                  unsigned int param_3, unsigned int param_4)
{
    unsigned int action = param_1 & 0xffu;
    *(volatile unsigned char*)(0x20004950UL+5) = (unsigned char)action;
    *(volatile unsigned char*)0x2001b814UL = (unsigned char)action;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a8ff3UL, 0x000a959eUL, 0x000a959eUL,
                        action, param_4);
        } else {
            FUN_00019c70(0x000a8ff3UL, 0x000a959eUL, 0x000a959eUL,
                        action, param_4);
        }
    }
    return 0;
}
