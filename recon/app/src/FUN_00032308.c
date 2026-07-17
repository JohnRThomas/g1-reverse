/* Reconstructed FUN_00032308 @ 0x32308  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned int, ...);
extern void FUN_00022b00(int,int);
extern int FUN_000232f8(void*);
extern void FUN_0007d14a(int);

int FUN_00032308(int param_1, unsigned param_2, uint32_t *param_3, uint8_t *param_4){
    unsigned char status_record[21];
    DEBUG_PRINT(0x000a6711, 0x000a7712);
    if (param_3==0 || param_4==0 || param_1==0 || param_2 < 5){
        DEBUG_PRINT(0x000a671e, 0x000a7712);
        return 0xffffffff;
    }
    unsigned char *puVar6 = (unsigned char*)*param_3;
    *puVar6 = 0x3c;
    puVar6[2]=3; puVar6[1]=1; puVar6[3]=1;
    unsigned char bVar1 = *(unsigned char*)(param_1+4);
    unsigned char uVar4;
    if (bVar1 < 2){
        int iVar2 = FUN_000167a8();
        if (*(unsigned char*)(iVar2+0xed4) != bVar1){
            iVar2 = FUN_000167a8(); *(unsigned char*)(iVar2+0xed4) = bVar1;
            iVar2 = FUN_000167a8(); FUN_00022b00(iVar2, 0);
            char cVar5 = 0;
            do {
                iVar2 = FUN_000232f8(status_record);
                if (iVar2 == 0 && status_record[20] == bVar1) break;
                cVar5 = cVar5 + 1;
                FUN_0007d14a(100);
            } while (cVar5 != 5);
            puVar6[4] = (cVar5 == 5);
            goto LAB;
        }
        uVar4 = 4;
    } else {
        if (*(int*)0x20007554 == 0) DEBUG_PRINT(0x000a676d, 0x000a7712, 0x3c1);
        else FUN_00019c70(0x000a676d, 0x000a7712, 0x3c1);
        uVar4 = 3;
    }
    puVar6[4] = uVar4;
    LAB:
    *param_4 = 5;
    return 0;
}
