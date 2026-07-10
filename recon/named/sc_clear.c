/* named: sc_clear */
/* Reconstructed sc_clear @ 0x5a090  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_is_bonded(unsigned char a, int b);
extern int find_sc_cfg_59bcc(unsigned char a, int b);
extern void FUN_00082928(void);
extern int bt_gatt_clear_sc(void);
extern void FUN_00082a42(int a, int b, void *c);

void sc_clear(int param_1)
{
    int iVar1;

    iVar1 = bt_addr_le_is_bonded(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
    if (iVar1 == 0) {
        iVar1 = find_sc_cfg_59bcc(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
        if (iVar1 != 0) {
            FUN_00082928();
        }
    } else {
        int iStack_18 = bt_gatt_clear_sc();
        if (iStack_18 != 0) {
            int local_20 = 3;
            int local_1c = 0xf47c1;
            (void)local_1c;
            FUN_00082a42(0x88128, 0x1840, &local_20);
        }
    }
}

