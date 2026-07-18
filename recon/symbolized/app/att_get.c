#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005858c @ 0x0005858c
 * public-name: att_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_get                                  <= FUN_0005858c @ 0x0005858c
 *   bt_l2cap_le_lookup_rx_cid                <= FUN_00081aca @ 0x00081aca
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 */
/* Reconstructed FUN_0005858c @ 0x5858c  (parity: 300/300 trials, PROVEN) */

extern int bt_l2cap_le_lookup_rx_cid(int a, int b, int c, int d, int e, int f, int g, int h);
extern void FUN_00081ddc(int a, int b, void *c);

unsigned int att_get(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1;
    unsigned int uVar2;
    int local[2];

    if (*(char *)(param_1 + 0xd) == 7) {
        iVar1 = bt_l2cap_le_lookup_rx_cid(param_1, 4, param_3, 7, param_1, param_2, param_3, param_4);
        if (iVar1 != 0 && (*(volatile int *)(iVar1 + 0x118) << 0x1d) < 0) {
            return *(unsigned int *)(iVar1 - 8);
        }
        uVar2 = 0x1040;
    } else {
        uVar2 = 0x1080;
    }
    FUN_00081ddc(((unsigned long)&rodata_88100) /*=0x88100*/, uVar2, local);
    return 0;
}
