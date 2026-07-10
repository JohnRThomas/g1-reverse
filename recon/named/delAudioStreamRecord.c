/* named: delAudioStreamRecord */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003890  g_audio_msgq                 
//   0x20007554  g_log_use_alt_sink           
//   0x200079e4  g_app_language_msgq          
*/
/* Reconstructed delAudioStreamRecord @ 0x2f878  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void FUN_00072880(unsigned int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int delAudioStreamRecord(unsigned char param_1)
{
    int iVar2;
    unsigned int uVar3;
    unsigned char buf[204];

    if (2 < *(volatile int*)0x2000230cUL) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0xa420e, 0xa4944);
        } else {
            debug_print();
        }
    }
    memset_bytes(buf + 1, 0, 0xcb);
    *(unsigned short*)(buf + 2) = 1;
    buf[0] = 4;
    buf[4] = param_1;
    iVar2 = k_msgq_put(*(volatile unsigned int*)0x20003890UL, buf, 0, 0);
    if (iVar2 == 0) {
        FUN_00072880(*(volatile unsigned int*)0x200079e4UL);
        uVar3 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa3f45, 0xa4944);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

