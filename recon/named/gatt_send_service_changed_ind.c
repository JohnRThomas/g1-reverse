/* named: gatt_send_service_changed_ind */
/* Reconstructed gatt_send_service_changed_ind @ 0x81b30  (parity: 300/300 trials, PROVEN) */

extern int FUN_00057394(void);
extern int FUN_000573f4(int a, int b, int c);
extern short *net_buf_simple_add(int a, int b);
extern void att_send_and_schedule_tx(int a, int b, int c, int d, int e);

unsigned int gatt_send_service_changed_ind(int *param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;

    if (*param_1 == 0) {
        uVar1 = 0xffffff80;
    } else {
        uVar1 = FUN_00057394();
        *(volatile char *)((char *)param_1 + 0xb8) = (char)uVar1;
        iVar2 = FUN_000573f4(6, uVar1, 4);
        if (iVar2 == 0) {
            uVar1 = 0xfffffff4;
        } else {
            short *puVar3 = net_buf_simple_add(iVar2 + 0xc, 4);
            *(volatile short *)puVar3 = *(volatile short *)((char *)param_1 + 0x24);
            *(volatile short *)(puVar3 + 1) = *(volatile short *)((char *)param_1 + 0x14);
            att_send_and_schedule_tx((int)param_1, iVar2, 0x10000, 0, param_4);
            uVar1 = 0;
            *(volatile char *)((char *)param_1 + 0xb4) = 4;
        }
    }
    return uVar1;
}

