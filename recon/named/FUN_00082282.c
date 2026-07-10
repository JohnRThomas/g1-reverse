/* named: FUN_00082282 */
/* Reconstructed FUN_00082282 @ 0x82282  (parity: 300/300 trials, PROVEN) */

extern unsigned int net_buf_simple_pull_le16(int);
extern void FUN_00058c34(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00082282(unsigned int param_1, int param_2)
{
    unsigned int uVar1;
    uVar1 = net_buf_simple_pull_le16(param_2 + 0xc);
    FUN_00058c34(param_1, 0x12, 0x13, uVar1, 0, *(unsigned int*)(param_2 + 0xc), *(unsigned short*)(param_2 + 0x10));
    return;
}

