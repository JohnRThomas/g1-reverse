/* readable reconstruction; identity: FUN_00034bd4 @ 0x00034bd4
 * public-name: is_on_whitelist_by_identifier
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 *   strstr                                   <= FUN_000870be @ 0x000870be
 * address symbols (name @ address):
 *   rodata_9adaa                             @ 0x0009adaa
 *   rodata_9d7b8                             @ 0x0009d7b8
 *   rodata_a819e                             @ 0x000a819e
 *   rodata_a81b7                             @ 0x000a81b7
 *   rodata_a81d0                             @ 0x000a81d0
 *   rodata_a81e6                             @ 0x000a81e6
 *   rodata_a81fa                             @ 0x000a81fa
 *   rodata_a835e                             @ 0x000a835e
 *   rodata_a8373                             @ 0x000a8373
 *   rodata_a844e                             @ 0x000a844e
 *   rodata_a8491                             @ 0x000a8491
 *   rodata_a84a2                             @ 0x000a84a2
 *   rodata_a84c4                             @ 0x000a84c4
 *   rodata_a85c4                             @ 0x000a85c4
 *   rodata_a85d6                             @ 0x000a85d6
 *   rodata_a8a8a                             @ 0x000a8a8a
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed is_on_whitelist_by_identifier @ 0x34bd4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void log_message(uint32_t,...);
extern unsigned int strlen(const void *);
extern void debug_print(uint32_t,...);
extern int strncmp(const void *,int,unsigned int);
extern int strstr(const void *,int);

int is_on_whitelist_by_identifier(int param_1){
    volatile int *g = (volatile int*)0x20007554UL;
    volatile unsigned char *pb = (volatile unsigned char*)0x2001a22cUL;
    int iVar6 = *g;
    unsigned int uVar4;
    unsigned int uVar3;
    unsigned int uVar5;
    int chk;

    if(param_1 != 0){
        uVar4 = strlen((const void *)param_1);
        if(uVar4 < 0x28){
            if(iVar6==0){ log_message(0x000a8491,param_1); }
            else { debug_print(0x000a8491,param_1); }
            chk = strncmp((const void *)0x000a81d0,param_1,0x15);
            int iVar7 = *g;
            int sh;
            if( (chk==0) ||
                ((chk=strncmp((const void *)0x0009adaa,param_1,0x1c))==0) ||
                ((chk=strncmp((const void *)0x000a81b7,param_1,0x18))==0) ||
                ((chk=strncmp((const void *)0x000a819e,param_1,0x18))==0) ){
                sh = (int)((unsigned int)*pb << 0x1f);
                uVar3 = 0x000a84a2;
                uVar5 = 0x000a84c4;
            } else {
                if( ((chk=strncmp((const void *)0x000a81e6,param_1,0x13))==0) ||
                    ((chk=strncmp((const void *)0x000a81fa,param_1,0x14))==0) ){
                    sh = (int)((unsigned int)*pb << 0x1e);
                    uVar3 = 0x000a84e7;
                    uVar5 = 0x000a850c;
                } else {
                    if( ((chk=strncmp((const void *)0x0009d7b8,param_1,0x13))==0) ||
                        ((chk=strncmp((const void *)0x000a8373,param_1,0x19))==0) ){
                        sh = (int)((unsigned int)*pb << 0x1c);
                        uVar3 = 0x000a8532;
                        uVar5 = 0x000a8558;
                    } else {
                        chk = strncmp((const void *)0x000a835e,param_1,0x14);
                        if(chk != 0){
                            if(iVar7==0){ log_message(0x000a85c4,pb[1]); }
                            else { debug_print(0x000a85c4,pb[1]); }
                            if( ((int)((unsigned int)*pb << 0x1b) < 0) && (pb[1] != 0) ){
                                unsigned char bVar9 = 0;
                                while( (unsigned int)bVar9 < pb[1] ){
                                    unsigned char *entry = (unsigned char *)pb +
                                                           (unsigned int)bVar9 * 0x38 + 2;
                                    if(*g==0){ log_message(0x000a85d6,(unsigned int)bVar9,entry); }
                                    else { debug_print(0x000a85d6,(unsigned int)bVar9,entry); }
                                    uVar4 = strlen(entry);
                                    chk = strncmp(entry,param_1,uVar4);
                                    bVar9 = bVar9 + 1;
                                    if(chk==0){ return 2; }
                                }
                            }
                            chk = strstr((const void *)0x0009d7b8,param_1);
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
                if(iVar7==0){ log_message(uVar3); } else { debug_print(uVar3); }
                return 2;
            }
            if(iVar7==0){ log_message(uVar5); } else { debug_print(uVar5); }
            return 1;
        }
        uVar3 = 0x000a846a;
        uVar5 = 0x4a;
    } else {
        uVar3 = 0x000a844e;
        uVar5 = 0x46;
    }
    if(iVar6==0){ log_message(uVar3,0x000a8a8a,uVar5); }
    else { debug_print(uVar3,0x000a8a8a,uVar5); }
    return 0;
}
