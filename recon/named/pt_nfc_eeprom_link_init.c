/* named: pt_nfc_eeprom_link_init */
/* globals referenced:
//   0x20007bc0  g_pt_nfc_link_cfg            
//   0x20019dad  g_pt_nfc_link_busy           
*/
/* Reconstructed pt_nfc_eeprom_link_init @ 0x30b3c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int attr_store_set(int,int);
extern int flash_driver_reset_sequence(void);
extern int flash_apply_config_table(void);
extern int attr_store_get(int,void*);
extern int flash_get_ready_status_bit(void);
extern int commit_default_config_record(void);
extern int flash_firmware_update_transfer(int);
extern int wait_for_attr_0x4410_set(void);

int pt_nfc_eeprom_link_init(int *param_1){
    uint8_t auStack_1c[4], auStack_18[4], auStack_14[8];
    int iVar1;
    if (param_1 && *param_1 && param_1[1] && param_1[2] && param_1[3]){
        *(volatile int*)0x20007bc0UL = (int)param_1;
        *(volatile int*)0x20007bc8UL = 0;
        *(volatile int*)0x20007bc4UL = 0;
        *(volatile uint8_t*)0x20019dadUL = 0;
        *(volatile uint8_t*)0x20003030UL = 1;
        iVar1 = flash_get_ready_status_bit();
        if (iVar1 != -1 && (iVar1=flash_driver_reset_sequence())==0 && (iVar1=wait_for_attr_0x4410_set())!=-1){
            if (iVar1 == -2){
                attr_store_set(0xff20, 0x3c00f091);
                attr_store_get(0x1c00, auStack_1c);
                attr_store_get(0x4744, auStack_14);
                attr_store_get(0x4444, auStack_18);
                attr_store_set(0xff20, 0x3c00f011);
            }
            iVar1 = flash_firmware_update_transfer(iVar1 == -2);
            if (iVar1==0 || ((iVar1=commit_default_config_record())==0 && (iVar1=flash_driver_reset_sequence())==0 && (iVar1=flash_get_ready_status_bit())==0 && (iVar1=wait_for_attr_0x4410_set())==0)){
                iVar1 = flash_apply_config_table();
                if (iVar1 != 0) iVar1 = 1;
                return -iVar1;
            }
        }
    }
    return -1;
}

