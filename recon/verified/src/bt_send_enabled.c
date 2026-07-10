/* Reconstructed bt_send_enabled @ 0x17e3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, unsigned int, int);
extern void FUN_00019c70(void);

void bt_send_enabled(int param_1)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9a143UL, 0x9a2cdUL, param_1);
        } else {
            FUN_00019c70();
        }
    }
    int *p = *(int* volatile*)0x20006a30UL;
    *(volatile unsigned char*)((char*)p + 0x366) = (param_1 == 0);
}

