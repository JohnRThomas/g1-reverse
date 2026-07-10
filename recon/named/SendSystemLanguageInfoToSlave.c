/* named: SendSystemLanguageInfoToSlave */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x2000392c  g_dashboard_response_msgq    
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed SendSystemLanguageInfoToSlave @ 0x48998  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int);

u32 SendSystemLanguageInfoToSlave(int param_1)
{
    u8 local[28];
    int iVar1;
    u32 uVar4;

    memset_bytes(&local[1], 0, 0x17);
    local[0] = 5;
    local[4] = (u8)param_1;
    *(u16*)&local[2] = 1;
    iVar1 = k_msgq_put(0x2000392cUL, local, 0, 0);
    if (iVar1 == 0) {
        uVar4 = 0;
        if (*(volatile int*)0x2000230cUL > 2) {
            u32 uVar3 = (u32)(param_1 - 1);
            u32 uVar2;
            if ((uVar3 & 0xff) < 0x11) {
                uVar2 = *(volatile u32*)(0x200024f4UL + (uVar3 & 0xff) * 4);
            } else {
                uVar2 = 0xef596U;
            }
            if (*(volatile u32*)0x20007554UL == 0) {
                DEBUG_PRINT(0xef59eU, 0xef6d4U, uVar2);
            } else {
                debug_print(0xef59eU, 0xef6d4U, uVar2);
            }
        }
    } else {
        DEBUG_PRINT(0xef058U, 0xef6d4U);
        uVar4 = 0xffffffffU;
    }
    return uVar4;
}

