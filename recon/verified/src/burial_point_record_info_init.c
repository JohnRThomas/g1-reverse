/* Reconstructed burial_point_record_info_init @ 0x4ab3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern int FUN_000167a8(void);
extern void FUN_00086c78(void);

void burial_point_record_info_init(void)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    int iVar1 = FUN_000167a8();
    (void)iVar1;
    FUN_00086c78();
    iVar1 = FUN_000167a8();
    (void)iVar1;
    FUN_00086c78();
}

