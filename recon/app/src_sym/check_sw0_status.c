/* Reconstructed check_sw0_status @ 0x2a868  (parity: 300/300 trials, PROVEN) */

extern int FUN_00017e30(void);
extern void debug_print(void);
extern void FUN_00030c90(void);
extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);

void check_sw0_status(void)
{
    int iVar3 = FUN_00017e30();
    volatile int *piVar2 = (volatile int *)0x2000230cUL /* unknown global 0x2000230c */;
    volatile int *piVar1 = (volatile int *)0x20007af0UL /* device_info+0x10f4 (unnamed) */;

    if (iVar3 == 0) {
        if (*piVar2 > 1) {
            if (*(volatile int *)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
                DEBUG_PRINT(0xa18cdU, 0xa19afU);
            } else {
                debug_print();
            }
        }
        iVar3 = *piVar1 + 1;
        *piVar1 = iVar3;
        if (iVar3 > 3) {
            if (*piVar2 > 1) {
                if (*(volatile int *)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
                    DEBUG_PRINT(0xa18eaU, 0xa19afU);
                } else {
                    debug_print();
                }
            }
            FUN_00030c90();
            return;
        }
    } else {
        *piVar1 = 0;
    }
    return;
}

