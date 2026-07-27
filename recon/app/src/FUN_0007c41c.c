/* Reconstructed FUN_0007c41c @ 0x7c41c  (parity: 300/300 trials, PROVEN) */

/* P4 iteration 40 -- DROPPED ARGUMENT.  Shipped 0007c41e `mov r5,r0` then
 * 0007c420 `bl #0x7c3ea` with r0 STILL the node; the header-length op is a
 * one-argument function (see FUN_0007c3ea, which dereferences r0). */
extern int FUN_0007c3ea(unsigned int param_1);
extern int FUN_0007c408(unsigned int param_1);

int FUN_0007c41c(unsigned int param_1)
{
    int iVar1 = FUN_0007c3ea(param_1);
    int iVar2 = FUN_0007c408(param_1);
    return iVar2 + iVar1;
}

