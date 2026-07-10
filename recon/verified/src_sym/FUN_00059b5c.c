/* Reconstructed FUN_00059b5c @ 0x59b5c  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int FUN_00059b5c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = 0;
    unsigned int iVar3 = 0x2000aed5UL;
    while ((*(volatile unsigned char*)(iVar3 - 1) != param_1) ||
           (bt_addr_le_eq_0(param_2, iVar3, param_3, (unsigned int)*(volatile unsigned char*)(iVar3 - 1), param_4) == 0))
    {
        iVar2 = iVar2 + 0x10;
        iVar3 = iVar3 + 0x10;
        if (iVar2 == 0x30) {
            return 0;
        }
    }
    return 0x2000aed4UL + iVar2;
}

