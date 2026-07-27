/* Reconstructed FUN_00018300 @ 0x18300  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00072880(int);
extern void change_work_mode_to(int);
void FUN_00018300(int param_1, unsigned int param_2)
{
    DEBUG_PRINT(0x0009a436);
    if (99 < param_2) {
        FUN_00072880(*(volatile int*)0x20006ab8UL + 0x230);
        if (param_2 == 0x1f2) {
            change_work_mode_to(1);
            return;
        }
    }
}

