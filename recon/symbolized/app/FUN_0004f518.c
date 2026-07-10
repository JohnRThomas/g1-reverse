#include "g1_app_symbols.h"
/* named: FUN_0004f518 */
/* Reconstructed FUN_0004f518 @ 0x4f518  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*,int,int);
extern int FUN_0005b0dc(int,int,int);
extern int bt_gatt_notify_cb(int,void*);

int FUN_0004f518(int param_1, int param_2, short param_3)
{
    unsigned char buf[24];
    int iVar2;
    memset_bytes(buf, 0, 0x18);
    *(int*)(buf+4) = "Y5" /*=0x8ad40*/;
    *(int*)(buf+8) = param_2;
    *(short*)(buf+0xc) = param_3;
    *(int*)(buf+0x10) = ((uintptr_t)&tbl_4f4b8) /*=0x4f4f1*/;
    if (param_1 == 0 || ((iVar2 = FUN_0005b0dc(param_1, "Y5" /*=0x8ad40*/, 1)), iVar2 != 0)) {
        return bt_gatt_notify_cb(param_1, buf);
    } else {
        return 0xffffffea;
    }
}

