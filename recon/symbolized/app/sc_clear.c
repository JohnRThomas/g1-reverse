#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a090 @ 0x0005a090
 * public-name: sc_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59bcc                        <= FUN_00059bcc @ 0x00059bcc
 *   bt_gatt_clear_sc                         <= FUN_0005a044 @ 0x0005a044
 *   sc_clear                                 <= FUN_0005a090 @ 0x0005a090
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   gatt_sc_ctx_clear                        <= FUN_00082928 @ 0x00082928
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f47c1                             @ 0x000f47c1
 */
/* Reconstructed FUN_0005a090 @ 0x5a090  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_is_bonded(unsigned char, const void*);
extern int find_sc_cfg_59bcc(unsigned char a, int b);
extern void gatt_sc_ctx_clear(void);
extern unsigned int bt_gatt_clear_sc(void);
extern void log_msg_create_3arg(int a, int b, void *c);

void sc_clear(int param_1)
{
    int iVar1;

    iVar1 = bt_addr_le_is_bonded(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
    if (iVar1 == 0) {
        iVar1 = find_sc_cfg_59bcc(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
        if (iVar1 != 0) {
            gatt_sc_ctx_clear();
        }
    } else {
        int iStack_18 = bt_gatt_clear_sc();
        if (iStack_18 != 0) {
            int local_20 = 3;
            int local_1c = ((unsigned long)&rodata_f47c1) /*=0xf47c1*/;
            (void)local_1c;
            log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &local_20);
        }
    }
}
