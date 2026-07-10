/* Reconstructed is_on_whitelist_by_identifier @ 0x34bd4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(void);
extern unsigned int FUN_0000ef12(void);
extern int FUN_00019c70(void);
extern int FUN_00087036(void);
extern int FUN_000870be(void);

int is_on_whitelist_by_identifier(int param_1){
    volatile int *g = (volatile int*)0x20007554UL;
    volatile unsigned char *pb = (volatile unsigned char*)0x2001a22cUL;
    int iVar6 = *g;
    unsigned int uVar4;
    int chk;

    if(param_1 != 0){
        uVar4 = FUN_0000ef12();
        if(uVar4 < 0x28){
            if(iVar6==0){ DEBUG_PRINT(); } else { FUN_00019c70(); }
            chk = FUN_00087036();
            int iVar7 = *g;
            int sh;
            if( (chk==0) ||
                ((chk=FUN_00087036())==0) ||
                ((chk=FUN_00087036())==0) ||
                ((chk=FUN_00087036())==0) ){
                sh = (int)((unsigned int)*pb << 0x1f);
            } else {
                if( ((chk=FUN_00087036())==0) ||
                    ((chk=FUN_00087036())==0) ){
                    sh = (int)((unsigned int)*pb << 0x1e);
                } else {
                    if( ((chk=FUN_00087036())==0) ||
                        ((chk=FUN_00087036())==0) ){
                        sh = (int)((unsigned int)*pb << 0x1c);
                    } else {
                        chk = FUN_00087036();
                        if(chk != 0){
                            if(iVar7==0){ DEBUG_PRINT(); } else { FUN_00019c70(); }
                            if( ((int)((unsigned int)*pb << 0x1b) < 0) && (pb[1] != 0) ){
                                unsigned char bVar9 = 0;
                                while( (unsigned int)bVar9 < pb[1] ){
                                    if(*g==0){ DEBUG_PRINT(); } else { FUN_00019c70(); }
                                    FUN_0000ef12();
                                    chk = FUN_00087036();
                                    bVar9 = bVar9 + 1;
                                    if(chk==0){ return 2; }
                                }
                            }
                            chk = FUN_000870be();
                            if(chk==0){ return 1; }
                            return 3;
                        }
                        sh = (int)((unsigned int)*pb << 0x1d);
                    }
                }
            }
            if(sh < 0){
                if(iVar7==0){ DEBUG_PRINT(); } else { FUN_00019c70(); }
                return 2;
            }
            if(iVar7==0){ DEBUG_PRINT(); } else { FUN_00019c70(); }
            return 1;
        }
    }
    if(iVar6==0){ DEBUG_PRINT(); } else { FUN_00019c70(); }
    return 0;
}

