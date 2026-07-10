#include "g1_app_symbols.h"
/* named: FUN_0008509e */
/* Reconstructed FUN_0008509e @ 0x8509e  (parity: 300/300 trials, PROVEN) */

extern int cjson_create_string(int);
extern int cjson_add_item_to_object(int,int,int,int);
extern void cjson_delete(int);
int FUN_0008509e(int param_1,int param_2,int param_3)
{
    int uVar1 = cjson_create_string(param_3);
    int iVar2 = cjson_add_item_to_object(param_1,param_2,uVar1,0);
    if (iVar2 == 0) {
        cjson_delete(uVar1);
        uVar1 = 0;
    }
    return uVar1;
}

