/* Reconstructed FUN_00024dac @ 0x24dac  (parity: 300/300 trials, PROVEN) */

extern int FUN_00024d74(void*a);
extern int FUN_00025788(unsigned a, unsigned b, void*c, int d, unsigned e);
int FUN_00024dac(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    volatile unsigned char *pc = (volatile unsigned char*)0x20007a14;
    pc[8] = 0;
    unsigned local_18 = param_3;
    unsigned uStack_14 = param_4;
    unsigned local_1c = param_2;
    short sv = (short)FUN_00024d74(&local_18);
    int iVar4 = (int)sv;
    if (iVar4 != 0) return iVar4;
    unsigned b0 = local_18 & 0xff;
    if ((unsigned char)(b0 + 0x1f) > 1) return -5;
    unsigned b1 = (local_18 >> 8) & 0xff;
    if ((b1 & 0xfc) != 0x40) return -5;
    unsigned uVar7 = (local_18 >> 16) & 0xff;
    pc[2] = (unsigned char)uVar7;
    unsigned uVar5; short sVar3;
    if (uVar7 == 0){
        unsigned hw = (uStack_14 >> 16) & 0xffff;
        unsigned sw = ((hw & 0xff) << 8) | ((hw >> 8) & 0xff);
        uVar7 = sw; sVar3 = (short)sw; uVar5 = 8;
    } else { uVar5 = 4; sVar3 = 0; }
    pc[1] = (unsigned char)b1;
    unsigned b3 = (local_18 >> 24) & 0xff;
    volatile unsigned *puVar2 = (volatile unsigned*)0x20007a44;
    *(volatile short*)(pc + 6) = sVar3;
    *(volatile unsigned*)(pc + 0xc) = uVar5;
    pc[0] = (unsigned char)b0;
    pc[3] = (unsigned char)b3;
    for(;;){
        int r = FUN_00025788(*puVar2, *(volatile unsigned*)(pc + 0xc), &local_1c, 4, param_1);
        if (r != 0) return -5;
        if (*(volatile unsigned*)(pc + 0xc) >= uVar7) return -5;
        unsigned l0 = local_1c & 0xff;
        if (l0 == 3){
            unsigned l1 = (local_1c >> 8) & 0xff;
            unsigned char store;
            if (l1 == 0) store = 1;
            else { store = 3; if ((pc[1] & 3) == 0) store = 2; }
            pc[8] = store;
            return 0;
        }
        if (l0 != 0xfd) return -5;
        unsigned uVar6 = (local_1c >> 8) & 0xff;
        if (uVar6 == 0xff) uVar6 = (local_1c >> 16) & 0xffff;
        *(volatile unsigned*)(pc + 0xc) = *(volatile unsigned*)(pc + 0xc) + uVar6;
    }
}

