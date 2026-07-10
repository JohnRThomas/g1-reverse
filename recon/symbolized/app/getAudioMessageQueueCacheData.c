#include "g1_app_symbols.h"
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
    int iVar1 = k_msgq_get(((uintptr_t)&g_audio_msgq) /*=0x20003890*/, param_1, 0, 0, param_4);
    if(iVar1 != 0){
        if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0){
            if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0){
                DEBUG_PRINT("%s(): dequeue_dmic failed\r\n\n" /*=0xa3f62*/,"getAudioMessageQueueCacheData" /*=0xa4908*/);
            } else { debug_print(); }
        }
        iVar1 = -1;
    }
    return iVar1;
}

