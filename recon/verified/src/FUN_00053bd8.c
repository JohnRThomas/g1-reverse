/* Reconstructed FUN_00053bd8 @ 0x53bd8 CFG_VERIFY_ORACLE0_R0_POINTER */

#include <stdint.h>
extern void FUN_000566a4(int);
extern uint64_t FUN_00056908(uint32_t,int);
extern void FUN_00056ae0(int);
extern void FUN_00073418(int,uint32_t,int,int);
extern uint64_t FUN_00080e6a(void*,int);
extern void FUN_00080ea2(uint32_t,int,void*);
extern void FUN_00080ea8(void*,uint32_t);
extern void FUN_00081adc(int,void*);

void FUN_00053bd8(int param_1){
    volatile char *pcVar4 = *(char* volatile*)(param_1+0xc);
    uint16_t uVar1 = *(volatile uint16_t*)(pcVar4+1);
    uint64_t uVar6 = FUN_00056908(uVar1, 1);
    uint32_t uVar3 = (uint32_t)(uVar6 >> 32);
    int iVar2 = (int)(uint32_t)uVar6;
    uint32_t local_30, local_2c, uStack_28, local_20, local_1c;
    if (iVar2 == 0){
        local_2c = 0x000f2db7; local_30 = 3; uStack_28 = uVar1;
        FUN_00080ea2(0x00088138, 0x1840, &local_30);
        return;
    }
    volatile uint32_t *piVar5 = (volatile uint32_t *)(iVar2 + 4);
    if (*pcVar4 == 0x1a){
        if (*(volatile char*)(iVar2+3) == 1){
            uVar6 = FUN_00080e6a((void*)piVar5, 0x400);
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
        FUN_00080ea8((void*)piVar5, 0xfffffeff);
    }
    FUN_00056ae0(iVar2);
  L_c44:
    FUN_000566a4(iVar2);
    return;
  L_c74:
    /* The original uses LDA then tests bit 8 via LSLS #23/BPL. */
    if (((*piVar5 & 0x100u) == 0) || (*pcVar4 != 0x20) || (*(volatile char*)(iVar2+0xb4) == 0)) goto L_c68;
    *(volatile char*)(iVar2+0xb4) = *(volatile char*)(iVar2+0xb4) - 1;
    FUN_00073418(iVar2+0x60, uVar3, 0x28000, 0);
    FUN_00056ae0(iVar2);
    goto L_c44;
    (void)local_2c; (void)uStack_28; (void)local_1c;
}
