/* Reconstructed check_bonded_addr @ 0x183e4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00018334(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

void check_bonded_addr(unsigned int param_1)
{
    FUN_00018334();
    unsigned int *cnt = (unsigned int*)0x20007514UL /* device_info+0xb18 (gap near gap_0B0D+0x17, name best-effort) */;
    *cnt = *cnt + 1;
    unsigned int ptr = *(volatile unsigned int*)0x20006ab8UL /* device_info+0xbc (gap near gap_0003+0xb9, name best-effort) */;
    *(volatile unsigned char*)(ptr + 0x367) = 0;
    if (*(volatile int*)0x2000230cUL /* unknown global 0x2000230c */ > 0) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
}

