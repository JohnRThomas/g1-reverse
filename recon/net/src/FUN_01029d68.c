/* net-core FUN_01029d68 @ 0x1029d68  (parity 300 trials PROVEN) */

extern void FUN_01023d38(int);
void FUN_01029d68(int param_1,int param_2)
{
    param_2 = param_2 + *(int *)(param_1 + 4);
    *(int *)(param_1 + 4) = param_2;
    FUN_01023d38(param_2 - 0x62);
}

