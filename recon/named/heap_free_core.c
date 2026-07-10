/* named: heap_free_core */
/* Reconstructed heap_free_core @ 0x76d8c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int __malloc_lock(void);
extern void __malloc_unlock(void*,void*,void*,void*);
#define U(x) ((uint32_t)(x))
void heap_free_core(int* param_1, int param_2, int param_3, int param_4){
    int *piVar1, *piVar3, *piVar4, *piVar5;
    int iVar2; int bVar6;
    if(param_2==0) return;
    piVar5 = (int*)(param_2 - 4);
    if(*(int*)(param_2-4) < 0)
        piVar5 = (int*)((int)piVar5 + *(int*)(param_2-4));
    piVar1 = (int*)__malloc_lock();
    piVar3 = (int*)0x2000cc20;
    piVar4 = (int*)*(volatile uint32_t*)0x2000cc20UL;
    if(piVar4 != 0){
        if(U(piVar4) <= U(piVar5)){
            do {
                piVar3 = piVar4;
                piVar4 = (int*)piVar3[1];
                if(piVar4==0) break;
            } while(U(piVar4) <= U(piVar5));
            piVar1 = (int*)*piVar3;
            if((int*)((int)piVar3+(int)piVar1)==piVar5){
                piVar1 = (int*)((int)piVar1 + *piVar5);
                *piVar3 = (int)piVar1;
                if(piVar4 == (int*)((int)piVar3+(int)piVar1)){
                    iVar2 = *piVar4;
                    piVar3[1] = piVar4[1];
                    *piVar3 = iVar2 + (int)piVar1;
                }
            } else if(U(piVar5) < U((int*)((int)piVar3+(int)piVar1))){
                *param_1 = 0xc;
            } else {
                piVar1 = (int*)((int)piVar5 + *piVar5);
                bVar6 = (piVar4 == piVar1);
                if(bVar6){
                    iVar2 = *piVar4;
                    piVar4 = (int*)piVar4[1];
                    piVar1 = (int*)(iVar2 + *piVar5);
                }
                piVar5[1] = (int)piVar4;
                if(bVar6) *piVar5 = (int)piVar1;
                piVar3[1] = (int)piVar5;
            }
            goto LAB;
        }
        piVar1 = (int*)((int)piVar5 + *piVar5);
        if(piVar4 == piVar1){
            iVar2 = *piVar4;
            piVar4 = (int*)piVar4[1];
            piVar1 = (int*)(iVar2 + *piVar5);
            *piVar5 = (int)piVar1;
        }
    }
    piVar5[1] = (int)piVar4;
    *piVar3 = (int)piVar5;
LAB:
    __malloc_unlock(param_1, piVar1, piVar3, (void*)param_4);
    return;
}

