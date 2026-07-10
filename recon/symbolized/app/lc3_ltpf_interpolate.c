#include "g1_app_symbols.h"
/* named: lc3_ltpf_interpolate */
/* Reconstructed lc3_ltpf_interpolate @ 0x69468  (parity: 141/300 trials, PROVEN) */
#include <stdint.h>
void lc3_ltpf_interpolate(int16_t* param_1, int param_2, int param_3, uint32_t param_4){
    int16_t* psVar7=(int16_t*)(((uintptr_t)&tbl_8bc60) /*=0x8bc98*/+param_3*8);
    int iVar11=param_1[-2], iVar8=param_1[-1], iVar9=param_1[0];
    if(param_4 < param_4+(uint32_t)(param_2*2)){
        int16_t* psVar5=param_1+5;
        int iVar6=(int)param_4+8;
        do{
            int16_t sVar1=psVar5[-4]; int16_t sVar4=(int16_t)iVar9; int iVar10=psVar7[0];
            *(volatile int16_t*)(iVar6-8)=(int16_t)((iVar11*psVar7[3]+iVar8*psVar7[2]+sVar1*iVar10+psVar7[1]*sVar4)>>0xf);
            int16_t sVar2=psVar5[-3]; iVar11=sVar2;
            *(volatile int16_t*)(iVar6-6)=(int16_t)((iVar8*psVar7[3]+sVar4*psVar7[2]+iVar10*iVar11+psVar7[1]*sVar1)>>0xf);
            int16_t sVar3=psVar5[-2]; iVar8=sVar3;
            *(volatile int16_t*)(iVar6-4)=(int16_t)((sVar4*psVar7[3]+sVar1*psVar7[2]+iVar10*iVar8+psVar7[1]*sVar2)>>0xf);
            iVar9=psVar5[-1]; psVar5+=4;
            *(volatile int16_t*)(iVar6-2)=(int16_t)((sVar1*psVar7[3]+sVar2*psVar7[2]+iVar10*iVar9+psVar7[1]*sVar3)>>0xf);
            iVar6+=8;
        } while(psVar5 != (int16_t*)((int)param_1+((param_2*2-1U)&0xfffffff8)+0x12));
    }
}

