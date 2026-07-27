/* Reconstructed is_on_whitelist_by_identifier @ 0x34bd4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern unsigned int FUN_0000ef12(const void *);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00087036(const void *,int,unsigned int);
extern int FUN_000870be(const void *,int);

int is_on_whitelist_by_identifier(int param_1){
    volatile int *g = (volatile int*)0x20007554UL;
    volatile unsigned char *pb = (volatile unsigned char*)0x2001a22cUL;
    int iVar6 = *g;
    unsigned int uVar4;
    unsigned int uVar3;
    unsigned int uVar5;
    int chk;

    if(param_1 != 0){
        uVar4 = FUN_0000ef12((const void *)param_1);
        if(uVar4 < 0x28){
            if(iVar6==0){ DEBUG_PRINT(0x000a8491,param_1); }
            else { FUN_00019c70(0x000a8491,param_1); }
            chk = FUN_00087036((const void *)0x000a81d0,param_1,0x15);
            int iVar7 = *g;
            int sh;
            if( (chk==0) ||
                ((chk=FUN_00087036((const void *)0x0009adaa,param_1,0x1c))==0) ||
                ((chk=FUN_00087036((const void *)0x000a81b7,param_1,0x18))==0) ||
                ((chk=FUN_00087036((const void *)0x000a819e,param_1,0x18))==0) ){
                sh = (int)((unsigned int)*pb << 0x1f);
                uVar3 = 0x000a84a2;
                uVar5 = 0x000a84c4;
            } else {
                if( ((chk=FUN_00087036((const void *)0x000a81e6,param_1,0x13))==0) ||
                    ((chk=FUN_00087036((const void *)0x000a81fa,param_1,0x14))==0) ){
                    sh = (int)((unsigned int)*pb << 0x1e);
                    uVar3 = 0x000a84e7;
                    uVar5 = 0x000a850c;
                } else {
                    if( ((chk=FUN_00087036((const void *)0x0009d7b8,param_1,0x13))==0) ||
                        ((chk=FUN_00087036((const void *)0x000a8373,param_1,0x19))==0) ){
                        sh = (int)((unsigned int)*pb << 0x1c);
                        uVar3 = 0x000a8532;
                        uVar5 = 0x000a8558;
                    } else {
                        chk = FUN_00087036((const void *)0x000a835e,param_1,0x14);
                        if(chk != 0){
                            if(iVar7==0){ DEBUG_PRINT(0x000a85c4,pb[1]); }
                            else { FUN_00019c70(0x000a85c4,pb[1]); }
                            if( ((int)((unsigned int)*pb << 0x1b) < 0) && (pb[1] != 0) ){
                                unsigned char bVar9 = 0;
                                while( (unsigned int)bVar9 < pb[1] ){
                                    unsigned char *entry = (unsigned char *)pb +
                                                           (unsigned int)bVar9 * 0x38 + 2;
                                    if(*g==0){ DEBUG_PRINT(0x000a85d6,(unsigned int)bVar9,entry); }
                                    else { FUN_00019c70(0x000a85d6,(unsigned int)bVar9,entry); }
                                    uVar4 = FUN_0000ef12(entry);
                                    chk = FUN_00087036(entry,param_1,uVar4);
                                    bVar9 = bVar9 + 1;
                                    if(chk==0){ return 2; }
                                }
                            }
                            chk = FUN_000870be((const void *)0x0009d7b8,param_1);
                            if(chk==0){ return 1; }
                            return 3;
                        }
                        sh = (int)((unsigned int)*pb << 0x1d);
                        uVar3 = 0x000a857f;
                        uVar5 = 0x000a85a1;
                    }
                }
            }
            if(sh < 0){
                if(iVar7==0){ DEBUG_PRINT(uVar3); } else { FUN_00019c70(uVar3); }
                return 2;
            }
            if(iVar7==0){ DEBUG_PRINT(uVar5); } else { FUN_00019c70(uVar5); }
            return 1;
        }
        uVar3 = 0x000a846a;
        uVar5 = 0x4a;
    } else {
        uVar3 = 0x000a844e;
        uVar5 = 0x46;
    }
    if(iVar6==0){ DEBUG_PRINT(uVar3,0x000a8a8a,uVar5); }
    else { FUN_00019c70(uVar3,0x000a8a8a,uVar5); }
    return 0;
}
