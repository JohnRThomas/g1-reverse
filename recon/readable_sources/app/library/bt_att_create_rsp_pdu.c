#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_att_chan__param_0234                [param_0234; library]
 * Raw function identity: 0x00058f34.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00058f34 @ 0x00058f34
 * public-name: bt_att_create_rsp_pdu
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_chan_create_pdu                   <= FUN_000585f0 @ 0x000585f0
 *   bt_att_create_rsp_pdu                    <= FUN_00058f34 @ 0x00058f34
 *   att_log_emit_3arg                        <= FUN_00081ddc @ 0x00081ddc
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_f4651                             @ 0x000f4651
 */
/* Reconstructed FUN_00058f34 @ 0x58f34  (parity: 300/300 trials, PROVEN) */

extern int bt_att_chan_create_pdu(void);
extern void att_log_emit_3arg(int,int,void*);

int bt_att_create_rsp_pdu(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uStack_20 = param_3 + 1;
    unsigned short h2e = *(volatile unsigned short*)(param_1+0x2e);
    unsigned short h1e = *(volatile unsigned short*)(param_1+0x1e);
    unsigned int local_24 = h2e;
    if (h1e <= h2e) local_24 = h1e;
    if (local_24 < uStack_20) {
        struct { int f0; int f4; int f8; unsigned int fc; unsigned int f10; } s;
        s.f0 = 5;
        s.f4 = ((unsigned long)&rodata_f4651) /*=0xf4651*/;
        s.f8 = param_1;
        s.fc = local_24;
        s.f10 = uStack_20;
        att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x2880, &s);
        return 0;
    } else {
        return bt_att_chan_create_pdu();
    }
}
