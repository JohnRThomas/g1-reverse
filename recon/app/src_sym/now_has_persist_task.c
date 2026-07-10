/* Reconstructed now_has_persist_task @ 0x2be64  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007cdf8(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2)
{
    volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20018d9cUL;
    while (*pcVar1 != 0) {
        FUN_0007cdf8();
    }
    int *p = *(int**)(param_1 + 0x1054);
    unsigned int uVar3 = *((unsigned char*)p + 4);
    unsigned char uVar2 = 0;
    if (uVar3 > 1) {
        if (*(volatile int*)0x2000230cUL > 3) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}

