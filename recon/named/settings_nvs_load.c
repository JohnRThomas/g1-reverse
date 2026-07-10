/* named: settings_nvs_load */
/* Reconstructed settings_nvs_load @ 0x4e780  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
extern int settings_nvs_read_latest(int,int,void*,int);
extern void settings_nvs_delete_id(int,int);
extern void nvs_write(int,int,void*,int);
extern int settings_call_set_handler(void*,int,unsigned,void*,unsigned);

int settings_nvs_load(int param_1, unsigned param_2){
    unsigned uVar1 = 0x0007f211;
    int iVar7 = param_1 + 8;
    unsigned char auStack_6c[76];
    unsigned char uStack_75;
    int local_74; short local_70;
    unsigned short r4v = (unsigned short)(*(unsigned short*)(param_1+0x38) + 1);
    int iVar2, iVar3;
    unsigned short sVar4, sVar6, sVar5;
  LOOP:
    sVar4 = r4v;
    sVar6 = (unsigned short)(sVar4 - 1);
    if (sVar6 == 0x8000) return 0;
    iVar2 = settings_nvs_read_latest(iVar7, sVar6, auStack_6c, 0x4a);
    sVar5 = (unsigned short)(sVar4 + 0x3fff);
    iVar3 = settings_nvs_read_latest(iVar7, sVar5, &uStack_75, 1);
    if (iVar2 > 0){
        if (iVar3 > 0) goto L806;
        goto L7d8;
    }
    if (iVar3 > 0) goto L7d8;
    r4v = sVar6;
    goto LOOP;
  L7d8:
    if (*(unsigned short*)(param_1+0x38) == sVar6){
        *(unsigned short*)(param_1+0x38) = (unsigned short)(sVar4 - 2);
        nvs_write(iVar7, 0x8000, (void*)(param_1+0x38), 2);
    }
    settings_nvs_delete_id(iVar7, sVar6);
    settings_nvs_delete_id(iVar7, sVar5);
    r4v = sVar6;
    goto LOOP;
  L806:
    auStack_6c[iVar2] = 0;
    local_74 = iVar7;
    local_70 = (short)sVar5;
    iVar2 = settings_call_set_handler(auStack_6c, iVar3, uVar1, &local_74, param_2);
    if (iVar2 != 0) return iVar2;
    r4v = sVar6;
    goto LOOP;
}

