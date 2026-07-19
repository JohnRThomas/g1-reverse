#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086e1c @ 0x00086e1c
 * public-name: vfprintf_emit_padded_field
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   vfprintf_emit_padded_field               <= FUN_00086e1c @ 0x00086e1c
 */
/* Reconstructed FUN_00086e1c @ 0x86e1c  (parity: 246/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef int (*codef)(int,int,int,int);
uint32_t vfprintf_emit_padded_field(int param_1, uint* param_2, uint* param_3, int param_4, codef param_5){
    uint uVar4=param_2[4];
    if((int)param_2[4] < (int)param_2[2]) uVar4=param_2[2];
    *(volatile uint*)param_3=uVar4;
    if(*(volatile char*)((int)param_2+0x43)!=0) *(volatile uint*)param_3=uVar4+1;
    if((int)(*(volatile uint*)param_2<<0x1a)<0) *(volatile uint*)param_3=*(volatile uint*)param_3+2;
    if((*(volatile uint*)param_2&6)==0){
        for(int i=0;i<(int)(param_2[3]-*(volatile uint*)param_3);i++){
            int iVar3=param_5(param_1,param_4,(int)param_2+0x19,1);
            if(iVar3==-1) return 0xffffffff;
        }
    }
    uint u4=*(volatile uint8_t*)((int)param_2+0x43); if(u4!=0) u4=1;
    uint uVar5=u4;
    if((int)(*(volatile uint*)param_2<<0x1a)<0){
        uVar5=u4+2;
        *(volatile uint8_t*)((int)param_2+u4+0x43)=0x30;
        *(volatile uint8_t*)((int)param_2+u4+0x44)=*(volatile uint8_t*)((int)param_2+0x45);
    }
    int iVar1=param_5(param_1,param_4,(int)param_2+0x43,uVar5);
    if(iVar1==-1) return 0xffffffff;
    uint uu=*(volatile uint*)param_2&6;
    int bVar7=(uu==4);
    uint u5,u4b;
    if(bVar7){ u5=param_2[3]; u4b=*(volatile uint*)param_3; } else { u5=0; u4b=0; }
    uint uVar6=0;
    if(bVar7) u5=u5-u4b;
    if(bVar7) u5=u5 & ~((int)u5>>0x1f);
    if((int)param_2[4]<(int)param_2[2]) u5=u5+(param_2[2]-param_2[4]);
    for(; u5!=uVar6; uVar6++){
        int iv=param_5(param_1,param_4,(int)param_2+0x1a,1);
        if(iv==-1) return 0xffffffff;
    }
    return 0;
}
