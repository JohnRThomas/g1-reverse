#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000543d8 @ 0x000543d8
 * public-name: bt_hci_cmd_send_or_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_or_create                <= FUN_000543d8 @ 0x000543d8
 *   net_buf_destroy_default                  <= FUN_0005f200 @ 0x0005f200
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f3103                             @ 0x000f3103
 *   hci_cmd_pool                             @ 0x2000214c
 */
/* Reconstructed FUN_000543d8 @ 0x543d8  (parity: 300/300 trials, PROVEN) */
extern int bt_hci_cmd_create(void);
extern int FUN_000543c8(int);
extern void net_buf_destroy_default(unsigned,int);
extern void net_buf_unref(int);
extern void FUN_00080ea2(unsigned,int,void*);
int bt_hci_cmd_send_or_create(int param_1, int param_2, unsigned param_3, unsigned param_4){
    int r4 = param_2;
    if (param_2 == 0){
        r4 = bt_hci_cmd_create();
        if (r4 == 0) return -0x69;
    }
    if (param_1 == 0xc35){
        int r5 = FUN_000543c8(r4);
        if (r5 != 0){
            volatile unsigned local[8];
            local[4]=3; local[5]=((unsigned long)&rodata_f3103) /*=0xf3103*/; local[6]=(unsigned)r5;
            FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, (void*)&local[4]);
            net_buf_unref(r4);
        }
        return r5;
    } else {
        net_buf_destroy_default(((unsigned long)&hci_cmd_pool) /*=0x2000214c*/, r4);
        return 0;
    }
}
