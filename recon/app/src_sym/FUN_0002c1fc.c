/* Reconstructed FUN_0002c1fc @ 0x2c1fc  (parity: 300/300 trials, PROVEN) */

extern void k_uptime_get_2(void);
extern int FUN_00033cf8(void);

void FUN_0002c1fc(void)
{
    k_uptime_get_2();
    int iVar1 = FUN_00033cf8();
    if (iVar1 != 0) {
        *(volatile unsigned char*)0x20018d9eUL = 1;
    }
}

