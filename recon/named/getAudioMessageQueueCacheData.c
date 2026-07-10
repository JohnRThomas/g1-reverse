/* named: getAudioMessageQueueCacheData */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003890  g_audio_msgq                 
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed getAudioMessageQueueCacheData @ 0x2f460  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int getAudioMessageQueueCacheData(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    int iVar1 = k_msgq_get(0x20003890UL, param_1, 0, 0, param_4);
    if(iVar1 != 0){
        if(*(volatile int*)0x2000230cUL > 0){
            if(*(volatile unsigned int*)0x20007554UL==0){
                DEBUG_PRINT(0x000a3f62UL,0x000a4908UL);
            } else { debug_print(); }
        }
        iVar1 = -1;
    }
    return iVar1;
}

