#include "g1_app_symbols.h"
/* named: pull_message */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed pull_message @ 0x342e0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void debug_print(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int get_device_info(void);

unsigned char pull_message(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int iVar3;

    if (param_1 == (int *)0) {
        if (0 < *(int *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): [%s-%d] message is NULL \n\n" /*=0xa804b*/, "pull_message" /*=0xa822e*/, "pull_message" /*=0xa8221*/, 0x3bdU, param_4);
            } else {
                debug_print("%s(): [%s-%d] message is NULL \n\n" /*=0xa804b*/, "pull_message" /*=0xa822e*/, "pull_message" /*=0xa8221*/, 0x3bdU);
            }
        }
    } else {
        iVar3 = get_device_info();
        if (*(unsigned char *)(iVar3 + 0xdd) <= 0xa) {
            *param_1 = (unsigned int)(*(unsigned char *)((uintptr_t)&g_message_pool_index) /*=0x2001a22a*/) * 0x1b4 + (g_message_pool) /*=0x20007dac*/;
            if (*(int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("[csh_debug_msg]g_curShowMsgIdx is %d \n" /*=0xa80bc*/, 0, 0, 0, 0);
            } else {
                debug_print("[csh_debug_msg]g_curShowMsgIdx is %d \n" /*=0xa80bc*/, 0, 0, 0);
            }
            return *(unsigned char *)((uintptr_t)&g_message_pool_index) /*=0x2001a22a*/;
        }
        if (*(int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            iVar3 = get_device_info();
            DEBUG_PRINT("exception handle, GLOBAL->master_sync_pkg.panel_data_pkg.unread_msg_num is %d \n" /*=0xa806c*/, (unsigned int)*(unsigned char *)(iVar3 + 0xdd), 0, 0, 0);
        } else {
            iVar3 = get_device_info();
            debug_print("exception handle, GLOBAL->master_sync_pkg.panel_data_pkg.unread_msg_num is %d \n" /*=0xa806c*/, *(unsigned char *)(iVar3 + 0xdd), 0, 0);
        }
    }
    return 10;
}

