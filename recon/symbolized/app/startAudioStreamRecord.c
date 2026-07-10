#include "g1_app_symbols.h"
/* named: startAudioStreamRecord */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003890  g_audio_msgq                 
//   0x20007554  g_log_use_alt_sink           
//   0x200079e4  g_app_language_msgq          
*/
/* Reconstructed startAudioStreamRecord @ 0x2f764  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);
extern unsigned int get_device_info(void);
extern void display_DelayClose(unsigned int ms);
extern int k_msgq_put(int a, void *b, int c, int d);
extern void FUN_00072880(void *a);
extern void memset_bytes(void *dst, int val, int n);
extern void sync_to_slave(unsigned int a, unsigned int b, void *c, unsigned int d);

unsigned int startAudioStreamRecord(void)
{
    unsigned char buf[208];
    int iVar2;
    unsigned int uVar3;

    memset_bytes(buf + 5, 0, 0xcb);
    buf[4] = 1;
    iVar2 = k_msgq_put(((uintptr_t)&g_audio_msgq) /*=0x20003890*/, buf + 4, 0, 0);
    if (iVar2 == 0) {
        FUN_00072880((void*)((uintptr_t)&g_app_language_msgq) /*=0x200079e4*/);
        uVar3 = 0;
    } else {
        if (0 < *(int *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): start up audio record failed\r\n\n" /*=0xa4304*/, "startAudioStreamRecord" /*=0xa496f*/);
            } else {
                debug_print();
            }
        }
        *(unsigned short *)buf = 1;
        uVar3 = get_device_info();
        sync_to_slave(uVar3, 6, buf, 2);
        display_DelayClose(10000);
        if (0 < *(int *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): because startup auido record failed,exit quicknote ....\n" /*=0xa432a*/, "startAudioStreamRecord" /*=0xa496f*/);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

