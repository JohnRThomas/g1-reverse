#include "g1_app_symbols.h"
/* named: cjson_print */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_print @ 0x64a88  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int cjson_print_value(int,void*);
extern void cursor_advance_past_cstring(void*);
extern void memcpy(int,uint32_t,unsigned);
extern void memset_bytes(void*,int,int);
typedef int (*fp)(int,int);
int cjson_print(int param_1, int param_2){
    volatile uint32_t *puVar1 = (volatile uint32_t*)((uintptr_t)&g_cjson_hooks) /*=0x20002bac*/;
    uint32_t s[9];
    int iVar2; unsigned uVar3;
    memset_bytes(s, 0, 0x24);
    s[0] = ((fp)puVar1[0])(0x100,0);
    s[1] = 0x100;
    s[6] = puVar1[0];
    s[7] = puVar1[1];
    s[8] = puVar1[2];
    s[5] = param_2;
    int local_34 = (int)s[0];
    if(local_34 != 0 && (iVar2 = cjson_print_value(param_1, s)) != 0){
        cursor_advance_past_cstring(s);
        int local_2c = (int)s[2];
        if(puVar1[2]==0){
            iVar2 = ((fp)puVar1[0])(local_2c+1,0);
            if(iVar2!=0){
                uVar3 = local_2c+1U;
                if(s[1] <= (unsigned)(local_2c+1U)) uVar3 = s[1];
                memcpy(iVar2, s[0], uVar3);
                *(volatile uint8_t*)(iVar2+local_2c)=0;
                ((fp)puVar1[1])(s[0],0);
                return iVar2;
            }
        } else {
            iVar2 = ((fp)puVar1[2])(s[0], local_2c+1);
            if(iVar2!=0) return iVar2;
        }
    }
    if((int)s[0]!=0){
        ((fp)puVar1[1])(0,0);
    }
    return 0;
}

