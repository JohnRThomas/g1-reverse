/* named: gatt_dm_start */
/* Reconstructed gatt_dm_start @ 0x4ed8c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0004e98c(int);
extern int bt_gatt_discover(uint32_t,uint32_t);
extern int atomic_and_0(uint32_t,uint32_t);
extern int FUN_0007f406(uint32_t,uint32_t,void*);
extern int FUN_00086c1e(void*,void*,uint32_t,int);

int gatt_dm_start(uint32_t param_1, uint32_t *param_2, uint32_t param_3, uint32_t param_4){
    int iVar3;
    volatile uint32_t *g = (volatile uint32_t*)0x2000a28cUL;
    if ( (param_2==0 || (( *(uint8_t*)param_2 & 0xfd)==0)) && (param_3!=0) ) {
        uint32_t uVar4 = *g;
        *g = uVar4 | 1;
        if ((uVar4 & 1) == 0) {
            uint32_t one = uVar4 & 1;
            *(volatile uint32_t*)0x2000a154UL = param_1;
            *(volatile uint32_t*)0x2000a158UL = param_4;
            *(volatile uint32_t*)0x2000a2a4UL = one;
            *(volatile uint32_t*)0x2000a2a8UL = one;
            *(volatile uint8_t*)0x2000a2b4UL = (param_2 != 0) ? 1 : 0;
            *(volatile uint32_t*)0x2000a2b0UL = param_3;
            *(volatile uint32_t*)0x2000a288UL = one;
            *(volatile uint32_t*)0x2000a2acUL = one;
            if (param_2 != 0) {
                uint32_t uVar2 = FUN_0004e98c((uint8_t)*param_2);
                FUN_00086c1e((void*)0x2000a290UL, (void*)param_2, uVar2, 0x28);
                param_2 = (uint32_t*)0x2000a290UL;
            }
            *(volatile uint32_t*)0x2000a160UL = 0x0004ea79UL;
            *(volatile uint16_t*)0x2000a164UL = 1;
            *(volatile uint16_t*)0x2000a16aUL = 0xffff;
            *(volatile uint32_t*)0x2000a15cUL = (uint32_t)param_2;
            *(volatile uint8_t*)0x2000a16cUL = 0;
            iVar3 = bt_gatt_discover(param_1, 0x2000a15cUL);
            if (iVar3 != 0) {
                volatile uint32_t local_28=3, local_24=0x000f1574; volatile int iStack_20=iVar3;
                FUN_0007f406(0x00088130UL, 0x1840, (void*)&local_28);
                atomic_and_0(0x2000a28cUL, 0xfffffffe);
            }
        } else { iVar3 = -0x78; }
    } else { iVar3 = -0x16; }
    return iVar3;
}

