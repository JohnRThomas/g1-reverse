#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000829f0 @ 0x000829f0
 * public-name: read_name
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   bt_dev_get                               <= FUN_00054ce0 @ 0x00054ce0
 *   bt_gatt_attr_read                        <= FUN_00082932 @ 0x00082932
 *   read_name                                <= FUN_000829f0 @ 0x000829f0
 */
/* Reconstructed FUN_000829f0 @ 0x829f0  (parity: 300/300 trials, PROVEN) */

extern int strlen(const void *);
extern unsigned int bt_dev_get(void);
extern void bt_gatt_attr_read(int,int,int,unsigned int,unsigned short);
void read_name(int param_1, int param_2, int param_3, int param_4,
                  unsigned short param_5)
{
    unsigned int text = bt_dev_get();
    unsigned short length =
        (unsigned short)strlen((const void *)(unsigned long)text);
    bt_gatt_attr_read(param_3, param_4, param_5, text, length);
}
