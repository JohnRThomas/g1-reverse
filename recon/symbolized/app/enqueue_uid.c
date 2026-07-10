#include "g1_app_symbols.h"
/* named: enqueue_uid */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a38  g_uid_pipe                   
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed enqueue_uid @ 0x18e48  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, unsigned b, unsigned c);
extern void debug_print(void);
extern void k_msgq_get(unsigned a, void*b, int c, int d);
extern int  k_msgq_put(unsigned a, void*b, int c, int d);
int enqueue_uid(unsigned *param_1, unsigned param_2, unsigned param_3){
    unsigned local[3];
    local[0]=0; local[1]=0; local[2]=param_3;
    volatile int *g = (volatile int*)((uintptr_t)&g_uid_pipe) /*=0x20006a38*/;
    if (g[0x10/4] == 0) return 1;
    int iVar2;
    if (g[0x24/4] == 10){
        k_msgq_get(((uintptr_t)&g_uid_pipe) /*=0x20006a38*/, local, 0, 0);
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("enqueue uid drop package! \n" /*=0x9aa2f*/,0,0);
        else debug_print();
    }
    local[0] = param_1[0];
    local[1] = param_1[1];
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0){
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): local_data uid %d\n" /*=0x9aa4b*/,"enqueue_uid" /*=0x9b176*/,local[0]);
        else debug_print();
    }
    iVar2 = k_msgq_put(((uintptr_t)&g_uid_pipe) /*=0x20006a38*/, local, 0, 0);
    if (iVar2 != 0 && *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0){
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): en uid F\n" /*=0x9aa64*/,"enqueue_uid" /*=0x9b176*/,0);
        else debug_print();
    }
    return iVar2;
}

