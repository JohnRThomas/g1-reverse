/* named: FUN_00057358 */
/* Reconstructed FUN_00057358 @ 0x57358  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_queue_init(unsigned int);
extern void net_pkt_skip(unsigned int, unsigned int);
extern void bt_gatt_init(void);
extern int smp_update_bond_flag(void);
extern void bt_l2cap_init(void);

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
    bt_gatt_init();
    int r = smp_update_bond_flag();
    if (r == 0) {
        bt_l2cap_init();
    }
    return r;
}

