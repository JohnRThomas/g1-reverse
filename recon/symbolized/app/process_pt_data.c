#include "g1_app_symbols.h"
/* named: process_pt_data */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20002424  g_fuel_gauge_dev             
//   0x20007554  g_log_use_alt_sink           
//   0x20018d94  g_low_power_mode_enabled     
*/
/* Reconstructed process_pt_data @ 0x330ec  (parity: 300/300 trials, PROVEN) */
extern int DEBUG_PRINT(int,...);
extern int debug_print(int,...);
extern int set_delay_deadline(int,...);
extern int FUN_0002eaa8(int,...);
extern int set_pending_state_flag(int,...);
extern int erase_audio_buffer(int,...);
extern int nfc_eeprom_comm_lock(int,...);
extern int nfc_eeprom_comm_unlock(int,...);
extern int pt_comm_transport_write(int,...);
extern int FUN_00032b24(int,...);
extern int sys_reboot(int,...);
extern int FUN_0007d0e8(int,...);
extern int k_msleep_ticks32768_c(int,...);
extern int change_work_mode_to(int,...);

unsigned process_pt_data(unsigned param_1)
{
    unsigned uVar6 = ((uintptr_t)&g_system_19ff5) /*=0x20019ff5*/;
    unsigned uVar4;
    int iVar3;
    unsigned char *pbVar5;
    unsigned char *L = (unsigned char *)((uintptr_t)&g_pt_status_msg_buf) /*=0x2001a0f5*/;

    if ((*(volatile int *)((uintptr_t)&g_fuel_gauge_dev) /*=0x20002424*/ == 0) || (*(volatile int *)((uintptr_t)&g_pt_comm_dev) /*=0x20002428*/ == 0) ||
        ((char)*(volatile unsigned char *)((uintptr_t)&g_pt_comm_state) /*=0x2000242c*/ == 2)) {
        DEBUG_PRINT(0);
        return 0xffffffff;
    }

    nfc_eeprom_comm_lock(0);
    iVar3 = FUN_0007d0e8(0);
    if (iVar3 != 0) { nfc_eeprom_comm_unlock(0); return 0xfffffffe; }

    iVar3 = FUN_00032b24(0);
    if (iVar3 != 0) { DEBUG_PRINT(0); nfc_eeprom_comm_unlock(0); return 0xfffffffd; }

    iVar3 = pt_comm_transport_write(0);
    if (iVar3 != 0) { DEBUG_PRINT(0); nfc_eeprom_comm_unlock(0); return 0xfffffffc; }

    nfc_eeprom_comm_unlock(0);
    if (L[9] == 0x80) {
        k_msleep_ticks32768_c(0);
        L[9] = 0;
        nfc_eeprom_comm_lock(0);
        pt_comm_transport_write(0);
        nfc_eeprom_comm_unlock(0);
    }

    pbVar5 = L;
    if ((char)*(volatile unsigned char *)((uintptr_t)&g_pt_comm_state) /*=0x2000242c*/ != 0) pbVar5 = L + 4;
    uVar4 = (unsigned)*pbVar5;
    uVar6 = 0;
    if (uVar4 == 0x1b) {
        if (pbVar5[8] != 0) erase_audio_buffer(0);
    } else if (uVar4 == 0x13) {
        if (((pbVar5[4] & 0xfb) == 0) && (iVar3 = FUN_0002eaa8(0), iVar3 != 0)) uVar6 = 0xfffffffb;
    } else {
        if (uVar4 != 6) {
            if (uVar4 != 0xb) goto LAB_0003325a;
            pbVar5 = (unsigned char *)*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
            if ((int)pbVar5 < 1) goto LAB_0003324c;
            pbVar5 = (unsigned char *)*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            do {
                if (pbVar5 == 0) DEBUG_PRINT(0);
                else debug_print(0);
LAB_0003324c:
                do {
                    while (1) {
                        k_msleep_ticks32768_c(0);
                        sys_reboot(0);
LAB_0003325a:
                        if (uVar4 != 0x3c) break;
                        if (pbVar5[4] != 0) return 0;
                        pbVar5 = (unsigned char *)*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
                        if (0 < (int)pbVar5) {
                            pbVar5 = (unsigned char *)*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
                            if (pbVar5 == 0) DEBUG_PRINT(0);
                            else debug_print(0);
                        }
                    }
                    if (uVar4 != 1) return 0;
                    if (pbVar5[4] != 0) return 0;
                    pbVar5 = (unsigned char *)*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
                } while ((int)pbVar5 < 1);
                pbVar5 = (unsigned char *)*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            } while (1);
        }
        if (pbVar5[2] == 2) {
            *(volatile unsigned char *)((uintptr_t)&g_low_power_mode_enabled) /*=0x20018d94*/ = 1;
            set_pending_state_flag(0);
            set_delay_deadline(0);
        } else {
            DEBUG_PRINT(0);
            k_msleep_ticks32768_c(0);
            change_work_mode_to(7);
        }
    }
    return uVar6;
}

