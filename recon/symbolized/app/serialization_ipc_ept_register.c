#include "g1_app_symbols.h"
/* named: serialization_ipc_ept_register */
/* globals referenced:
//   0x200023cc  g_st25dv_i2c_dev             
//   0x20007a48  g_st25dv_i2c_cfg             
*/
/* Reconstructed serialization_ipc_ept_register @ 0x259d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int z_device_is_ready(int);
extern void kmutex_dlist_init(void);
int serialization_ipc_ept_register(void){
    *(volatile uint32_t*)(((uintptr_t)&g_st25dv_i2c_cfg) /*=0x20007a48*/+8) = ((uintptr_t)&tbl_889d0) /*=0x88a38*/;
    *(volatile uint16_t*)(((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/+4) = 0x53;
    *(volatile uint16_t*)(((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/+8) = 0x53;
    *(volatile uint32_t*)(((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/+0xc) = 0x1000;
    *(volatile uint32_t*)(((uintptr_t)&g_st25dv_i2c_cfg) /*=0x20007a48*/+0x10) = ((uintptr_t)&g_eeprom_comm_mutex) /*=0x20007a60*/;
    *(volatile uint32_t*)(((uintptr_t)&g_st25dv_i2c_cfg) /*=0x20007a48*/+4) = ((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/;
    kmutex_dlist_init();
    int r = z_device_is_ready(*(volatile uint32_t*)((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/);
    uint32_t s = (r==0)? "parent bus device not ready\r\n" /*=0x9f3fa*/ : "eeprom_st25dv_init ready\r\n" /*=0x9f418*/;
    DEBUG_PRINT(s);
    int r2v = z_device_is_ready(*(volatile uint32_t*)((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/);
    int ret;
    if(r2v==0){
        uint32_t base = *(volatile uint32_t*)((uintptr_t)&g_st25dv_i2c_dev) /*=0x200023cc*/;
        DEBUG_PRINT("\nError: Device \"%s\" is not ready; check the driver initialization logs for errors.\n" /*=0x9f433*/, *(volatile uint32_t*)base);
        ret = 0;
    } else {
        DEBUG_PRINT("update_eeprom_interface\r\n" /*=0x9f487*/);
        ret = ((uintptr_t)&g_st25dv_i2c_cfg) /*=0x20007a48*/;
    }
    return ret;
}

