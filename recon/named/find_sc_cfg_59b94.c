/* named: find_sc_cfg_59b94 */
/* Reconstructed find_sc_cfg_59b94 @ 0x59b94  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int find_sc_cfg_59b94(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = 0;
    unsigned int iVar3 = 0x20006329UL;
    while ((*(volatile unsigned char*)(iVar3 - 1) != param_1) ||
           (bt_addr_le_eq_0(param_2, iVar3, param_3, (unsigned int)*(volatile unsigned char*)(iVar3 - 1), param_4) == 0))
    {
        iVar2 = iVar2 + 0xc;
        iVar3 = iVar3 + 0xc;
        if (iVar2 == 0x24) {
            return 0;
        }
    }
    return 0x20006328UL + iVar2;
}

