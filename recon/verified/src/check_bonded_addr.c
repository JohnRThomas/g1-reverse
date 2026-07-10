/* Reconstructed check_bonded_addr @ 0x183e4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00018334(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

void check_bonded_addr(unsigned int param_1)
{
    FUN_00018334();
    unsigned int *cnt = (unsigned int*)0x20007514UL;
    *cnt = *cnt + 1;
    unsigned int ptr = *(volatile unsigned int*)0x20006ab8UL;
    *(volatile unsigned char*)(ptr + 0x367) = 0;
    if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
}

