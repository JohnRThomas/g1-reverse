/* Reconstructed opt3007_get_max_lux @ 0x10a68  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern unsigned long long __floatdidf(unsigned int, unsigned int);
extern unsigned long long __divdf3(unsigned int lo, unsigned int hi, unsigned int c1, unsigned int c2, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
extern int __fixdfsi(unsigned int lo, unsigned int hi);
extern int get_device_info(void);
extern void debug_print(unsigned long, ...);
extern int FUN_0002e648(unsigned int a);

int opt3007_get_max_lux(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2;

    if (*(volatile unsigned char *)0x20018da1UL == 0) {
        iVar2 = -1;
    } else {
        iVar2 = FUN_0002e648(0);
        if (1 < (unsigned int)(iVar2 + 1)) {
            unsigned int iVar3 = get_device_info();
            long long lVar1 = (long long)iVar2 * (long long)*(volatile int *)(iVar3 + 0xfb0);
            unsigned long long uVar5 = __floatdidf((unsigned int)lVar1, (unsigned int)((unsigned long long)lVar1 >> 32));
            uVar5 = __divdf3((unsigned int)uVar5, (unsigned int)(uVar5 >> 32), 0, 0x412e8480U,
                                  param_1, param_2, param_3, param_4);
            if (2 < *(volatile int *)0x2000230cUL) {
                if (*(volatile int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                    iVar3 = get_device_info();
                    DEBUG_PRINT(0xa3c82U, 0xa3d12U, (unsigned int)iVar2, *(volatile unsigned int *)(iVar3 + 0xfb0),
                                (unsigned int)uVar5, (unsigned int)(uVar5 >> 32), *(volatile unsigned int *)(iVar3 + 0xfb0));
                } else {
                    iVar3 = get_device_info();
                    debug_print(0xa3c82U, 0xa3d12U, (unsigned int)iVar2, *(volatile unsigned int *)(iVar3 + 0xfb0), uVar5,
                                 *(volatile unsigned int *)(iVar3 + 0xfb0));
                }
            }
            iVar2 = __fixdfsi((unsigned int)uVar5, (unsigned int)(uVar5 >> 32));
        }
    }
    return iVar2;
}

