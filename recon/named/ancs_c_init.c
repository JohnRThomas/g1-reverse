/* named: ancs_c_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ae8  g_ancs_client                
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed ancs_c_init @ 0x1905c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int debug_print(int,...);
extern int FUN_0007f69e(int,...);
extern int bt_ancs_register_attr(int,...);
extern int bt_ancs_register_app_attr(int,...);
#define C8 (*(volatile int*)0x2000230c)
#define CC (*(volatile int*)0x20007554)

int ancs_c_init(int param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
    int iVar1; unsigned uVar2;
    iVar1 = FUN_0007f69e(0x20006ae8);
    if(iVar1 == 0){
        iVar1 = bt_ancs_register_attr(0x20006ae8, 0, param_1+0x10, 0x20, param_4);
        if(iVar1 == 0){
            iVar1 = bt_ancs_register_app_attr(0x20006ae8, 0, param_1+0x30, 0x20);
            if(iVar1 == 0){
                iVar1 = bt_ancs_register_attr(0x20006ae8, 1, param_1+0x50, 0x20, param_4);
                if(iVar1 == 0){
                    iVar1 = bt_ancs_register_attr(0x20006ae8, 2, param_1+0x70, 0x20, param_4);
                    if(iVar1 == 0){
                        iVar1 = bt_ancs_register_attr(0x20006ae8, 3, param_1+0x90, 0x100);
                        if(iVar1 == 0){
                            iVar1 = bt_ancs_register_attr(0x20006ae8, 5, param_1+400, 0x20);
                            if(iVar1 == 0) return 0;
                            if(C8 < 1) return iVar1;
                            if(CC == 0){ uVar2 = 0x3e4; goto LAB_00019090; }
                            uVar2 = 0x3e4;
                        } else {
                            if(C8 < 1) return iVar1;
                            if(CC == 0){ uVar2 = 0x3dc;
LAB_00019090:
                                DEBUG_PRINT(0x0009ab0c, 0x0009b15e, uVar2, iVar1); return iVar1; }
                            uVar2 = 0x3dc;
                        }
                    } else {
                        if(C8 < 1) return iVar1;
                        if(CC == 0){ uVar2 = 0x3d4; goto LAB_00019090; }
                        uVar2 = 0x3d4;
                    }
                } else {
                    if(C8 < 1) return iVar1;
                    if(CC == 0){ uVar2 = 0x3cc; goto LAB_00019090; }
                    uVar2 = 0x3cc;
                }
            } else {
                if(C8 < 1) return iVar1;
                if(CC == 0){ uVar2 = 0x3c4; goto LAB_00019090; }
                uVar2 = 0x3c4;
            }
        } else {
            if(C8 < 1) return iVar1;
            if(CC == 0){ uVar2 = 0x3bc; goto LAB_00019090; }
            uVar2 = 0x3bc;
        }
    } else {
        if(C8 < 1) return iVar1;
        if(CC == 0){ uVar2 = 0x3b4; goto LAB_00019090; }
        uVar2 = 0x3b4;
    }
    debug_print(0x0009ab0c, 0x0009b15e, uVar2, iVar1);
    return iVar1;
}

