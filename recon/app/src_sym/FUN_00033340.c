/* Reconstructed FUN_00033340 @ 0x33340  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00033088(unsigned int a);
extern int process_pt_data(void);
extern unsigned int FUN_000332dc(void);
extern void FUN_00074844(unsigned int a, unsigned int b);

int FUN_00033340(void)
{
    int iVar1;

    iVar1 = FUN_000332dc();
    if (iVar1 == 0) {
        iVar1 = FUN_00033088(0x00087bc0UL);
        if (iVar1 == 0) {
            iVar1 = process_pt_data();
            if (iVar1 != 0) {
                iVar1 = -3;
            }
        } else {
            DEBUG_PRINT(0x000a7907UL);
            FUN_00074844(0x4000, 0);
            iVar1 = -2;
        }
    } else {
        iVar1 = -1;
    }
    return iVar1;
}

