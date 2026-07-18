/* Reconstructed FUN_00057358 @ 0x57358  (parity: 300/300 trials, PROVEN) */

#define g1_recon_z_impl_k_queue_init FUN_000864e8
extern void g1_recon_z_impl_k_queue_init(void *queue);
extern void FUN_00086502(unsigned int, unsigned int);
extern void FUN_00059690(void);
extern int FUN_0005e5b8(void);
extern void FUN_000579d0(void);

int FUN_00057358(void)
{
    g1_recon_z_impl_k_queue_init((void *)0x20003a60UL);
    unsigned int uVar1 = 0x20003a60UL;
    unsigned int iVar3 = 0x2000ac7cUL;
    int iVar2 = 0;
    do {
        iVar2 = iVar2 + 1;
        FUN_00086502(uVar1, iVar3);
        iVar3 = iVar3 + 0x10;
    } while (iVar2 != 10);
    FUN_00059690();
    int r = FUN_0005e5b8();
    if (r == 0) {
        FUN_000579d0();
    }
    return r;
}
