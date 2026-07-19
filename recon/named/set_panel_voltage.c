/* readable reconstruction; identity: FUN_00032308 @ 0x00032308
 * public-name: set_panel_voltage
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   read_sys_settting_from_flash             <= FUN_000232f8 @ 0x000232f8
 *   set_panel_voltage                        <= FUN_00032308 @ 0x00032308
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 * address symbols (name @ address):
 *   rodata_a6711                             @ 0x000a6711
 *   rodata_a671e                             @ 0x000a671e
 *   rodata_a676d                             @ 0x000a676d
 *   rodata_a7712                             @ 0x000a7712
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00032308 @ 0x32308  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(unsigned,...);
extern int get_device_info(void);
extern void debug_print(unsigned int, ...);
extern void build_and_send_device_status_report(int,int);
extern int read_sys_settting_from_flash(void*);
extern void k_msleep_ticks32768_b(int);

int set_panel_voltage(int param_1, unsigned param_2, uint32_t *param_3, uint8_t *param_4){
    unsigned char status_record[21];
    log_message(0x000a6711, 0x000a7712);
    if (param_3==0 || param_4==0 || param_1==0 || param_2 < 5){
        log_message(0x000a671e, 0x000a7712);
        return 0xffffffff;
    }
    unsigned char *puVar6 = (unsigned char*)*param_3;
    *puVar6 = 0x3c;
    puVar6[2]=3; puVar6[1]=1; puVar6[3]=1;
    unsigned char bVar1 = *(unsigned char*)(param_1+4);
    unsigned char uVar4;
    if (bVar1 < 2){
        int iVar2 = get_device_info();
        if (*(unsigned char*)(iVar2+0xed4) != bVar1){
            iVar2 = get_device_info(); *(unsigned char*)(iVar2+0xed4) = bVar1;
            iVar2 = get_device_info(); build_and_send_device_status_report(iVar2, 0);
            char cVar5 = 0;
            do {
                iVar2 = read_sys_settting_from_flash(status_record);
                if (iVar2 == 0 && status_record[20] == bVar1) break;
                cVar5 = cVar5 + 1;
                k_msleep_ticks32768_b(100);
            } while (cVar5 != 5);
            puVar6[4] = (cVar5 == 5);
            goto LAB;
        }
        uVar4 = 4;
    } else {
        if (*(int*)0x20007554 == 0) log_message(0x000a676d, 0x000a7712, 0x3c1);
        else debug_print(0x000a676d, 0x000a7712, 0x3c1);
        uVar4 = 3;
    }
    puVar6[4] = uVar4;
    LAB:
    *param_4 = 5;
    return 0;
}
