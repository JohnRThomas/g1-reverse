/* Reconstructed FUN_00082258 @ 0x82258  (parity: 300/300 trials, PROVEN) */

extern void FUN_00058c34(int,int,int,int,int,int,short);
extern int net_buf_simple_pull_le16(int);
void FUN_00082258(int param_1,int param_2)
{
    int uVar1 = net_buf_simple_pull_le16(param_2 + 0xc);
    FUN_00058c34(param_1,0,0,uVar1,0,*(int*)(param_2+0xc),*(short*)(param_2+0x10));
}

