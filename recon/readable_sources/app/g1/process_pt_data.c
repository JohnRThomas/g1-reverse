#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x000332a4       => struct g1_layout_pt_data_indices__global_0961           [global_0961; G1-original]
 *   local_1c         => struct g1_layout_pt_data_pair__stack_0960               [stack_0960; G1-original]
 * Raw function identity: 0x000330ec.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000330ec @ 0x000330ec
 * public-name: process_pt_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_delay_deadline                       <= FUN_0002a4d8 @ 0x0002a4d8
 *   display_dev_reg_config                   <= FUN_0002eaa8 @ 0x0002eaa8
 *   set_pending_state_flag                   <= FUN_0002eb28 @ 0x0002eb28
 *   erase_audio_buffer                       <= FUN_0002f008 @ 0x0002f008
 *   nfc_eeprom_comm_lock                     <= FUN_00030cb8 @ 0x00030cb8
 *   nfc_eeprom_comm_unlock                   <= FUN_00030cc4 @ 0x00030cc4
 *   pt_comm_transport_write                  <= FUN_00030cd0 @ 0x00030cd0
 *   pt_cmd_dispatch_and_encode_response      <= FUN_00032b24 @ 0x00032b24
 *   process_pt_data                          <= FUN_000330ec @ 0x000330ec
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   serial_data_read_dispatch                <= FUN_0007d0e8 @ 0x0007d0e8
 *   k_msleep_ticks32768_c                    <= FUN_0007d194 @ 0x0007d194
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_a776c                             @ 0x000a776c
 *   rodata_a7780                             @ 0x000a7780
 *   rodata_a779f                             @ 0x000a779f
 *   rodata_a77b5                             @ 0x000a77b5
 *   rodata_a77cc                             @ 0x000a77cc
 *   rodata_a780d                             @ 0x000a780d
 *   rodata_a7882                             @ 0x000a7882
 *   g_log_level                              @ 0x2000230c
 *   g_fuel_gauge_dev                         @ 0x20002424
 *   g_pt_comm_dev                            @ 0x20002428
 *   g_pt_comm_state                          @ 0x2000242c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_low_power_mode_enabled                 @ 0x20018d94
 *   g_system_19ff5                           @ 0x20019ff5
 *   g_pt_status_msg_buf                      @ 0x2001a0f5
 */
/* Reconstructed FUN_000330ec @ 0x330ec  (parity: 300/300 trials, PROVEN) */
extern int log_message(int,...);
extern int debug_print(int,...);
extern int set_delay_deadline(int,...);
extern int display_dev_reg_config(void);
extern int set_pending_state_flag(int,...);
extern int erase_audio_buffer(void);
extern int nfc_eeprom_comm_lock(void);
extern int nfc_eeprom_comm_unlock(void);
extern int pt_comm_transport_write(int,...);
extern int pt_cmd_dispatch_and_encode_response(int,...);
extern int sys_reboot(int,...);
extern int serial_data_read_dispatch(int,...);
extern int k_msleep_ticks32768_c(int,...);
extern int change_work_mode_to(int,...);

