/* named: notification_icon_type_from_package */
/* Reconstructed notification_icon_type_from_package @ 0x3483c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint8_t strlen(void*);
extern int get_device_info(void);
extern int strncmp(int,int,int,int,int);
int notification_icon_type_from_package(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
    int iVar3=param_1*0x1b4+0x20007dbc;
    int iVar2=strncmp(0xa819e,iVar3,0x18,0x1b4,(int)param_4);
    if(iVar2==0){ iVar2=1; }
    else{
        iVar2=strncmp(0x9adaa,iVar3,0x1c,0,0);
        if(iVar2==0){ iVar2=1; }
        else{
            iVar2=strncmp(0xa81b7,iVar3,0x18,0,0);
            if(iVar2==0){ iVar2=2; }
            else{
                iVar2=strncmp(0xa81d0,iVar3,0x15,0,0);
                if(iVar2==0){ iVar2=2; }
                else{
                    iVar2=strncmp(0xa81e6,iVar3,0x13,0,0);
                    if(iVar2!=0){
                        iVar2=strncmp(0xa81fa,iVar3,0x14,0,0);
                        if(iVar2!=0){
                            int t=get_device_info();
                            char* pcVar4=(*(volatile char*)(t+0x1068)!=0)?(char*)0x20003292:(char*)0x20003152;
                            for(; *(volatile char*)pcVar4!=0; pcVar4+=0x20){
                                uint8_t b=strlen(pcVar4);
                                if(b>0x1e) b=0x1f;
                                iVar2=strncmp((int)pcVar4,iVar3,b,0,0);
                                if(iVar2==0) return 3;
                            }
                            t=get_device_info();
                            pcVar4=(*(volatile char*)(t+0x1068)!=0)?(char*)0x200030d2:(char*)0x20003032;
                            for(; *(volatile char*)pcVar4!=0; pcVar4+=0x20){
                                uint8_t b=strlen(pcVar4);
                                if(b>0x1e) b=0x1f;
                                iVar2=strncmp((int)pcVar4,iVar3,b,0,0);
                                if(iVar2==0) return 4;
                            }
                            iVar2=5;
                        }
                    }
                }
            }
        }
    }
    return iVar2;
}

