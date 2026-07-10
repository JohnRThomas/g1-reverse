#include "g1_app_symbols.h"
/* named: opt3007_chip_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed opt3007_chip_init @ 0x2e67c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef unsigned char byte;
extern void DEBUG_PRINT(u32 a,...);
extern int get_device_info(void);
extern void debug_print(void);
extern int opt3001_reg_read(int a, void* b);
extern int z_device_is_ready(u32 a);
#define FLAG (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/)

u32 opt3007_chip_init(int param_1){
    unsigned short local_2c; unsigned short local_2a;
    unsigned char local_28; byte local_27; unsigned char local_26;
    unsigned char *local_24; u32 local_20; unsigned char local_1c;
    int iVar5; u32 uVar6=0; u32 uVar4;
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *piVar2 = (volatile int*)((uintptr_t)&g_opt3007_dev) /*=0x20007b6c*/;
    volatile int *piVar3;

    local_2c = 0;
    if (param_1 == 0) { param_1 = get_device_info(); param_1 = param_1 + 0xf80; }
    iVar5 = *piVar1;
    *piVar2 = param_1;
    if (2 < iVar5) {
        if (FLAG == 0) DEBUG_PRINT("%s(): opt3007 init start:\n" /*=0xa3b3f*/, "opt3007_chip_init" /*=0xa3d00*/);
        else debug_print();
    }
    iVar5 = opt3001_reg_read(0x7e, &local_2c);
    if (iVar5 == 0) {
        uVar6 = local_2c;
        if (1 < *piVar1) {
            if (FLAG == 0) DEBUG_PRINT("%s(): mfg_id=0x%x,\n" /*=0xa3b7a*/, "opt3007_chip_init" /*=0xa3d00*/, uVar6);
            else debug_print();
        }
        if (uVar6 == 0x5449) {
            iVar5 = opt3001_reg_read(0x7f, &local_2c);
            if (iVar5 != 0) {
                if (*piVar1 < 1) return 0xfffffffbUL;
                iVar5 = FLAG; uVar4 = "%s(): opt3007 dev id=0x%x err!\n" /*=0xa3bb6*/; goto LAB_0002e6c8;
            }
            uVar6 = local_2c;
            if (1 < *piVar1) {
                if (FLAG == 0) DEBUG_PRINT("%s(): dev_id=0x%x,\n" /*=0xa3bd6*/, "opt3007_chip_init" /*=0xa3d00*/, uVar6);
                else debug_print();
            }
            if (uVar6 == 0x3001) {
                iVar5 = opt3001_reg_read(1, &local_2a);
                piVar3 = (volatile int*)((uintptr_t)&g_opt3007_bus_dev) /*=0x200023fc*/;
                if (iVar5 == 0) {
                    local_27 = (byte)(((local_2a & 63999) >> 8) | 6);
                    local_28 = 1;
                    local_26 = (unsigned char)(local_2a & 63999);
                    iVar5 = z_device_is_ready((u32)*piVar3);
                    if (iVar5 == 0) {
                        if (*piVar1 < 1) return 0xfffffffbUL;
                        if (FLAG == 0) DEBUG_PRINT("%s(): Bus device is not ready\n" /*=0xa3af8*/, "opt3001_reg_write" /*=0xa3cee*/);
                        else debug_print();
                    } else {
                        int obj, vt; int (*f)(int,void*,int,int);
                        local_24 = &local_28; local_20 = 3; local_1c = 2;
                        obj = *piVar3;
                        vt = *(int*)(uintptr_t)(obj + 8);
                        f = *(int(**)(int,void*,int,int))(uintptr_t)(vt + 8);
                        iVar5 = f(obj, &local_24, 1, 0x45);
                        if (-1 < iVar5) {
                            if (*piVar2 != 0) *(volatile u32*)(uintptr_t)(*piVar2 + 0x10) = 1;
                            if (2 < *piVar1) {
                                if (FLAG == 0) DEBUG_PRINT("%s(): opt3007 init done!\n" /*=0xa3c68*/, "opt3007_chip_init" /*=0xa3d00*/);
                                else debug_print();
                            }
                            *(volatile byte*)((uintptr_t)&g_opt3007_chip_ready) /*=0x20018da1*/ = 1;
                            return 0;
                        }
                        if (*piVar1 < 1) return 0xfffffffbUL;
                        if (FLAG == 0) DEBUG_PRINT("%s(): opt3007 i2c write err=%d,\n" /*=0xa3c0c*/, "opt3001_reg_write" /*=0xa3cee*/);
                        else debug_print();
                    }
                }
                if (*piVar1 < 1) return 0xfffffffbUL;
                if (FLAG != 0) { debug_print(); return 0xfffffffbUL; }
                DEBUG_PRINT("%s(): opt3007 Failed to set mode to continuous conversion\n" /*=0xa3c2d*/, "opt3007_chip_init" /*=0xa3d00*/);
                return 0xfffffffbUL;
            }
            if (*piVar1 < 1) return 0xffffff7aUL;
            iVar5 = FLAG; uVar4 = "%s(): opt3007 Bad device id 0x%x\n" /*=0xa3bea*/;
        } else {
            if (*piVar1 < 1) return 0xffffff7aUL;
            iVar5 = FLAG; uVar4 = "%s(): opt3007 Bad manufacturer id 0x%x\n" /*=0xa3b8e*/;
        }
        if (iVar5 == 0) DEBUG_PRINT(uVar4, "opt3007_chip_init" /*=0xa3d00*/, uVar6);
        else debug_print();
        return 0xffffff7aUL;
    }
    if (*piVar1 < 1) return 0xfffffffbUL;
    iVar5 = FLAG; uVar4 = "%s(): opt3007 mfg id=0x%x, err\n" /*=0xa3b5a*/;
LAB_0002e6c8:
    if (iVar5 == 0) DEBUG_PRINT(uVar4, "opt3007_chip_init" /*=0xa3d00*/, (u32)local_2c);
    else debug_print();
    return 0xfffffffbUL;
}

