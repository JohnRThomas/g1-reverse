#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085076 @ 0x00085076
 * public-name: cjson_object_add_number
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_create_number                      <= FUN_00012c18 @ 0x00012c18
 *   cjson_add_item_to_object                 <= FUN_0006466c @ 0x0006466c
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_object_add_number                  <= FUN_00085076 @ 0x00085076
 */
/* Reconstructed FUN_00085076 @ 0x85076  (parity: 300/300 trials, PROVEN) */

extern unsigned int cjson_create_number(void);
extern int cjson_add_item_to_object(int, int, int, int);
extern void cjson_delete(volatile int*);

unsigned int cjson_object_add_number(unsigned int param_1, unsigned int param_2)
{
    unsigned int uVar1;
    int iVar2;
    uVar1 = cjson_create_number();
    iVar2 = cjson_add_item_to_object(param_1, param_2, uVar1, 0);
    if (iVar2 == 0) {
        cjson_delete(uVar1);
        uVar1 = 0;
    }
    return uVar1;
}
