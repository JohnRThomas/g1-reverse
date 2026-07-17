/* Reconstructed FUN_0008397e @ 0x8397e  (parity: 300/300 trials, PROVEN) */

extern int FUN_00060ab0(unsigned int a, void *b, unsigned int c);
extern void FUN_00086384(unsigned int a);

int FUN_0008397e(unsigned int param_1)
{
    int iVar1;
    struct {
        unsigned int opcode;
        unsigned int first;
        unsigned int second;
    } request = { 0xab, 0, 0 };
    iVar1 = FUN_00060ab0(param_1, &request, 0);
    if (-1 < iVar1) {
        FUN_00086384(0x23);
        iVar1 = 0;
    }
    return iVar1;
}
