/* named: load_usr_setting */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed load_usr_setting @ 0x22e78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int flash_settings_read(int, void*, int);
extern void reset_usr_setting(int);
extern int is_battery_critical(void);
extern void set_test_mode(int);
extern void FUN_0007c28e(int, int);
extern void memset_bytes(void*, int, int);

int load_usr_setting(int param_1)
{
    volatile int *dbg = (volatile int*)0x2000230c;
    volatile int *a4 = (volatile int*)0x20007554;
    volatile uint8_t buf[0x20];
    int iVar1;
    int local_34;
    uint8_t local_24, local_21;

    memset_bytes((void*)buf, 0, 0x20);
    iVar1 = flash_settings_read(0x134000, (void*)buf, 0x20);
    if (iVar1 != 0) {
        if (1 < *dbg) { if (*a4 == 0) DEBUG_PRINT(); else debug_print(); }
        return -1;
    }
    if (1 < *dbg) { if (*a4 == 0) DEBUG_PRINT(); else debug_print(); }

    *(volatile uint8_t*)(param_1 + 0xed5) = buf[1];
    *(volatile uint8_t*)(param_1 + 0xef4) = buf[2];
    local_34 = *(volatile int*)(buf + 4);
    if (local_34 == 0) local_34 = 400;
    *(volatile int*)(param_1 + 0xf6c) = local_34;
    *(volatile uint8_t*)(param_1 + 0xfea) = buf[0];
    *(volatile uint8_t*)(param_1 + 0xf98) = buf[8];
    *(volatile uint8_t*)(param_1 + 0xf60) = buf[3];
    *(volatile uint8_t*)(param_1 + 0x1070) = buf[9];
    *(volatile uint8_t*)(param_1 + 0x108d) = buf[0xa];
    *(volatile uint8_t*)(param_1 + 0xec0) = buf[0xb];
    *(volatile uint32_t*)(param_1 + 0x1069) = *(volatile uint32_t*)(buf + 0xc);
    *(volatile uint8_t*)(param_1 + 0x106f) = buf[0x12];
    *(volatile uint16_t*)(param_1 + 0x106d) = *(volatile uint16_t*)(buf + 0x10);
    *(volatile uint8_t*)(param_1 + 0xef5) = buf[0x13];
    local_24 = buf[0x14];
    if (1 < local_24) local_24 = 0;
    *(volatile uint8_t*)(param_1 + 0x108f) = local_24;
    *(volatile uint8_t*)(param_1 + 0x1090) = buf[0x15];
    *(volatile uint8_t*)(param_1 + 0x1091) = buf[0x16];
    *(volatile uint8_t*)(param_1 + 0xec1) = buf[0x18];
    *(volatile uint32_t*)(param_1 + 0xf68) = *(volatile uint32_t*)(buf + 0x1c);

    if ((uint8_t)(buf[0] & buf[3]) == 0xff) {
        reset_usr_setting(param_1);
    }
    if (8 < *(volatile uint8_t*)(param_1 + 0xec0)) {
        *(volatile uint8_t*)(param_1 + 0xec0) = 3;
    }
    if ((uint32_t)(*(volatile uint8_t*)(param_1 + 0xec1) - 1) > 8) {
        *(volatile uint8_t*)(param_1 + 0xec1) = 3;
    }
    if (*(volatile int8_t*)(param_1 + 0xfea) == 11) {
        *(volatile uint8_t*)(param_1 + 0xfea) = 10;
        FUN_0007c28e(param_1, 0);
    }
    local_21 = buf[0x17];
    if (1 < local_21) local_21 = 0;
    set_test_mode(local_21);
    iVar1 = is_battery_critical();
    if (iVar1 == 1) {
        *(volatile uint8_t*)(param_1 + 0xf98) = 0;
        *(volatile uint8_t*)(param_1 + 0xfea) = 0xb;
        *(volatile uint8_t*)(param_1 + 0xed5) = 0x15;
        *(volatile uint16_t*)(param_1 + 0xec0) = 0x303;
    } else {
        *(volatile uint8_t*)(param_1 + 0xfea) = 10;
    }
    if (*(volatile int*)(param_1 + 0xf68) == -1) {
        *(volatile uint32_t*)(param_1 + 0xf68) = 0;
    }
    return 0;
}

