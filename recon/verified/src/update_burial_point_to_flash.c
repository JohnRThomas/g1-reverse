/* Reconstructed update_burial_point_to_flash @ 0x23014  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void FUN_00019c70(unsigned int,unsigned int);
extern int FUN_000225b4(unsigned int a, void *b, unsigned int n);
extern int FUN_00022658(unsigned int a, void *b, unsigned int n);
extern int FUN_00086be4(void *a, void *b, unsigned int n);
extern void FUN_00086c78(void *dst, int val, int n);

unsigned int update_burial_point_to_flash(char *param_1)
{
    unsigned char buf[196];
    int iVar2;
    unsigned int format_string;

    FUN_00086c78(buf, 0, 0xc0);
    if (1 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x9e655U, 0x9e789U);
        } else {
            FUN_00019c70(0x9e655U, 0x9e789U);
        }
    }
    iVar2 = FUN_000225b4(0x135000U, buf, 0xc0);
    if (iVar2 == 0) {
        char *p = param_1 + 0x10c6;
        iVar2 = FUN_00086be4(buf, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        iVar2 = FUN_00022658(0x135000U, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        if (*(volatile int *)0x2000230cUL < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)0x20007554UL;
        format_string = 0x9e69cU;
    } else {
        if (*(volatile int *)0x2000230cUL < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)0x20007554UL;
        format_string = 0x9e67cU;
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, 0x9e789U);
    } else {
        FUN_00019c70(format_string, 0x9e789U);
    }
    return 0xffffffff;
}
