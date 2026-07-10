/* Reconstructed flash_ops_thread @ 0x23480  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern int FUN_0002f758(void);
extern void FUN_0002f94c(void);
extern int FUN_00024678(void);
extern void FUN_00024684(void);
extern int FUN_00023ef8(void);
extern void FUN_00023f04(void);
extern void FUN_00072908(void);

void flash_ops_thread(void)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    do {
        FUN_00072908();
        while (FUN_0002f758() != 0) {
            FUN_0002f94c();
        }
        while (FUN_00024678() != 0) {
            FUN_00024684();
        }
        while (FUN_00023ef8() != 0) {
            FUN_00023f04();
        }
    } while (1);
}

