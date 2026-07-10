/* named: le_adv_update */
/* Reconstructed le_adv_update @ 0x811ce  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint8_t strlen(int);
extern int bt_dev_get(void);
extern int hci_set_ad(int,void*,int);
extern void memset_bytes(void*,int,int);
int le_adv_update(int param_1,int param_2,int param_3,int param_4,int param_5,char param_6,char param_7){
    char buf[0x10];
    memset_bytes(buf,0,0x10);
    int uVar3;
    if(param_7 != 0){
        int local_3c=bt_dev_get();
        if(param_2!=0){ for(int i=0;param_3!=i;i++) if((uint8_t)(*(volatile uint8_t*)(param_2+i*8)-8)<2) return -0x16; }
        if(param_4!=0){ for(int i=0;param_5!=i;i++) if((uint8_t)(*(volatile uint8_t*)(param_4+i*8)-8)<2) return -0x16; }
        strlen(local_3c);
        if(param_7==1){ uVar3=2; goto Lfa; }
    }
    uVar3=1;
Lfa:;
    int iVar1=hci_set_ad(0x2008,buf,uVar3);
    if(iVar1==0){
        if(param_6!=0){
            uVar3=1;
            if(param_7==2) uVar3=2;
            int iVar2=hci_set_ad(0x2009,buf,uVar3);
            if(iVar2!=0) return iVar2;
        }
        *(volatile uint32_t*)(param_1+0x10)=*(volatile uint32_t*)(param_1+0x10)|4;
    }
    return iVar1;
}

