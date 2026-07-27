/* Reconstructed pairing_failed @ 0x18444  (parity: 300/300 trials, PROVEN) */

extern void FUN_00018334(void);
extern unsigned int FUN_00081526(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void FUN_00056a68(void);

void pairing_failed(unsigned int param_1, unsigned int param_2)
{
    unsigned int uVar1 = FUN_00081526();
    (void)uVar1;
    FUN_00018334();
    DEBUG_PRINT();
    if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    FUN_00056a68();
}

