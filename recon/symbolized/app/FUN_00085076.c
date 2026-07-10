#include "g1_app_symbols.h"
/* named: FUN_00085076 */
/* Reconstructed FUN_00085076 @ 0x85076  (parity: 300/300 trials, PROVEN) */

extern unsigned int cjson_create_number(void);
extern int cjson_add_item_to_object(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void cjson_delete(unsigned int a);

unsigned int FUN_00085076(unsigned int param_1, unsigned int param_2)
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

