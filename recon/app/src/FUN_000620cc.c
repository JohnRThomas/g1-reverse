/* Reconstructed FUN_000620cc @ 0x620cc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_0008638c(void);

int FUN_000620cc(int param_1){
    int iVar5 = *(volatile int*)(param_1+4);
    int iVar6 = iVar5 + 0x28;
    int iVar2; uint32_t uVar7; uint8_t bVar1; volatile uint32_t *puVar8;
    uint32_t uVar9, uVar4, uVar3;
    while (1) {
        if (*(volatile int*)(iVar5+4) != 0){
            iVar2 = FUN_0008638c();
            if (iVar2==0) return -0x13;
            uVar7 = *(volatile uint16_t*)(iVar5+10);
            iVar2 = *(volatile int*)(iVar5+4);
            bVar1 = *(volatile uint8_t*)(iVar5+8);
            puVar8 = *(volatile uint32_t* volatile*)(iVar2+8);
            if ((uVar7 & 0x30)==0x30){
                FUN_0007e2fa(0x00099cbd,0x00099c84,0x00099c53,0x3ca);
                FUN_0007e2fa(0x00099cda);
                uVar3 = 0x3ca; goto L62124;
            }
          L6212a:
            if ((uVar7 & 6)==4){
                FUN_0007e2fa(0x00099cbd,0x00099dad,0x00099c53,0x3d1);
                uVar3 = 0x3d1; goto L62124;
            }
            uVar9 = 1u << bVar1;
            if ((uVar9 & **(volatile uint32_t* volatile*)(iVar2+4))==0){
                FUN_0007e2fa(0x00099cbd,0x00099de0,0x00099c53,0x3e4);
                FUN_0007e2fa(0x00099e1e);
                uVar3 = 0x3e4; goto L62124;
            }
            uVar4 = **(volatile uint32_t* volatile*)(iVar2+0x10);
            if ((int)(uVar7 << 0x1f) < 0) uVar9 = uVar9 | uVar4;
            else uVar9 = uVar4 & ~uVar9;
            **(volatile uint32_t* volatile*)(iVar2+0x10) = uVar9;
            iVar2 = ((int(*)(int,uint32_t,uint32_t))(*puVar8))(iVar2,(uint32_t)bVar1, uVar7|0x20000);
            if (iVar2 != 0) return iVar2;
        }
        iVar5 = iVar5 + 8;
        if (iVar6 == iVar5) return 0;
        continue;
      L62124:
        FUN_0007e2ec(0x00099c53, uVar3);
        goto L6212a;
    }
}

