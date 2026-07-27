/* Reconstructed FUN_00055ba0 @ 0x55ba0  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007e2ec(unsigned long, unsigned long);
extern void FUN_0007e2fa(unsigned long, ...);

void FUN_00055ba0(unsigned char *param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
    (void)param_3; (void)param_4;
    unsigned char *puVar1 = param_2 + 0x10;
    int bVar2;
    if (param_2 < param_1) {
        bVar2 = (puVar1 <= param_1);
    } else {
        if (param_1 == param_2) {
            FUN_0007e2fa(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"((psrc < pdst && (psrc + length) <= pdst) || (psrc > pdst && (pdst + length) <= psrc))"), ((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h"), 533);
            FUN_0007e2fa(((unsigned long)"\tSource and destination buffers must not overlap\n"));
            FUN_0007e2ec(((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h"), 533);
            return;
        }
        bVar2 = ((param_1 + 0x10) <= param_2);
    }
    if (bVar2) {
        param_1 = param_1 - 1;
        do {
            puVar1 = puVar1 - 1;
            param_1 = param_1 + 1;
            *param_1 = *puVar1;
        } while (puVar1 != param_2);
        return;
    }
    FUN_0007e2fa(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"((psrc < pdst && (psrc + length) <= pdst) || (psrc > pdst && (pdst + length) <= psrc))"), ((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h"), 533);
    FUN_0007e2fa(((unsigned long)"\tSource and destination buffers must not overlap\n"));
    FUN_0007e2ec(((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h"), 533);
}
