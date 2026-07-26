#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00048a3c @ 0x00048a3c
 * public-name: SendDashBoardStartupModeInfoToSlave
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef5df                             @ 0x000ef5df
 *   rodata_ef603                             @ 0x000ef603   [INLINED -- G6 literal batch]
 *   rodata_ef6b0                             @ 0x000ef6b0   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed SendDashBoardStartupModeInfoToSlave @ 0x48a3c  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);

unsigned int SendDashBoardStartupModeInfoToSlave(int param_1)
{
    int iVar1;
    unsigned int uVar2, uVar3;
    unsigned char buf[24];

    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 6;
    buf[4] = (unsigned char)param_1;
    *(unsigned short*)(buf + 2) = 1;
    iVar1 = k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, buf, 0, 0);
    if (iVar1 == 0) {
        uVar3 = 0;
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            uVar2 = 0xef5f3;
            if (param_1 == 1) {
                uVar2 = ((unsigned long)&rodata_ef5df) /*=0xef5df*/;
            }
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): send dashboard startup mode to slave . startup mode  = %s\n") /*=0xef603*/, ((unsigned long)"SendDashBoardStartupModeInfoToSlave") /*=0xef6b0*/, uVar2, ((unsigned long)&rodata_ef5df) /*=0xef5df*/);
            } else {
                debug_print(((unsigned long)"%s(): send dashboard startup mode to slave . startup mode  = %s\n") /*=0xef603*/, ((unsigned long)"SendDashBoardStartupModeInfoToSlave") /*=0xef6b0*/, uVar2, ((unsigned long)&rodata_ef5df) /*=0xef5df*/);
            }
        }
    } else {
        log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"SendDashBoardStartupModeInfoToSlave") /*=0xef6b0*/);
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
