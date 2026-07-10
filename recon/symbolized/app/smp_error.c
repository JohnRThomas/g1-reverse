#include "g1_app_symbols.h"
/* named: smp_error */
/* Reconstructed smp_error @ 0x5dc2c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00056a68(unsigned a, int b);
extern void smp_pairing_complete(int a, unsigned b);
extern void net_buf_unref(int a);
extern unsigned net_buf_simple_add(int a, int b);
extern int bt_conn_create_pdu(unsigned a, int b, int c, int d, int e);
extern unsigned atomic_test_bit(int a, int b);
extern void FUN_00083074(unsigned a, unsigned b, void*c);
extern int smp_create_pdu(int a, int b);
unsigned smp_error(int param_1, unsigned param_2){
    int iVar4 = param_1 + 4;
    unsigned uVar1 = atomic_test_bit(iVar4, 2);
    if (uVar1 != 0) uVar1 = (*(volatile short*)(param_1 + 0xe8) == 0) ? 1 : 0;
    int called = 0;
    if (atomic_test_bit(iVar4, 3) != 0) called = 1;
    else if (atomic_test_bit(iVar4, 1) != 0) called = 1;
    else if (atomic_test_bit(iVar4, 0xf) != 0) called = 1;
    if (called) smp_pairing_complete(param_1, param_2);
    unsigned loc[4];
    if (uVar1 == 0){
        int node = smp_create_pdu(param_1, 5);
        if (node == 0) return 0xffffff97u;
        unsigned char *puVar3 = (unsigned char*)net_buf_simple_add(node + 0xc, 1);
        *(volatile unsigned char*)puVar3 = (unsigned char)param_2;
        int i = bt_conn_create_pdu(*(volatile unsigned*)(param_1 + 0xf0), 6, node, 0, 0);
        if (i != 0) net_buf_unref(node);
    } else {
        loc[1] = "SMP does not allow a pairing failure at this point. Known issue. Disconnecting instead." /*=0xf4f98*/; loc[0] = 2;
        FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1080, loc);
        FUN_00056a68(*(volatile unsigned*)(param_1 + 0xf0), 5);
    }
    return 0;
}

