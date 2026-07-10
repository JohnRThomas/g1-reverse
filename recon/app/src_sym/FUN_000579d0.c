/* Reconstructed FUN_000579d0 @ 0x579d0  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_queue_init(int);
extern void net_pkt_skip(int,int);
extern void memset_bytes(int,int,int);
void FUN_000579d0(void)
{
    z_impl_k_queue_init(0x20003a44);
    int uVar1 = 0x20003a44;
    int iVar3 = 0;
    int iVar2 = 0x2000ad34;
    do {
        memset_bytes(iVar2, 0, 0x10);
        iVar3 = iVar3 + 1;
        net_pkt_skip(uVar1, iVar2);
        iVar2 = iVar2 + 0x10;
    } while (iVar3 != 10);
}

