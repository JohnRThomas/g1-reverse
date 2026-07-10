#include "g1_app_symbols.h"
/* named: FUN_00053bd8 */
/* Reconstructed FUN_00053bd8 @ 0x53bd8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void ble_conn_unref(int);
extern uint64_t ble_conn_lookup_masked(uint32_t,int);
extern void ble_notify_le_param_updated(int);
extern void FUN_00073418(int,uint32_t,int,int);
extern uint64_t atomic_or(void*,int);
extern void FUN_00080ea2(uint32_t,int,void*);
extern void atomic_and_3(void*,uint32_t);
extern void FUN_00081adc(int,void*);

void FUN_00053bd8(int param_1){
    volatile char *pcVar4 = *(char* volatile*)(param_1+0xc);
    uint16_t uVar1 = *(volatile uint16_t*)(pcVar4+1);
    uint64_t uVar6 = ble_conn_lookup_masked(uVar1, 1);
    uint32_t uVar3 = (uint32_t)(uVar6 >> 32);
    int iVar2 = (int)(uint32_t)uVar6;
    uint32_t local_30, local_2c, uStack_28, local_20, local_1c;
    if (iVar2 == 0){
        local_2c = "Unable to lookup conn for handle %u" /*=0xf2db7*/; local_30 = 3; uStack_28 = uVar1;
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, &local_30);
        return;
    }
    volatile int *piVar5 = (volatile int*)(iVar2+4);
    if (*pcVar4 == 0x1a){
        if (*(volatile char*)(iVar2+3) == 1){
            uVar6 = atomic_or((void*)piVar5, 0x400);
            uVar3 = (uint32_t)(uVar6 >> 32);
            if (((int32_t)((uint32_t)uVar6 << 0x15)) >= 0){
                local_20 = *(volatile uint32_t*)(iVar2+0xa8);
                local_1c = *(volatile uint32_t*)(iVar2+0xb0);
                FUN_00081adc(iVar2, &local_20);
                goto L_c44;
            }
            goto L_c4c;
        }
        goto L_c74;
    } else {
      L_c4c:
        if (*pcVar4 != 0) goto L_c74;
        *(volatile uint16_t*)(iVar2+0xa6) = *(volatile uint16_t*)(pcVar4+3);
        *(volatile uint16_t*)(iVar2+0xac) = *(volatile uint16_t*)(pcVar4+5);
        *(volatile uint16_t*)(iVar2+0xae) = *(volatile uint16_t*)(pcVar4+7);
      L_c68:
        atomic_and_3((void*)piVar5, 0xfffffeff);
    }
    ble_notify_le_param_updated(iVar2);
  L_c44:
    ble_conn_unref(iVar2);
    return;
  L_c74:
    if ((((int32_t)(*piVar5 << 0x17)) >= 0) || (*pcVar4 != 0x20) || (*(volatile char*)(iVar2+0xb4) == 0)) goto L_c68;
    *(volatile char*)(iVar2+0xb4) = *(volatile char*)(iVar2+0xb4) - 1;
    FUN_00073418(iVar2+0x60, uVar3, ((uintptr_t)&rodata_28000) /*=0x28000*/, 0);
    ble_notify_le_param_updated(iVar2);
    goto L_c44;
    (void)local_2c; (void)uStack_28; (void)local_1c;
}

