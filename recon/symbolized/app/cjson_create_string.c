#include "g1_app_symbols.h"
/* named: cjson_create_string */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_create_string @ 0x64c5c  (parity: 300/300 trials, PROVEN) */

extern int alloc_zeroed_node(unsigned int a);
extern int cjson_strdup(unsigned int a);
extern void cjson_delete(unsigned int a);

int cjson_create_string(unsigned int param_1)
{
    int iVar1, iVar2;
    iVar1 = alloc_zeroed_node(*(volatile unsigned int*)((uintptr_t)&g_cjson_hooks) /*=0x20002bac*/);
    if (iVar1 != 0) {
        *(volatile int*)(iVar1 + 0xc) = 0x10;
        iVar2 = cjson_strdup(param_1);
        *(volatile int*)(iVar1 + 0x10) = iVar2;
        if (iVar2 != 0) {
            return iVar1;
        }
        cjson_delete(iVar1);
    }
    return 0;
}

