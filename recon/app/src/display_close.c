/* Reconstructed display_close @ 0x497b0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void FUN_00019c70(void);
extern int FUN_000720d0(unsigned int a, void *b, int c, int d);
extern void FUN_00086c04(void *dst, void *src, unsigned int n);
extern void FUN_00086c78(void *dst, int val, int n);

unsigned int display_close(void *param_1, unsigned int param_2)
{
    unsigned char buf[24 + 4];
    int iVar1;

    FUN_00086c78(buf, 0, 0x18);
    if (param_2 < 0xb) {
        buf[0] = 3;
        if (param_1 != (void*)0) {
            FUN_00086c04(buf + 4, param_1, param_2);
            *(volatile unsigned short *)(buf + 2) = (unsigned short)param_2;
        }
        iVar1 = FUN_000720d0(0x200038c4U, buf, 0, 0);
        if (iVar1 == 0) {
            if (*(volatile int *)0x2000230cUL < 1) {
                return 0;
            }
            if (*(volatile int *)0x20007554UL != 0) {
                FUN_00019c70();
                return 0;
            }
            DEBUG_PRINT(0xf0044U, 0xf018cU);
            return 0;
        }
        DEBUG_PRINT(0xef058U, 0xf018cU);
    } else if (0 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0xef01cU, 0xf018cU);
        } else {
            FUN_00019c70();
        }
    }
    return 0xffffffff;
}

