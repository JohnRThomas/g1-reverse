/* Reconstructed get_flash_info @ 0x32628  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0007d120(int,int,int,int,void*);
extern int FUN_0008638c(int);
extern int FUN_00086c04(void*,int,int);

uint32_t get_flash_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    volatile uint8_t *puVar4;
    int iVar2;
    uint8_t uVar3;
    volatile uint8_t *puVar5 = (volatile uint8_t*)param_4;
    DEBUG_PRINT(0x000a69f3);
    if (param_3==0 || param_4==0){ DEBUG_PRINT(0x000a6a0b); return 0xffffffff; }
    puVar4 = (volatile uint8_t*)*param_3;
    *puVar4 = 0x1e;
    uVar3 = *(volatile uint8_t*)(param_1+1);
    puVar4[2]=3; puVar4[1]=uVar3; puVar4[3]=4;
    iVar2 = FUN_0008638c(0x00087bf0);
    if (iVar2==0){
        if (0 < *(volatile int*)0x2000230cUL){
            uint32_t v = *(volatile uint32_t*)0x00087bf0UL;
            int c = *(volatile int*)0x20007554UL;
            if (c==0){ DEBUG_PRINT(0x000a40e6,0x000a76cb,v); }
            else { FUN_00019c70(0x000a40e6,0x000a76cb,v); }
        }
        *puVar4=0x1e; puVar4[1]=*(volatile uint8_t*)(param_1+1); puVar4[2]=3; uVar3=1; puVar4[3]=1;
        puVar4[4]=uVar3; uVar3=5;
    } else {
        iVar2 = FUN_000167a8();
        if (*(volatile int*)(iVar2+0x1030) != 0){
            iVar2 = FUN_0007d120(0x00087bf0, 0x002612d2, 0x20019daf, 0x4e, (void*)puVar5);
            if (iVar2 != 0){
                DEBUG_PRINT(0x0009e2da, iVar2);
                *puVar4=0x1e; uVar3=*(volatile uint8_t*)(param_1+1); puVar4[2]=3; puVar4[1]=uVar3; puVar4[3]=1; uVar3=2;
                puVar4[4]=uVar3; uVar3=5;
                *(volatile uint8_t*)param_4=uVar3; return 0;
            }
            DEBUG_PRINT(0x000a6aab, 0);
        }
        FUN_00086c04((void*)(puVar4+4), 0x20019daf, 0x4e);
        uVar3=0x52;
    }
    *(volatile uint8_t*)param_4=uVar3;
    return 0;
}

