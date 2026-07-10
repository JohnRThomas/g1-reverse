/* named: FUN_000844a8 */
/* Reconstructed FUN_000844a8 @ 0x844a8  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fn_t)(int, void*, int, short);

void FUN_000844a8(int *param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char local_29;
    unsigned char *local_28;
    unsigned int local_24;
    unsigned char local_20;
    unsigned int local_1c;
    unsigned int uStack_18;
    unsigned char local_14;

    local_28 = &local_29;
    local_24 = 1;
    local_20 = 0;
    local_14 = 7;
    local_29 = param_2;
    local_1c = param_3;
    uStack_18 = param_4;
    ((fn_t)(*(int *)(*(int *)(*param_1 + 8) + 8)))(*param_1, &local_28, 2, (short)param_1[1]);
}

