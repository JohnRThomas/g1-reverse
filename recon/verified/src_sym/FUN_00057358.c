/* Reconstructed FUN_00057358 @ 0x57358  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_queue_init(unsigned int);
extern void net_pkt_skip(unsigned int, unsigned int);
extern void FUN_00059690(void);
extern int FUN_0005e5b8(void);
extern void FUN_000579d0(void);

int FUN_00057358(void)
{
    z_impl_k_queue_init(0x20003a60UL);
    unsigned int uVar1 = 0x20003a60UL;
    unsigned int iVar3 = 0x2000ac7cUL;
    int iVar2 = 0;
    do {
        iVar2 = iVar2 + 1;
        net_pkt_skip(uVar1, iVar3);
        iVar3 = iVar3 + 0x10;
    } while (iVar2 != 10);
    FUN_00059690();
    int r = FUN_0005e5b8();
    if (r == 0) {
        FUN_000579d0();
    }
    return r;
}

