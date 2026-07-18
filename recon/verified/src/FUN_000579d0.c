/* Reconstructed FUN_000579d0 @ 0x579d0  (parity: 300/300 trials, PROVEN) */

#define z_impl_k_queue_init FUN_000864e8
extern void z_impl_k_queue_init(void *queue);
extern void FUN_00086502(int,int);
extern void FUN_00086c78(int,int,int);
void FUN_000579d0(void)
{
    z_impl_k_queue_init((void *)0x20003a44);
    int uVar1 = 0x20003a44;
    int iVar3 = 0;
    int iVar2 = 0x2000ad34;
    do {
        FUN_00086c78(iVar2, 0, 0x10);
        iVar3 = iVar3 + 1;
        FUN_00086502(uVar1, iVar2);
        iVar2 = iVar2 + 0x10;
    } while (iVar3 != 10);
}