unsigned process_pt_data(unsigned param_1)
{
    unsigned uVar6 = ((unsigned long)&g_system_19ff5) /*=0x20019ff5*/;
    unsigned uVar4;
    int iVar3;
    unsigned char *pbVar5;
    unsigned char *L = (unsigned char *)((unsigned long)&g_pt_status_msg_buf) /*=0x2001a0f5*/;
    unsigned local_28 = 0;
    unsigned local_24 = 0;
    unsigned local_20 = ((unsigned long)&g_system_19ff5) /*=0x20019ff5*/;
    unsigned char *local_1c = L;
    unsigned int mode;
    int channel;

    if ((*(volatile int *)((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/ == 0) || (*(volatile int *)((unsigned long)&g_pt_comm_dev) /*=0x20002428*/ == 0) ||
        ((char)*(volatile unsigned char *)((unsigned long)&g_pt_comm_state) /*=0x2000242c*/ == 2)) {
        log_message(((unsigned long)&rodata_a776c) /*=0xa776c*/);
        return 0xffffffff;
    }

    nfc_eeprom_comm_lock();
    mode = *(volatile unsigned char *)((unsigned long)&g_pt_comm_state) /*=0x2000242c*/;
    channel = *(volatile int *)((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/;
    if (mode != 0)
        channel = *(volatile int *)((unsigned long)&g_pt_comm_dev) /*=0x20002428*/;
    iVar3 = serial_data_read_dispatch(mode, channel, &local_20, &local_24);
    if (iVar3 != 0) { nfc_eeprom_comm_unlock(); return 0xfffffffe; }

    iVar3 = pt_cmd_dispatch_and_encode_response(mode, uVar6, local_24 & 0xff,
                         &local_1c, &local_28, param_1);
    if (iVar3 != 0) { log_message(((unsigned long)&rodata_a7780) /*=0xa7780*/); nfc_eeprom_comm_unlock(); return 0xfffffffd; }

    channel = *(volatile int *)((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/;
    if (mode != 0)
        channel = *(volatile int *)((unsigned long)&g_pt_comm_dev) /*=0x20002428*/;
    iVar3 = pt_comm_transport_write(mode, channel, local_1c, local_28 & 0xff);
    if (iVar3 != 0) { log_message(((unsigned long)&rodata_a779f) /*=0xa779f*/); nfc_eeprom_comm_unlock(); return 0xfffffffc; }

    nfc_eeprom_comm_unlock();
    if (local_1c[9] == 0x80) {
        k_msleep_ticks32768_c(1000);
        local_1c[9] = 0;
        nfc_eeprom_comm_lock();
        pt_comm_transport_write(mode, *(volatile int *)((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/,
                     local_1c, local_28 & 0xff);
        nfc_eeprom_comm_unlock();
    }

    pbVar5 = local_1c;
    if (mode != 0) pbVar5 = local_1c + 4;
    uVar4 = (unsigned)*pbVar5;
    uVar6 = 0;
    if (uVar4 == 0x1b) {
        if (pbVar5[8] != 0) erase_audio_buffer();
    } else if (uVar4 == 0x13) {
        if (((pbVar5[4] & 0xfb) == 0) && (iVar3 = display_dev_reg_config(), iVar3 != 0)) uVar6 = 0xfffffffb;
    } else {
        if (uVar4 != 6) {
            if (uVar4 != 0xb) goto control_label_0003325a;
            pbVar5 = (unsigned char *)*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
            if ((int)pbVar5 < 1) goto control_label_0003324c;
            pbVar5 = (unsigned char *)*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            do {
                if (pbVar5 == 0) log_message(((unsigned long)&rodata_a77cc) /*=0xa77cc*/, ((unsigned long)&rodata_a7882) /*=0xa7882*/);
                else debug_print(((unsigned long)&rodata_a77cc) /*=0xa77cc*/, ((unsigned long)&rodata_a7882) /*=0xa7882*/);
control_label_0003324c:
                do {
                    while (1) {
                        k_msleep_ticks32768_c(300);
                        sys_reboot(1);
control_label_0003325a:
                        if (uVar4 != 0x3c) break;
                        if (pbVar5[4] != 0) return 0;
                        pbVar5 = (unsigned char *)*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
                        if (0 < (int)pbVar5) {
                            pbVar5 = (unsigned char *)*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                            if (pbVar5 == 0) log_message(((unsigned long)&rodata_a780d) /*=0xa780d*/, ((unsigned long)&rodata_a7882) /*=0xa7882*/);
                            else debug_print(((unsigned long)&rodata_a780d) /*=0xa780d*/, ((unsigned long)&rodata_a7882) /*=0xa7882*/);
                        }
                    }
                    if (uVar4 != 1) return 0;
                    if (pbVar5[4] != 0) return 0;
                    pbVar5 = (unsigned char *)*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
                } while ((int)pbVar5 < 1);
                pbVar5 = (unsigned char *)*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            } while (1);
        }
        if (pbVar5[2] == 2) {
            *(volatile unsigned char *)((unsigned long)&g_low_power_mode_enabled) /*=0x20018d94*/ = 1;
            set_pending_state_flag(1);
            set_delay_deadline(10000);
        } else {
            log_message(((unsigned long)&rodata_a77b5) /*=0xa77b5*/);
            k_msleep_ticks32768_c(10000);
            change_work_mode_to(7);
        }
    }
    return uVar6;
}
