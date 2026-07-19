#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076e20 @ 0x00076e20
 * public-name: _malloc_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _malloc_r                                <= FUN_00076e20 @ 0x00076e20
 *   _sbrk_r                                  <= FUN_000778f4 @ 0x000778f4
 *   __malloc_lock                            <= FUN_000785bc @ 0x000785bc
 *   __malloc_unlock                          <= FUN_000785c8 @ 0x000785c8
 * address symbols (name @ address):
 *   g_malloc_sbrk_start                      @ 0x2000cc1c
 *   g_malloc_free_list                       @ 0x2000cc20
 */
/* Reconstructed FUN_00076e20 @ 0x76e20  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int _sbrk_r(void*,...);
extern void __malloc_lock(void);
extern void __malloc_unlock(void*);

uint _malloc_r(uint *param_1, uint param_2, uint param_3, uint param_4){
    int iVar2;
    uint *puVar3, *puVar5;
    uint uVar4, uVar6;
    uVar6 = ((param_2 + 3) & 0xfffffffc) + 8;
    if (uVar6 < 0xc) uVar6 = 0xc;
    if (((int)uVar6 < 0) || (uVar6 < param_2)){
        *param_1 = 0xc;
        return 0;
    }
    __malloc_lock();
    int *piVar1 = (int*)((unsigned long)&g_malloc_sbrk_start) /*=0x2000cc1c*/;
    puVar3 = *(uint**)((unsigned long)&g_malloc_free_list) /*=0x2000cc20*/;
    for (puVar5 = *(uint**)((unsigned long)&g_malloc_free_list) /*=0x2000cc20*/; puVar5 != 0; puVar5 = (uint*)puVar5[1]){
        uVar4 = *puVar5 - uVar6;
        if (-1 < (int)uVar4){
            if (0xb < uVar4){
                *puVar5 = uVar4;
                puVar5 = (uint*)((int)puVar5 + uVar4);
                goto LAB_e84;
            }
            uVar6 = puVar5[1];
            if (puVar3 == puVar5) *(uint*)((unsigned long)&g_malloc_free_list) /*=0x2000cc20*/ = uVar6;
            if (puVar3 != puVar5) puVar3[1] = uVar6;
            goto LAB_e92;
        }
        puVar3 = puVar5;
    }
    if (*(int*)((unsigned long)&g_malloc_sbrk_start) /*=0x2000cc1c*/ == 0){
        iVar2 = _sbrk_r(param_1,0,puVar3,0,param_4);
        *piVar1 = iVar2;
    }
    puVar3 = (uint*)_sbrk_r(param_1,uVar6);
    if ((puVar3 != (uint*)0xffffffff) &&
        ((puVar5 = (uint*)(((int)puVar3 + 3U) & 0xfffffffc), puVar3 == puVar5 ||
          (iVar2 = _sbrk_r(param_1,(int)puVar5-(int)puVar3), iVar2 != -1)))){
        LAB_e84:
        *puVar5 = uVar6;
        LAB_e92:
        __malloc_unlock(param_1);
        puVar3 = puVar5 + 1;
        uVar6 = ((int)puVar5 + 0xbU) & 0xfffffff8;
        iVar2 = uVar6 - (int)puVar3;
        if (iVar2 != 0) puVar3 = (uint*)((int)puVar3 - uVar6);
        if (iVar2 == 0) return uVar6;
        *(uint**)((int)puVar5 + iVar2) = puVar3;
        return uVar6;
    }
    *param_1 = 0xc;
    __malloc_unlock(param_1);
    return 0;
}
