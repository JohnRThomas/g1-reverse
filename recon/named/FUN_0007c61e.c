/* named: FUN_0007c61e */
/* Reconstructed FUN_0007c61e @ 0x7c61e  (parity: 300/300 trials, PROVEN) */
extern unsigned int opt_node_value_len(void);

unsigned int FUN_0007c61e(unsigned char *param_1, unsigned char *param_2)
{
    unsigned int uVar1;
    unsigned int uVar2;

    if (param_1 == 0 || param_2 == 0 || (unsigned char)(*param_2 - 1) > 0x15 ||
        *(unsigned int*)(param_2 + 4) == 0 || *(unsigned int*)(param_2 + 8) == 0 ||
        *(unsigned int*)(param_2 + 0xc) == 0) {
        uVar2 = 7;
    } else {
        *(unsigned char **)(param_1 + 0x14) = param_2;
        uVar1 = opt_node_value_len();
        uVar2 = 0;
        *param_1 = (*param_1 & 0xef) | ((uVar1 < 0x100) << 4);
    }
    return uVar2;
}

