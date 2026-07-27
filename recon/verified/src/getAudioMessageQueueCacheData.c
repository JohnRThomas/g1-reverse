/* Reconstructed getAudioMessageQueueCacheData @ 0x2f460  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072240(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
int getAudioMessageQueueCacheData(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    (void)param_2;
    (void)param_3;
    int iVar1 = FUN_00072240(0x20003890UL, param_1, 0, 0, param_4);
    if(iVar1 != 0){
        if(*(volatile int*)0x2000230cUL > 0){
            unsigned int sink = *(volatile unsigned int*)0x20007554UL;
            if(sink==0){
                DEBUG_PRINT(0x000a3f62UL,0x000a4908UL,0,sink);
            } else { FUN_00019c70(0x000a3f62UL,0x000a4908UL,0,sink); }
        }
        iVar1 = -1;
    }
    return iVar1;
}
