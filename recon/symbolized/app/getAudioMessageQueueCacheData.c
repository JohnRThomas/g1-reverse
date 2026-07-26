#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002f460 @ 0x0002f460
 * public-name: getAudioMessageQueueCacheData
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   rodata_a3f62                             @ 0x000a3f62   [INLINED -- G6 literal batch]
 *   rodata_a4908                             @ 0x000a4908   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_audio_msgq                             @ 0x20003890
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed getAudioMessageQueueCacheData @ 0x2f460  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
int getAudioMessageQueueCacheData(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    (void)param_2;
    (void)param_3;
    int iVar1 = k_msgq_get(((unsigned long)&g_audio_msgq) /*=0x20003890*/, param_1, 0, 0, param_4);
    if(iVar1 != 0){
        if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0){
            unsigned int sink = *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            if(sink==0){
                log_message(((unsigned long)"%s(): dequeue_dmic failed\r\n\n") /*=0xa3f62*/,((unsigned long)"getAudioMessageQueueCacheData") /*=0xa4908*/,0,sink);
            } else { debug_print(((unsigned long)"%s(): dequeue_dmic failed\r\n\n") /*=0xa3f62*/,((unsigned long)"getAudioMessageQueueCacheData") /*=0xa4908*/,0,sink); }
        }
        iVar1 = -1;
    }
    return iVar1;
}
