/* Reconstructed FUN_0007d9c0 @ 0x7d9c0  (parity: 157/300 trials, PROVEN) */

unsigned FUN_0007d9c0(unsigned param_1, unsigned param_2, unsigned param_3, int param_4,
                      char param_5, unsigned char *param_6, int param_7){
    if (param_6 == 0) return 0;
    if (param_7 <= 0) return 0;
    unsigned char *cur = param_6;
    unsigned char *end = param_6 + param_7;
    do {
        unsigned byte = *(volatile unsigned char*)cur; cur++;
        unsigned uVar4;
        if (param_4 != 0){
            unsigned uVar7 = byte; int uVar6 = 7; unsigned uVar3 = 0;
            for(;;){
                unsigned t = uVar3;
                if (uVar7 & 1){ t = (t | (1u << uVar6)) & 0xff; }
                uVar3 = t;
                int cont = (uVar6 != 0);
                uVar6 = uVar6 - 1; uVar7 = uVar7 >> 1;
                if (!cont) break;
            }
            uVar4 = uVar3;
        } else { uVar4 = byte; }
        param_1 = param_1 ^ (uVar4 << 8);
        int iVar5 = 8;
        do {
            unsigned hi = param_1 & 0x8000;
            param_1 = (param_1 << 1) & 0xffff;
            if (hi != 0) param_1 = param_1 ^ param_2;
            iVar5--;
        } while (iVar5 != 0);
    } while (cur != end);
    unsigned uVar4 = param_1;
    if (param_5 != 0){
        unsigned r1 = param_1; int uVar3 = 0xf; uVar4 = 0;
        for(;;){
            if ((int)(r1 << 31) < 0){ uVar4 = ((1u << uVar3) | uVar4) & 0xffff; }
            int cont = (uVar3 != 0);
            uVar3 = uVar3 - 1; r1 = (r1 >> 1) & 0xffff;
            if (!cont) break;
        }
    }
    return param_3 ^ uVar4;
}

