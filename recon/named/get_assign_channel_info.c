/* named: get_assign_channel_info */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20019ef3  g_test_mode_flag             
*/
/* Reconstructed get_assign_channel_info @ 0x31fd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned uint; typedef unsigned char byte;
extern int DEBUG_PRINT(int,...);
extern int get_device_info(int,...);
extern int debug_print(int,...);
extern int build_and_send_device_status_report(int,...);
extern int read_sys_settting_from_flash(int,...);
extern int k_msleep_ticks32768_b(int,...);

unsigned get_assign_channel_info(int param_1, unsigned param_2, unsigned *param_3, unsigned char *param_4)
{
    volatile int *piVar1,*piVar2; unsigned uVar3; int iVar4; char cVar5; unsigned char *puVar6;
    unsigned char auStack_9c[8]; char local_94; char local_47; char local_46;
    piVar1 = (volatile int*)0x2000230c;
    if(3 < *piVar1){
        if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x000a723e, 0x000a76da); }
        else { debug_print(0); }
    }
    if(param_3 == 0 || param_4 == 0){
        if(0 < *piVar1){
            if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x000a7266, 0x000a76da); }
            else { debug_print(0); }
        }
        uVar3 = 0xffffffff;
    } else if(*(volatile char*)0x20019ef3 == 1){
        puVar6 = (unsigned char*)*param_3;
        iVar4 = get_device_info(0);
        *(unsigned char*)(iVar4 + 2) = *(unsigned char*)(param_1 + 4);
        iVar4 = get_device_info(0);
        *(unsigned char*)(iVar4 + 3) = *(unsigned char*)(param_1 + 5);
        iVar4 = get_device_info(0);
        *(unsigned char*)(iVar4 + 4) = *(unsigned char*)(param_1 + 6);
        piVar2 = (volatile int*)0x20007554;
        if(3 < *piVar1){
            if(*(volatile int*)0x20007554 == 0){
                iVar4 = get_device_info(0);
                DEBUG_PRINT(0x000a7293, 0x000a76da, (uint)*(byte*)(iVar4 + 2));
            } else {
                iVar4 = get_device_info(0);
                debug_print(0x000a7293, 0x000a76da, *(unsigned char*)(iVar4 + 2));
            }
            if(3 < *piVar1){
                if(*piVar2 == 0){
                    iVar4 = get_device_info(0);
                    DEBUG_PRINT(0x000a72ab, 0x000a76da, (uint)*(byte*)(iVar4 + 3));
                } else {
                    iVar4 = get_device_info(0);
                    debug_print(0x000a72ab, 0x000a76da, *(unsigned char*)(iVar4 + 3));
                }
                if(3 < *piVar1){
                    if(*piVar2 == 0){
                        iVar4 = get_device_info(0);
                        DEBUG_PRINT(0x000a72c6, 0x000a76da, (uint)*(byte*)(iVar4 + 4));
                    } else {
                        iVar4 = get_device_info(0);
                        debug_print(0x000a72c6, 0x000a76da, *(unsigned char*)(iVar4 + 4));
                    }
                }
            }
        }
        uVar3 = get_device_info(0);
        build_and_send_device_status_report(uVar3, 0);
        cVar5 = 0;
        *puVar6 = 0x1d;
        puVar6[2] = 3;
        puVar6[1] = 1;
        puVar6[3] = 1;
        puVar6[4] = 0;
        do {
            iVar4 = read_sys_settting_from_flash((int)auStack_9c);
            if(iVar4 == 0 && *(char*)(param_1 + 4) == local_94 &&
               *(char*)(param_1 + 5) == local_47 && *(char*)(param_1 + 6) == local_46)
                goto LAB_00032102;
            cVar5 = cVar5 + 1;
            k_msleep_ticks32768_b(100);
        } while(cVar5 != 5);
        puVar6[4] = 1;
LAB_00032102:
        uVar3 = 0;
        *param_4 = 5;
    } else {
        DEBUG_PRINT(0x000a672f);
        uVar3 = 0xfffffffe;
    }
    return uVar3;
}

