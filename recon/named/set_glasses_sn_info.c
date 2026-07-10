/* named: set_glasses_sn_info */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20019ef3  g_test_mode_flag             
*/
/* Reconstructed set_glasses_sn_info @ 0x31ee8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int debug_print(int,...);
extern int build_and_send_device_status_report(int,int);
extern int FUN_000232b8(void);
extern int FUN_000232dc(int);
extern int read_sys_settting_from_flash(void*);
extern int printf(int,int);
extern int k_msleep_ticks32768_b(int);
extern int memcmp(int,void*,int);

uint32_t set_glasses_sn_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    uint32_t uVar1;
    int iVar2;
    int8_t cVar3;
    uint8_t *puVar4;
    uint8_t auStack_9c[53];
    uint8_t auStack_67[83];
    DEBUG_PRINT(0x000a718e);
    if (param_3==0 || param_4==0){ DEBUG_PRINT(0x000a71ab); uVar1=0xffffffff; }
    else if (*(volatile uint8_t*)0x20019ef3UL == 1){
        param_1 = param_1 + 4;
        puVar4 = (uint8_t*)*param_3;
        FUN_000232dc(param_1);
        printf(0x000a71cd, param_1);
        uVar1 = get_device_info();
        build_and_send_device_status_report(uVar1,0);
        if (2 < *(volatile int*)0x2000230cUL){
            if (*(volatile int*)0x20007554UL == 0){ uVar1=FUN_000232b8(); DEBUG_PRINT(0x000a71e0,0x000a769d,uVar1); }
            else { uVar1=FUN_000232b8(); debug_print(0x000a71e0,0x000a769d,uVar1); }
        }
        *puVar4=0x29; puVar4[1]=1; puVar4[3]=1; cVar3=5; puVar4[2]=3; puVar4[4]=0; *param_4=5;
        do {
            iVar2 = read_sys_settting_from_flash(auStack_9c);
            if (iVar2==0 && (iVar2=memcmp(param_1, auStack_67, 0xb))==0){ DEBUG_PRINT(0x000a7209); goto done; }
            cVar3 = cVar3 - 1;
            k_msleep_ticks32768_b(100);
        } while (cVar3 != 0);
        puVar4[4]=1;
done:   uVar1=0;
    } else { DEBUG_PRINT(0x000a672f); uVar1=0xfffffffe; }
    return uVar1;
}

